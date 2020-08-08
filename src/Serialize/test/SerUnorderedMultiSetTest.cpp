#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include "SerUtil.h"
#include <algorithm>

namespace TS = ThorsAnvil::Serialize;

TEST(SerUnorderedMultisetTest, Jsonserialize)
{
    std::unordered_multiset<int>  data{24,8,11,2,2,2};

    std::stringstream       stream;
    stream << TS::jsonExporter(data, false);
    std::string result = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    bool test = result == R"([2,2,2,8,11,24])"
             || result == R"([2,2,8,2,11,24])"
             || result == R"([2,2,8,11,2,24])"
             || result == R"([2,2,8,11,24,2])"
             || result == R"([2,8,2,11,24,2])"
             || result == R"([2,8,11,2,24,2])"
             || result == R"([2,8,11,24,2,2])"
             || result == R"([8,2,11,24,2,2])"
             || result == R"([8,11,2,24,2,2])"
             || result == R"([8,11,24,2,2,2])"
             || result == R"([8,2,2,2,11,24])"
             || result == R"([8,2,2,11,2,24])"
             || result == R"([8,2,2,11,24,2])"
             || result == R"([8,2,11,2,24,2])"
             || result == R"([8,11,2,2,2,24])"
             || result == R"([8,11,2,2,24,2])"

             || result == R"([2,2,2,8,24,11])"
             || result == R"([2,2,8,2,24,11])"
             || result == R"([2,2,8,24,2,11])"
             || result == R"([2,2,8,24,11,2])"
             || result == R"([2,8,2,24,11,2])"
             || result == R"([2,8,24,2,11,2])"
             || result == R"([2,8,24,11,2,2])"
             || result == R"([8,2,24,11,2,2])"
             || result == R"([8,24,2,11,2,2])"
             || result == R"([8,24,11,2,2,2])"
             || result == R"([8,2,2,2,24,11])"
             || result == R"([8,2,2,24,2,11])"
             || result == R"([8,2,2,24,11,2])"
             || result == R"([8,2,24,2,11,2])"
             || result == R"([8,24,2,2,2,11])"
             || result == R"([8,24,2,2,11,2])"

             || result == R"([2,2,2,11,8,24])"
             || result == R"([2,2,11,2,8,24])"
             || result == R"([2,2,11,8,2,24])"
             || result == R"([2,2,11,8,24,2])"
             || result == R"([2,11,2,8,24,2])"
             || result == R"([2,11,8,2,24,2])"
             || result == R"([2,11,8,24,2,2])"
             || result == R"([11,2,8,24,2,2])"
             || result == R"([11,8,2,24,2,2])"
             || result == R"([11,8,24,2,2,2])"
             || result == R"([11,2,2,2,8,24])"
             || result == R"([11,2,2,8,2,24])"
             || result == R"([11,2,2,8,24,2])"
             || result == R"([11,2,8,2,24,2])"
             || result == R"([11,8,2,2,2,24])"
             || result == R"([11,8,2,2,24,2])"

             || result == R"([2,2,2,24,11,8])"
             || result == R"([2,2,24,2,11,8])"
             || result == R"([2,2,24,11,2,8])"
             || result == R"([2,2,24,11,8,2])"
             || result == R"([2,24,2,11,8,2])"
             || result == R"([2,24,11,2,8,2])"
             || result == R"([2,24,11,8,2,2])"
             || result == R"([24,2,11,8,2,2])"
             || result == R"([24,11,2,8,2,2])"
             || result == R"([24,11,8,2,2,2])"
             || result == R"([24,2,2,2,11,8])"
             || result == R"([24,2,2,11,2,8])"
             || result == R"([24,2,2,11,8,2])"
             || result == R"([24,2,11,2,8,2])"
             || result == R"([24,11,2,2,2,8])"
             || result == R"([24,11,2,2,8,2])"

             || result == R"([2,2,2,11,24,8])"
             || result == R"([2,2,11,2,24,8])"
             || result == R"([2,2,11,24,2,8])"
             || result == R"([2,2,11,24,8,2])"
             || result == R"([2,11,2,24,8,2])"
             || result == R"([2,11,24,2,8,2])"
             || result == R"([2,11,24,8,2,2])"
             || result == R"([11,2,24,8,2,2])"
             || result == R"([11,24,2,8,2,2])"
             || result == R"([11,24,8,2,2,2])"
             || result == R"([11,2,2,2,24,8])"
             || result == R"([11,2,2,24,2,8])"
             || result == R"([11,2,2,24,8,2])"
             || result == R"([11,2,24,2,8,2])"
             || result == R"([11,24,2,2,2,8])"
             || result == R"([11,24,2,2,8,2])"

             || result == R"([2,2,2,24,8,11])"
             || result == R"([2,2,24,2,8,11])"
             || result == R"([2,2,24,8,2,11])"
             || result == R"([2,2,24,8,11,2])"
             || result == R"([2,24,2,8,11,2])"
             || result == R"([2,24,8,2,11,2])"
             || result == R"([2,24,8,11,2,2])"
             || result == R"([24,2,8,11,2,2])"
             || result == R"([24,8,2,11,2,2])"
             || result == R"([24,8,11,2,2,2])"
             || result == R"([24,2,2,2,8,11])"
             || result == R"([24,2,2,8,2,11])"
             || result == R"([24,2,2,8,11,2])"
             || result == R"([24,2,8,2,11,2])"
             || result == R"([24,8,2,2,2,11])"
             || result == R"([24,8,2,2,11,2])";
    EXPECT_TRUE(test);

}

TEST(SerUnorderedMultisetTest, JsondeSerialize)
{
    std::unordered_multiset<int>  data;

    std::stringstream       stream(R"([5,6,8,8,101,123])");
    stream >> TS::jsonImporter(data, false);

    EXPECT_TRUE(data.find(5) != data.end());
    EXPECT_TRUE(data.find(6) != data.end());
    EXPECT_TRUE(data.find(8) != data.end());
    EXPECT_TRUE(data.find(101) != data.end());
    EXPECT_TRUE(data.find(123) != data.end());
    EXPECT_EQ(data.count(8), 2);
}

TEST(SerUnorderedMultisetTest, Bsonserialize)
{
    std::unordered_multiset<int>  data{24,8,11,2,2,2};

    std::stringstream       stream;
    stream << TS::bsonExporter(data, false);
    std::string result = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    bool test = result == R"([2,2,2,8,11,24])"
             || result == R"([2,2,8,2,11,24])"
             || result == R"([2,2,8,11,2,24])"
             || result == R"([2,2,8,11,24,2])"
             || result == R"([2,8,2,11,24,2])"
             || result == R"([2,8,11,2,24,2])"
             || result == R"([2,8,11,24,2,2])"
             || result == R"([8,2,11,24,2,2])"
             || result == R"([8,11,2,24,2,2])"
             || result == R"([8,11,24,2,2,2])"
             || result == R"([8,2,2,2,11,24])"
             || result == R"([8,2,2,11,2,24])"
             || result == R"([8,2,2,11,24,2])"
             || result == R"([8,2,11,2,24,2])"
             || result == R"([8,11,2,2,2,24])"
             || result == R"([8,11,2,2,24,2])"

             || result == R"([2,2,2,8,24,11])"
             || result == R"([2,2,8,2,24,11])"
             || result == R"([2,2,8,24,2,11])"
             || result == R"([2,2,8,24,11,2])"
             || result == R"([2,8,2,24,11,2])"
             || result == R"([2,8,24,2,11,2])"
             || result == R"([2,8,24,11,2,2])"
             || result == R"([8,2,24,11,2,2])"
             || result == R"([8,24,2,11,2,2])"
             || result == R"([8,24,11,2,2,2])"
             || result == R"([8,2,2,2,24,11])"
             || result == R"([8,2,2,24,2,11])"
             || result == R"([8,2,2,24,11,2])"
             || result == R"([8,2,24,2,11,2])"
             || result == R"([8,24,2,2,2,11])"
             || result == R"([8,24,2,2,11,2])"

             || result == R"([2,2,2,11,8,24])"
             || result == R"([2,2,11,2,8,24])"
             || result == R"([2,2,11,8,2,24])"
             || result == R"([2,2,11,8,24,2])"
             || result == R"([2,11,2,8,24,2])"
             || result == R"([2,11,8,2,24,2])"
             || result == R"([2,11,8,24,2,2])"
             || result == R"([11,2,8,24,2,2])"
             || result == R"([11,8,2,24,2,2])"
             || result == R"([11,8,24,2,2,2])"
             || result == R"([11,2,2,2,8,24])"
             || result == R"([11,2,2,8,2,24])"
             || result == R"([11,2,2,8,24,2])"
             || result == R"([11,2,8,2,24,2])"
             || result == R"([11,8,2,2,2,24])"
             || result == R"([11,8,2,2,24,2])"

             || result == R"([2,2,2,24,11,8])"
             || result == R"([2,2,24,2,11,8])"
             || result == R"([2,2,24,11,2,8])"
             || result == R"([2,2,24,11,8,2])"
             || result == R"([2,24,2,11,8,2])"
             || result == R"([2,24,11,2,8,2])"
             || result == R"([2,24,11,8,2,2])"
             || result == R"([24,2,11,8,2,2])"
             || result == R"([24,11,2,8,2,2])"
             || result == R"([24,11,8,2,2,2])"
             || result == R"([24,2,2,2,11,8])"
             || result == R"([24,2,2,11,2,8])"
             || result == R"([24,2,2,11,8,2])"
             || result == R"([24,2,11,2,8,2])"
             || result == R"([24,11,2,2,2,8])"
             || result == R"([24,11,2,2,8,2])"

             || result == R"([2,2,2,11,24,8])"
             || result == R"([2,2,11,2,24,8])"
             || result == R"([2,2,11,24,2,8])"
             || result == R"([2,2,11,24,8,2])"
             || result == R"([2,11,2,24,8,2])"
             || result == R"([2,11,24,2,8,2])"
             || result == R"([2,11,24,8,2,2])"
             || result == R"([11,2,24,8,2,2])"
             || result == R"([11,24,2,8,2,2])"
             || result == R"([11,24,8,2,2,2])"
             || result == R"([11,2,2,2,24,8])"
             || result == R"([11,2,2,24,2,8])"
             || result == R"([11,2,2,24,8,2])"
             || result == R"([11,2,24,2,8,2])"
             || result == R"([11,24,2,2,2,8])"
             || result == R"([11,24,2,2,8,2])"

             || result == R"([2,2,2,24,8,11])"
             || result == R"([2,2,24,2,8,11])"
             || result == R"([2,2,24,8,2,11])"
             || result == R"([2,2,24,8,11,2])"
             || result == R"([2,24,2,8,11,2])"
             || result == R"([2,24,8,2,11,2])"
             || result == R"([2,24,8,11,2,2])"
             || result == R"([24,2,8,11,2,2])"
             || result == R"([24,8,2,11,2,2])"
             || result == R"([24,8,11,2,2,2])"
             || result == R"([24,2,2,2,8,11])"
             || result == R"([24,2,2,8,2,11])"
             || result == R"([24,2,2,8,11,2])"
             || result == R"([24,2,8,2,11,2])"
             || result == R"([24,8,2,2,2,11])"
             || result == R"([24,8,2,2,11,2])";
    EXPECT_TRUE(test);

}

TEST(SerUnorderedMultisetTest, BsondeSerialize)
{
    std::unordered_multiset<int>  data;

    std::stringstream       stream(R"([5,6,8,8,101,123])");
    stream >> TS::bsonImporter(data, false);

    EXPECT_TRUE(data.find(5) != data.end());
    EXPECT_TRUE(data.find(6) != data.end());
    EXPECT_TRUE(data.find(8) != data.end());
    EXPECT_TRUE(data.find(101) != data.end());
    EXPECT_TRUE(data.find(123) != data.end());
    EXPECT_EQ(data.count(8), 2);
}

