#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonThor.h"
#include "Serialize.h"
#include "test/SerializeTest.h"
#include <algorithm>

std::string stripspace(std::string const& value)
{
    std::string  result(value);
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return std::isspace(x);}), std::end(result));
    return result;
}

TEST(SerializeEnum, RedGreenBlueAtRed)
{
    SerializeTest::RGB      enumHolder {SerializeTest::Red};
    std::stringstream   str;
    str << ThorsAnvil::Serialize::jsonExporter(enumHolder, false);

    EXPECT_EQ(R"("Red")", stripspace(str.str()));
}
TEST(SerializeEnum, RedGreenBlueAtGreen)
{
    SerializeTest::RGB      enumHolder {SerializeTest::Green};
    std::stringstream   str;
    str << ThorsAnvil::Serialize::jsonExporter(enumHolder, false);

    EXPECT_EQ(R"("Green")", stripspace(str.str()));
}
TEST(SerializeEnum, RedGreenBlueAtBlue)
{
    SerializeTest::RGB      enumHolder {SerializeTest::Blue};
    std::stringstream   str;
    str << ThorsAnvil::Serialize::jsonExporter(enumHolder, false);

    EXPECT_EQ(R"("Blue")", stripspace(str.str()));
}
TEST(DeSerializeEnum, RefGreenBlueFromRed)
{
    std::stringstream   str(R"("Red")");
    SerializeTest::RGB     enumHolder {SerializeTest::Green};

    str >> ThorsAnvil::Serialize::jsonImporter(enumHolder, false);
    EXPECT_EQ(SerializeTest::Red, enumHolder);
}
TEST(DeSerializeEnum, RefGreenBlueFromGreen)
{
    std::stringstream   str(R"("Green")");
    SerializeTest::RGB     enumHolder {SerializeTest::Red};

    str >> ThorsAnvil::Serialize::jsonImporter(enumHolder, false);
    EXPECT_EQ(SerializeTest::Green, enumHolder);
}
TEST(DeSerializeEnum, RefGreenBlueFromBlue)
{
    std::stringstream   str(R"("Blue")");
    SerializeTest::RGB     enumHolder {SerializeTest::Green};

    str >> ThorsAnvil::Serialize::jsonImporter(enumHolder, false);
    EXPECT_EQ(SerializeTest::Blue, enumHolder);
}
TEST(SerializeEnum, SerEnumInContainer)
{
    SerializeTest::EumHolder  holder { SerializeTest::Red };

    std::stringstream   str;

    str << ThorsAnvil::Serialize::jsonExporter(holder, false);
    EXPECT_EQ(R"({"value":"Red"})", stripspace(str.str()));
}
TEST(SerializeEnum, DeSerEnumInContainer)
{
    SerializeTest::EumHolder  holder { SerializeTest::Red };
    std::stringstream   str(R"({"value": "Green"})");

    str >> ThorsAnvil::Serialize::jsonImporter(holder, false);
    EXPECT_EQ(SerializeTest::Green, holder.value);
}


