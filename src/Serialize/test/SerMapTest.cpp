
#include "gtest/gtest.h"
#include "SerMap.h"
#include "Json.h"
#include <algorithm>

namespace TS = ThorsAnvil::Serialize;

TEST(SerMapTest, serialize)
{
    std::map<int, double>  data;
    data[56]    = 78.901;

    std::stringstream       stream;
    stream << TS::jsonExport(data);
    std::string result = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ(result, R"([{"first":56,"second":78.901}])");
}

TEST(SerMapTest, deSerialize)
{
    std::map<int, double>  data;

    std::stringstream       stream(R"([{"first":64,"second":12}, {"first":118,"second":14}])");
    stream >> TS::jsonImport(data);

    EXPECT_EQ(data[64],  12);
    EXPECT_EQ(data[118], 14);
}

TEST(SerMapTest, serializeStringKey)
{
    std::map<std::string, double>  data;
    data["AStringKey"]      = 78.902;
    data["TestValue"]       = 22.903;

    std::stringstream       stream;
    stream << TS::jsonExport(data);
    std::string result = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ(result, R"({"AStringKey":78.902,"TestValue":22.903})");
}

TEST(SerMapTest, deSerializeStringKey)
{
    std::map<std::string, bool>  data;

    std::stringstream       stream(R"({"OneFileDay":true, "TheLastStand":false, "OfMiceAndMen":true})");
    stream >> TS::jsonImport(data);

    EXPECT_EQ(data["OneFileDay"],   true);
    EXPECT_EQ(data["TheLastStand"], false);
    EXPECT_EQ(data["OfMiceAndMen"], true);
}

