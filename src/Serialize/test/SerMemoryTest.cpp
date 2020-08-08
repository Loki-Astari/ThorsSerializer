#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include "SerUtil.h"
#include <algorithm>

namespace TS = ThorsAnvil::Serialize;

TEST(SerMemoryTest, Jsonserialize)
{
    std::pair<int, double>  data(56, 78.901);

    std::stringstream       stream;
    stream << TS::jsonExporter(data, false);
    std::string result = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ(result, R"({"first":56,"second":78.901})");
}

TEST(SerMemoryTest, JsondeSerialize)
{
    std::pair<int, double>  data;

    std::stringstream       stream(R"({"first":22,"second":45.67})");
    stream >> TS::jsonImporter(data, false);

    EXPECT_EQ(data.first, 22);
    EXPECT_EQ(data.second, 45.67);
}

TEST(SerMemoryTest, Bsonserialize)
{
    std::pair<int, double>  data(56, 78.901);

    std::stringstream       stream;
    stream << TS::bsonExporter(data, false);
    std::string result = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ(result, R"({"first":56,"second":78.901})");
}

TEST(SerMemoryTest, BsondeSerialize)
{
    std::pair<int, double>  data;

    std::stringstream       stream(R"({"first":22,"second":45.67})");
    stream >> TS::bsonImporter(data, false);

    EXPECT_EQ(data.first, 22);
    EXPECT_EQ(data.second, 45.67);
}

