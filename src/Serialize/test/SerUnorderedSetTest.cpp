#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include "SerUtil.h"
#include <algorithm>

namespace TS = ThorsAnvil::Serialize;

TEST(SerUnorderedSetTest, Jsonserialize)
{
    std::unordered_set<int>  data{24,11,2};

    std::stringstream       stream;
    stream << TS::jsonExporter(data, false);
    std::string result = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    // unordered set can print in any order
    // so it should be one of these
    bool test = result == R"([2,11,24])"
             || result == R"([2,24,11])"
             || result == R"([11,2,24])"
             || result == R"([11,24,2])"
             || result == R"([24,2,11])"
             || result == R"([24,11,2])";

    EXPECT_TRUE(test);
}

TEST(SerUnorderedSetTest, JsondeSerialize)
{
    std::unordered_set<int>  data;

    std::stringstream       stream(R"([5,6,8,101,123])");
    stream >> TS::jsonImporter(data, false);

    EXPECT_TRUE(data.find(5) != data.end());
    EXPECT_TRUE(data.find(6) != data.end());
    EXPECT_TRUE(data.find(8) != data.end());
    EXPECT_TRUE(data.find(101) != data.end());
    EXPECT_TRUE(data.find(123) != data.end());
}

TEST(SerUnorderedSetTest, Bsonserialize)
{
    std::unordered_set<int>  data{24,11,2};

    std::stringstream       stream;
    stream << TS::bsonExporter(data, false);
    std::string result = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    // unordered set can print in any order
    // so it should be one of these
    bool test = result == R"([2,11,24])"
             || result == R"([2,24,11])"
             || result == R"([11,2,24])"
             || result == R"([11,24,2])"
             || result == R"([24,2,11])"
             || result == R"([24,11,2])";

    EXPECT_TRUE(test);
}

TEST(SerUnorderedSetTest, BsondeSerialize)
{
    std::unordered_set<int>  data;

    std::stringstream       stream(R"([5,6,8,101,123])");
    stream >> TS::bsonImporter(data, false);

    EXPECT_TRUE(data.find(5) != data.end());
    EXPECT_TRUE(data.find(6) != data.end());
    EXPECT_TRUE(data.find(8) != data.end());
    EXPECT_TRUE(data.find(101) != data.end());
    EXPECT_TRUE(data.find(123) != data.end());
}

