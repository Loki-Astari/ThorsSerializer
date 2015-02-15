
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

