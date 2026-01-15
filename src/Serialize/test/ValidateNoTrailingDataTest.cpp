#include "gtest/gtest.h"
#include "Traits.h"
#include "JsonThor.h"

struct ValidateNoTrailingDataStruct
{
    int validateNoTrailingDataValue = 0;
};

ThorsAnvil_MakeTrait(ValidateNoTrailingDataStruct, validateNoTrailingDataValue);

using ThorsAnvil::Serialize::jsonImporter;
using ThorsAnvil::Serialize::ParserConfig;

TEST(ValidateNoTrailingDataTest, NormalNoTrailing)
{
    using namespace std::string_literals;
    std::stringstream   stream(R"({"validateNoTrailingDataValue":12}     )"s);

    ValidateNoTrailingDataStruct    data;
    bool ok = static_cast<bool>(stream >> jsonImporter(data));

    EXPECT_TRUE(ok);
    EXPECT_EQ(12, data.validateNoTrailingDataValue);
}

TEST(ValidateNoTrailingDataTest, NormalWithTrailing)
{
    using namespace std::string_literals;
    std::stringstream   stream(R"({"validateNoTrailingDataValue":12}   XXX  )"s);

    ValidateNoTrailingDataStruct    data;
    bool ok = static_cast<bool>(stream >> jsonImporter(data));

    EXPECT_TRUE(ok);
    EXPECT_EQ(12, data.validateNoTrailingDataValue);
}

TEST(ValidateNoTrailingDataTest, CheckCleanNoTrailing)
{
    using namespace std::string_literals;
    std::stringstream   stream(R"({"validateNoTrailingDataValue":12}     )"s);

    ValidateNoTrailingDataStruct    data;
    bool ok = static_cast<bool>(stream >> jsonImporter(data, ParserConfig{}.setValidateNoTrailingData()));

    EXPECT_TRUE(ok);
    EXPECT_EQ(12, data.validateNoTrailingDataValue);
}

TEST(ValidateNoTrailingDataTest, CheckCleanWithTrailing)
{
    using namespace std::string_literals;
    std::stringstream   stream(R"({"validateNoTrailingDataValue":12}   XXX  )"s);

    ValidateNoTrailingDataStruct    data;
    bool ok = static_cast<bool>(stream >> jsonImporter(data, ParserConfig{}.setValidateNoTrailingData()));

    EXPECT_FALSE(ok);
    EXPECT_EQ(12, data.validateNoTrailingDataValue);
}


