
#include "gtest/gtest.h"
#include "JsonThor.h"
#include "Serialize.h"
#include "test/SerializeTest.h"

std::string stripspace(std::string const& value)
{
    std::string  result(value);
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return std::isspace(x);}), std::end(result));
    return result;
}

TEST(SerializeEnum, RedGreenBlueAtRed)
{
    RGB      enumHolder {Red};
    std::stringstream   str;
    str << ThorsAnvil::Serialize::jsonExport(enumHolder);

    EXPECT_EQ(R"("Red")", stripspace(str.str()));
}
TEST(SerializeEnum, RedGreenBlueAtGreen)
{
    RGB      enumHolder {Green};
    std::stringstream   str;
    str << ThorsAnvil::Serialize::jsonExport(enumHolder);

    EXPECT_EQ(R"("Green")", stripspace(str.str()));
}
TEST(SerializeEnum, RedGreenBlueAtBlue)
{
    RGB      enumHolder {Blue};
    std::stringstream   str;
    str << ThorsAnvil::Serialize::jsonExport(enumHolder);

    EXPECT_EQ(R"("Blue")", stripspace(str.str()));
}
TEST(DeSerializeEnum, RefGreenBlueFromRed)
{
    std::stringstream   str(R"("Red")");
    RGB     enumHolder {Green};

    str >> ThorsAnvil::Serialize::jsonImport(enumHolder);
    EXPECT_EQ(Red, enumHolder);
}
TEST(DeSerializeEnum, RefGreenBlueFromGreen)
{
    std::stringstream   str(R"("Green")");
    RGB     enumHolder {Red};

    str >> ThorsAnvil::Serialize::jsonImport(enumHolder);
    EXPECT_EQ(Green, enumHolder);
}
TEST(DeSerializeEnum, RefGreenBlueFromBlue)
{
    std::stringstream   str(R"("Blue")");
    RGB     enumHolder {Green};

    str >> ThorsAnvil::Serialize::jsonImport(enumHolder);
    EXPECT_EQ(Blue, enumHolder);
}
TEST(SerializeEnum, SerEnumInContainer)
{
    EumHolder  holder { Red };

    std::stringstream   str;

    str << ThorsAnvil::Serialize::jsonExport(holder);
    EXPECT_EQ(R"({"value":"Red"})", stripspace(str.str()));
}
TEST(SerializeEnum, DeSerEnumInContainer)
{
    EumHolder  holder { Red };
    std::stringstream   str(R"({"value": "Green"})");

    str >> ThorsAnvil::Serialize::jsonImport(holder);
    EXPECT_EQ(Green, holder.value);
}


