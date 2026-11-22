#include "gtest/gtest.h"
#include <sstream>
#include "JsonThor.h"



TEST(AnyBlockTest, BoolTrue)
{
    std::stringstream               stream("true");
    ThorsAnvil::Serialize::AnyBlock any;

    stream >> ThorsAnvil::Serialize::jsonImporter(any);

    EXPECT_EQ("true", any.getString());
}

TEST(AnyBlockTest, AnyMoveOut)
{
    std::stringstream               stream("false");
    ThorsAnvil::Serialize::AnyBlock any;

    stream >> ThorsAnvil::Serialize::jsonImporter(any);

    std::string extracted = std::move(any).getString();
    EXPECT_EQ("false", extracted);
    EXPECT_EQ("",      any.getString());
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
TEST(AnyBlockTest, Reset)
{
    std::stringstream               stream(R"([true, false, null, 12, 12.75, {"val":12}])");
    ThorsAnvil::Serialize::AnyBlock any;

    stream >> ThorsAnvil::Serialize::jsonImporter(any);
    any.reset();

    EXPECT_EQ("", any.getString());
}
TEST(AnyBlockTest, OutputObject)
{
    std::stringstream               stream(R"({"key1":"string","key2":true,"key3":false,"key4":null,"key5":12,"key6":12.75,"key7":{"val":1}})");
    ThorsAnvil::Serialize::AnyBlock any;

    stream >> ThorsAnvil::Serialize::jsonImporter(any);

    std::stringstream               output;
    output << ThorsAnvil::Serialize::jsonExporter(any);
    std::string anyOutput = output.str();
    anyOutput.erase(std::remove_if(std::begin(anyOutput), std::end(anyOutput), [](unsigned char x){return std::isspace(x);}), std::end(anyOutput));

    EXPECT_EQ(R"({"key1":"string","key2":true,"key3":false,"key4":null,"key5":12,"key6":12.75,"key7":{"val":1}})", anyOutput);
}
struct JsonRPCInput
{
    std::string                         jsonrpc;
    std::optional<long>                 id;         // id can be number / string / null  (not support incoming Id's with String).
                                                    // Note: A notification can be sent either way and does not have an id.
                                                    //       As a result there is no response for a notification.
    std::optional<std::string>                                  method;
    std::optional<ThorsAnvil::Serialize::AnyBlock>              params;
    std::optional<ThorsAnvil::Serialize::AnyBlock>              result;
    std::optional<ThorsAnvil::Serialize::AnyBlock>              error;
};

ThorsAnvil_MakeTrait(JsonRPCInput,                  jsonrpc, id, method, params, result, error);
TEST(AnyBlockTest, JsonRPC)
{
    std::string                     stream{R"({"jsonrpc":"2.0","id":1,"result":{"resultType":"complete","supportedVersions":["2026-07-28"],"capabilities":{"prompts":{"listChanged":true},"tools":{"listChanged":true},"resources":{"listChanged":true}},"instructions":"This is a test server dont do anything","ttlMs":60000,"cacheScope":"public","_meta":{"io.modelcontextprotocol/serverInfo":{"icons":[{"src":"A","mimeType":"a/a1","sizes":["1","2","3"],"theme":"dark"},{"src":"B","mimeType":"b/b2","sizes":["4","5","6"],"theme":"light"},{"src":"C","mimeType":"c/c3","sizes":["7","8","9"],"theme":"light"}],"name":"Test Server","title":"Serve Test Data","version":"1.2.3.4","description":"A server that we can test","websiteUrl":"A web"}}}})"};
    JsonRPCInput                    jsonrpc;
    stream >> ThorsAnvil::Serialize::jsonImporter(jsonrpc);
}

