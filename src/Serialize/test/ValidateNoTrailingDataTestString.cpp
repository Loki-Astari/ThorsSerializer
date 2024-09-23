#include "gtest/gtest.h"
#include "Traits.h"
#include "JsonThor.h"
#include "ThorsSerializerUtil.h"

struct ValidateNoTrailingDataStruct
{
    int validateNoTrailingDataValue = 0;
};

ThorsAnvil_MakeTrait(ValidateNoTrailingDataStruct, validateNoTrailingDataValue);

using ThorsAnvil::Serialize::jsonImporter;
using ThorsAnvil::Serialize::ParserConfig;

TEST(ValidateNoTrailingDataTestString, NormalNoTrailing)
{
    using namespace std::string_literals;
    std::string     stream(R"({"validateNoTrailingDataValue":12}     )"s);

    ValidateNoTrailingDataStruct    data;
    bool ok = static_cast<bool>(stream >> jsonImporter(data));

    EXPECT_TRUE(ok);
    EXPECT_EQ(12, data.validateNoTrailingDataValue);
}

TEST(ValidateNoTrailingDataTestString, NormalWithTrailing)
{
    using namespace std::string_literals;
    std::string     stream(R"({"validateNoTrailingDataValue":12}   XXX  )"s);

    ValidateNoTrailingDataStruct    data;
    bool ok = static_cast<bool>(stream >> jsonImporter(data));

    EXPECT_TRUE(ok);
    EXPECT_EQ(12, data.validateNoTrailingDataValue);
}

TEST(ValidateNoTrailingDataTestString, CheckCleanNoTrailing)
{
    using namespace std::string_literals;
    std::string     stream(R"({"validateNoTrailingDataValue":12}     )"s);

    ValidateNoTrailingDataStruct    data;
    bool ok = static_cast<bool>(stream >> jsonImporter(data, ParserConfig{}.setValidateNoTrailingData()));

    EXPECT_TRUE(ok);
    EXPECT_EQ(12, data.validateNoTrailingDataValue);
}

TEST(ValidateNoTrailingDataTestString, CheckCleanWithTrailing)
{
    using namespace std::string_literals;
    std::string     stream(R"({"validateNoTrailingDataValue":12}   XXX  )"s);

    ValidateNoTrailingDataStruct    data;
    bool ok = static_cast<bool>(stream >> jsonImporter(data, ParserConfig{}.setValidateNoTrailingData()));

    EXPECT_FALSE(ok);
    EXPECT_EQ(12, data.validateNoTrailingDataValue);
}


