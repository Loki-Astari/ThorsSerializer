#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include "SerUtil.h"
#include <algorithm>

namespace TS = ThorsAnvil::Serialize;

TEST(SerTuppleTest, Jsonserialize)
{
    std::tuple<int, double>  data {56, 78.901};

    std::stringstream       stream;
    stream << TS::jsonExporter(data, false);
    std::string result = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ(result, R"([56,78.901])");
}

TEST(SerTuppleTest, JsondeSerialize)
{
    std::stringstream   stream(R"([59,22.801])");
    std::tuple<int, double>  data {56, 78.925};

    stream >> TS::jsonImporter(data, false);
    EXPECT_EQ(59,     std::get<0>(data));
    EXPECT_EQ(22.801, std::get<1>(data));
}

TEST(SerTuppleTest, Bsonserialize)
{
    std::tuple<int, double>  data {56, 78.901};

    std::stringstream       stream;
    stream << TS::bsonExporter(data, false);
    std::string result = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ(result, R"([56,78.901])");
}

TEST(SerTuppleTest, BsondeSerialize)
{
    std::stringstream   stream(R"([59,22.801])");
    std::tuple<int, double>  data {56, 78.925};

    stream >> TS::bsonImporter(data, false);
    EXPECT_EQ(59,     std::get<0>(data));
    EXPECT_EQ(22.801, std::get<1>(data));
}

