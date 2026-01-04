#include <sstream>
#include "gtest/gtest.h"
#include "SerUtil.h"
#include "JsonThor.h"



TEST(AnyBlockTest, BoolTrue)
{
    std::stringstream               stream("true");
    ThorsAnvil::Serialize::AnyBlock any;

    stream >> ThorsAnvil::Serialize::jsonImporter(any);

    EXPECT_EQ("true", any.getString());
}
TEST(AnyBlockTest, BoolFalse)
{
    std::stringstream               stream("false");
    ThorsAnvil::Serialize::AnyBlock any;

    stream >> ThorsAnvil::Serialize::jsonImporter(any);

    EXPECT_EQ("false", any.getString());
}
TEST(AnyBlockTest, Int)
{
    std::stringstream               stream("12");
    ThorsAnvil::Serialize::AnyBlock any;

    stream >> ThorsAnvil::Serialize::jsonImporter(any);

    EXPECT_EQ("12", any.getString());
}
TEST(AnyBlockTest, Real)
{
    std::stringstream               stream("12.75");
    ThorsAnvil::Serialize::AnyBlock any;

    stream >> ThorsAnvil::Serialize::jsonImporter(any);

    EXPECT_EQ("12.75", any.getString());
}
TEST(AnyBlockTest, String)
{
    std::stringstream               stream("\"This is a string\"");
    ThorsAnvil::Serialize::AnyBlock any;

    stream >> ThorsAnvil::Serialize::jsonImporter(any);

    EXPECT_EQ("\"This is a string\"", any.getString());
}
TEST(AnyBlockTest, Null)
{
    std::stringstream               stream("null");
    ThorsAnvil::Serialize::AnyBlock any;

    stream >> ThorsAnvil::Serialize::jsonImporter(any);

    EXPECT_EQ("null", any.getString());
}
TEST(AnyBlockTest, Object)
{
    std::stringstream               stream(R"({  "key1": "string",  "key2": true, "key3":false, "key4":null, "key5":12, "key6":12.75, "key7":{"val":1}})");
    ThorsAnvil::Serialize::AnyBlock any;

    stream >> ThorsAnvil::Serialize::jsonImporter(any);

    EXPECT_EQ(R"({"key1":"string","key2":true,"key3":false,"key4":null,"key5":12,"key6":12.75,"key7":{"val":1}})", any.getString());
}
TEST(AnyBlockTest, Array)
{
    std::stringstream               stream(R"([true, false, null, 12, 12.75, {"val":12}])");
    ThorsAnvil::Serialize::AnyBlock any;

    stream >> ThorsAnvil::Serialize::jsonImporter(any);

    EXPECT_EQ(R"([true,false,null,12,12.75,{"val":12}])", any.getString());
}

