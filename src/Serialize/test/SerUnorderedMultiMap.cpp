#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonThor.h"
#include "SerUtil.h"
#include <algorithm>

namespace TS = ThorsAnvil::Serialize;

TEST(SerUnorderedMultiMapTest, serialize)
{
    std::unordered_multimap<int, double>  data;
    data.insert(std::make_pair(56, 78.901));
    data.insert(std::make_pair(56, 901));

    std::stringstream       stream;
    stream << TS::jsonExporter(data);
    std::string result = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    bool test = result == R"([{"first":56,"second":78.901},{"first":56,"second":901}])"
             || result == R"([{"first":56,"second":901},{"first":56,"second":78.901}])";

    EXPECT_TRUE(test);
}

TEST(SerUnorderedMultiMapTest, deSerialize)
{
    std::unordered_multimap<int, double>  data;

    std::stringstream       stream(R"([{"first":64,"second":12}, {"first":118,"second":14}, {"first":118,"second": 112}])");
    stream >> TS::jsonImporter(data, false);

    EXPECT_TRUE(data.find(64) != data.end());
    EXPECT_TRUE(data.find(118) != data.end());
    EXPECT_EQ(data.count(118), 2);
}

TEST(SerUnorderedMultiMapTest, serializeStringKey)
{
    std::unordered_multimap<std::string, double>  data;
    data.insert(std::make_pair("AStringKey", 78.902));
    data.insert(std::make_pair("TestValue",  22.903));
    data.insert(std::make_pair("TestValue",  903));

    std::stringstream       stream;
    stream << TS::jsonExporter(data, false);
    std::string result = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    bool test =  result == R"({"AStringKey":78.902,"TestValue":22.903,"TestValue":903})"
              || result == R"({"AStringKey":78.902,"TestValue":903,"TestValue":22.903})"
              || result == R"({"TestValue":22.903,"AStringKey":78.902,"TestValue":903})"
              || result == R"({"TestValue":22.903,"TestValue":903,"AStringKey":78.902})"
              || result == R"({"TestValue":903,"AStringKey":78.902,"TestValue":22.903})"
              || result == R"({"TestValue":903,"TestValue":22.903,"AStringKey":78.902})";

    EXPECT_TRUE(test);
}

TEST(SerUnorderedMultiMapTest, deSerializeStringKey)
{
    std::unordered_multimap<std::string, bool>  data;

    std::stringstream       stream(R"({"OneFileDay":true, "TheLastStand":false, "OfMiceAndMen":true, "1":true, "1":false})");
    stream >> TS::jsonImporter(data, false);

    EXPECT_TRUE(data.find("OneFileDay") != data.end());
    EXPECT_TRUE(data.find("TheLastStand") != data.end());
    EXPECT_TRUE(data.find("OfMiceAndMen") != data.end());
    EXPECT_TRUE(data.find("1") != data.end());
    EXPECT_EQ(data.count("1"), 2);
}

