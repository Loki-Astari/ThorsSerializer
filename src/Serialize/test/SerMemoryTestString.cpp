#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include "SerUtil.h"
#include <algorithm>

namespace TS = ThorsAnvil::Serialize;

TEST(SerMemoryTestString, Jsonserialize)
{
    std::pair<int, double>  data(56, 78.901);

    std::string             stream;
    stream << TS::jsonExporter(data, false);
    std::string result = stream;
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ(result, R"({"first":56,"second":78.901000})");
}

TEST(SerMemoryTestString, JsondeSerialize)
{
    std::pair<int, double>  data;

    std::string     stream(R"({"first":22,"second":45.67})");
    stream >> TS::jsonImporter(data, false);

    EXPECT_EQ(data.first, 22);
    EXPECT_EQ(data.second, 45.67);
}

TEST(SerMemoryTestString, Bsonserialize)
{
    std::pair<int, double>  data(56, 78.901);

    std::string             stream;
    stream << TS::bsonExporter(data, false);
    std::string result = stream;

    static const char expectedRaw[]
                = "\x20\x00\x00\x00"
                  "\x10" "first\x00"  "\x38\x00\x00\x00"
                  "\x01" "second\x00" "\x8b\x6c\xe7\xfb\xa9\xb9\x53\x40"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(result, expected);
    //NOTE OUTPUT (result, R"({"first":56,"second":78.901})");
}

TEST(SerMemoryTestString, BsondeSerialize)
{
    std::pair<int, double>  data;

    //NOTE INPUT (R"({"first":22,"second":45.67})");
    static const char inputRaw[]
                = "\x20\x00\x00\x00"
                  "\x10" "first\x00"  "\x16\x00\x00\x00"
                  "\x01" "second\x00" "\xf6\x28\x5c\x8f\xc2\xd5\x46\x40"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::string     stream(input);
    stream >> TS::bsonImporter(data, false);

    EXPECT_EQ(data.first, 22);
    EXPECT_EQ(data.second, 45.67);
}

