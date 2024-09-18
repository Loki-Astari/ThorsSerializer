#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "test/SerializeTest.h"
#include "Serialize.h"
#include "Traits.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include "SerUtil.h"
#include <memory>
#include <iostream>


using namespace std::string_literals;
using namespace ThorsAnvil::Serialize;
using namespace std;

namespace Issue49
{
    enum class FloatFormat {scientific = 1,fixed = 2,hex = 4,general = fixed | scientific};
}

TEST(Issue49TestString, JsonStreamScientific)
{
    std::string   stream;

    Issue49::FloatFormat    testData = Issue49::FloatFormat::scientific;
    stream << ThorsAnvil::Serialize::jsonExporter(testData, false);

    std::string result = stream;
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ("\"scientific\"", result);
}
TEST(Issue49TestString, JsonStreamFixed)
{
    std::string   stream;

    Issue49::FloatFormat    testData = Issue49::FloatFormat::fixed;
    stream << ThorsAnvil::Serialize::jsonExporter(testData, false);

    std::string result = stream;
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ("\"fixed\"", result);
}
TEST(Issue49TestString, JsonStreamHex)
{
    std::string   stream;

    Issue49::FloatFormat    testData = Issue49::FloatFormat::hex;
    stream << ThorsAnvil::Serialize::jsonExporter(testData, false);

    std::string result = stream;
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ("\"hex\"", result);
}
TEST(Issue49TestString, JsonStreamGeneral)
{
    std::string   stream;

    Issue49::FloatFormat    testData = Issue49::FloatFormat::general;
    stream << ThorsAnvil::Serialize::jsonExporter(testData, false);

    std::string result = stream;
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ("\"general\"", result);
}
TEST(Issue49TestString, JsonImportScientific)
{
    std::string stream = R"("scientific")";

    Issue49::FloatFormat    testData = Issue49::FloatFormat::general;
    stream >> ThorsAnvil::Serialize::jsonImporter(testData, false);

    EXPECT_EQ(Issue49::FloatFormat::scientific, testData);
}
TEST(Issue49TestString, JsonImportFixed)
{
    std::string stream = R"("fixed")";

    Issue49::FloatFormat    testData = Issue49::FloatFormat::general;
    stream >> ThorsAnvil::Serialize::jsonImporter(testData, false);

    EXPECT_EQ(Issue49::FloatFormat::fixed, testData);
}
TEST(Issue49TestString, JsonImportHex)
{
    std::string stream = R"("hex")";

    Issue49::FloatFormat    testData = Issue49::FloatFormat::general;
    stream >> ThorsAnvil::Serialize::jsonImporter(testData, false);

    EXPECT_EQ(Issue49::FloatFormat::hex, testData);
}
TEST(Issue49TestString, JsonImportGeneral)
{
    std::string stream = R"("general")";

    Issue49::FloatFormat    testData = Issue49::FloatFormat::scientific;
    stream >> ThorsAnvil::Serialize::jsonImporter(testData, false);

    EXPECT_EQ(Issue49::FloatFormat::general, testData);
}

TEST(Issue49TestString, BsonStreamScientific)
{
    std::string   stream;

    Issue49::FloatFormat    testData = Issue49::FloatFormat::scientific;
    stream << ThorsAnvil::Serialize::bsonExporter(testData, false);

    std::string result = stream;

    EXPECT_EQ(result, "\x17\x00\x00\x00"
                      "\x02" "0\x00" "\x0B\x00\x00\x00" "scientific\x00"
                      "\x00"s);
    // NOTE OUTPUT ("\"scientific\"", result);
}
TEST(Issue49TestString, BsonStreamFixed)
{
    std::string   stream;

    Issue49::FloatFormat    testData = Issue49::FloatFormat::fixed;
    stream << ThorsAnvil::Serialize::bsonExporter(testData, false);

    std::string result = stream;

    EXPECT_EQ(result, "\x12\x00\x00\x00"
                      "\x02" "0\x00" "\x06\x00\x00\x00" "fixed\x00"
                      "\x00"s);
    // NOTE OUTPUT ("\"fixed\"", result);
}
TEST(Issue49TestString, BsonStreamHex)
{
    std::string   stream;

    Issue49::FloatFormat    testData = Issue49::FloatFormat::hex;
    stream << ThorsAnvil::Serialize::bsonExporter(testData, false);

    std::string result = stream;

    EXPECT_EQ(result, "\x10\x00\x00\x00"
                      "\x02" "0\x00" "\x04\x00\x00\x00" "hex\x00"
                      "\x00"s);
    // NOTE OUTPUT ("\"hex\"", result);
}
TEST(Issue49TestString, BsonStreamGeneral)
{
    std::string   stream;

    Issue49::FloatFormat    testData = Issue49::FloatFormat::general;
    stream << ThorsAnvil::Serialize::bsonExporter(testData, false);

    std::string result = stream;

    EXPECT_EQ(result, "\x14\x00\x00\x00"
                      "\x02" "0\x00" "\x08\x00\x00\x00" "general\x00"
                      "\x00"s);
    // NOTE OUTPUT ("\"general\"", result);
}
TEST(Issue49TestString, BsonImportScientific)
{
    //NOTE INPUT  = R"("scientific")";
    std::string stream = "\x17\x00\x00\x00"
                        "\x02" "0\x00" "\x0B\x00\x00\x00" "scientific\x00"
                        "\x00"s;

    Issue49::FloatFormat    testData = Issue49::FloatFormat::general;
    stream >> ThorsAnvil::Serialize::bsonImporter(testData, false);

    EXPECT_EQ(Issue49::FloatFormat::scientific, testData);
}
TEST(Issue49TestString, BsonImportFixed)
{
    //NOTE INPUT  = R"("fixed")";
    std::string stream = "\x12\x00\x00\x00"
                        "\x02" "0\x00" "\x06\x00\x00\x00" "fixed\x00"
                        "\x00"s;

    Issue49::FloatFormat    testData = Issue49::FloatFormat::general;
    stream >> ThorsAnvil::Serialize::bsonImporter(testData, false);

    EXPECT_EQ(Issue49::FloatFormat::fixed, testData);
}
TEST(Issue49TestString, BsonImportHex)
{
    //NOTE INPUT  = R"("hex")";
    std::string stream = "\x10\x00\x00\x00"
                        "\x02" "0\x00" "\x04\x00\x00\x00" "hex\x00"
                        "\x00"s;

    Issue49::FloatFormat    testData = Issue49::FloatFormat::general;
    stream >> ThorsAnvil::Serialize::bsonImporter(testData, false);

    EXPECT_EQ(Issue49::FloatFormat::hex, testData);
}
TEST(Issue49TestString, BsonImportGeneral)
{
    //NOTE INPUT  = R"("general")";
    std::string stream = "\x14\x00\x00\x00"
                        "\x02" "0\x00" "\x08\x00\x00\x00" "general\x00"
                        "\x00"s;

    Issue49::FloatFormat    testData = Issue49::FloatFormat::scientific;
    stream >> ThorsAnvil::Serialize::bsonImporter(testData, false);

    EXPECT_EQ(Issue49::FloatFormat::general, testData);
}




