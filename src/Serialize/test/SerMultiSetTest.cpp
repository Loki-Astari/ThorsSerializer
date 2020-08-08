#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include "SerUtil.h"
#include <algorithm>

namespace TS = ThorsAnvil::Serialize;

TEST(SerMultisetTest, Jsonserialize)
{
    std::multiset<int>  data{34,24,8,11,2,2,2};

    std::stringstream       stream;
    stream << TS::jsonExporter(data, false);
    std::string result = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ(result, R"([2,2,2,8,11,24,34])");
}

TEST(SerMultisetTest, JsonbeSerialize)
{
    std::multiset<int>  data;

    std::stringstream       stream(R"([5,6,8,8,101,123])");
    stream >> TS::jsonImporter(data, false);

    EXPECT_TRUE(data.find(5) != data.end());
    EXPECT_TRUE(data.find(6) != data.end());
    EXPECT_TRUE(data.find(8) != data.end());
    EXPECT_TRUE(data.find(101) != data.end());
    EXPECT_TRUE(data.find(123) != data.end());
    EXPECT_EQ(data.count(8), 2);
}

TEST(SerMultisetTest, Bsonserialize)
{
    std::multiset<int>  data{34,24,8,11,2,2,2};

    std::stringstream       stream;
    stream << TS::bsonExporter(data, false);
    std::string result = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ(result, R"([2,2,2,8,11,24,34])");
}

TEST(SerMultisetTest, BsonbeSerialize)
{
    std::multiset<int>  data;

    std::stringstream       stream(R"([5,6,8,8,101,123])");
    stream >> TS::bsonImporter(data, false);

    EXPECT_TRUE(data.find(5) != data.end());
    EXPECT_TRUE(data.find(6) != data.end());
    EXPECT_TRUE(data.find(8) != data.end());
    EXPECT_TRUE(data.find(101) != data.end());
    EXPECT_TRUE(data.find(123) != data.end());
    EXPECT_EQ(data.count(8), 2);
}

