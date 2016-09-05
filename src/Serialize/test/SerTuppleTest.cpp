
#include "gtest/gtest.h"
#include "JsonThor.h"
#include "SerUtil.h"
#include <algorithm>

namespace TS = ThorsAnvil::Serialize;

TEST(SerTuppleTest, serialize)
{
    std::tuple<int, double>  data {56, 78.901};

    std::stringstream       stream;
    stream << TS::jsonExport(data);
    std::string result = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ(result, R"([56,78.901])");
}

TEST(SerTuppleTest, deSerialize)
{
    std::stringstream   stream(R"([59,22.801])");
    std::tuple<int, double>  data {56, 78.925};

    stream >> TS::jsonImport(data);
    EXPECT_EQ(59,     std::get<0>(data));
    EXPECT_EQ(22.801, std::get<1>(data));
}

