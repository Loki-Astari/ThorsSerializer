#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonThor.h"
#include "SerUtil.h"
#include <algorithm>

namespace TS = ThorsAnvil::Serialize;

TEST(SetUnorderedMapTest, serialize)
{
    std::unordered_map<int, double>  data;
    data[56]    = 78.901;

    std::stringstream       stream;
    stream << TS::jsonExporter(data, false);
    std::string result = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ(result, R"([{"first":56,"second":78.901}])");
}

TEST(SetUnorderedMapTest, deSerialize)
{
    std::unordered_map<int, double>  data;

    std::stringstream       stream(R"([{"first":64,"second":12}, {"first":118,"second":14}])");
    stream >> TS::jsonImporter(data, false);

    EXPECT_EQ(data[64],  12);
    EXPECT_EQ(data[118], 14);
}

TEST(SetUnorderedMapTest, serializeStringKey)
{
    std::unordered_map<std::string, double>  data;
    data["AStringKey"]      = 78.902;
    data["TestValue"]       = 22.903;

    std::stringstream       stream;
    stream << TS::jsonExporter(data, false);
    std::string result = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    bool test = result == R"({"AStringKey":78.902,"TestValue":22.903})"
             || result == R"({"TestValue":22.903,"AStringKey":78.902})";
    EXPECT_TRUE(test);
}

TEST(SetUnorderedMapTest, deSerializeStringKey)
{
    std::unordered_map<std::string, bool>  data;

    std::stringstream       stream(R"({"OneFileDay":true, "TheLastStand":false, "OfMiceAndMen":true})");
    stream >> TS::jsonImporter(data, false);

    EXPECT_EQ(data["OneFileDay"],   true);
    EXPECT_EQ(data["TheLastStand"], false);
    EXPECT_EQ(data["OfMiceAndMen"], true);
}

