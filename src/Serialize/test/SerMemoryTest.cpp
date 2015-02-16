
#include "gtest/gtest.h"
#include "Json.h"
#include "SerMemory.h"
#include <algorithm>

namespace TS = ThorsAnvil::Serialize;

TEST(SerMemoryTest, serialize)
{
    std::pair<int, double>  data(56, 78.901);

    std::stringstream       stream;
    stream << TS::jsonExport(data);
    std::string result = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ(result, R"({"first":56,"second":78.901})");
}

TEST(SerMemoryTest, deSerialize)
{
    std::pair<int, double>  data;

    std::stringstream       stream(R"({"first":22,"second":45.67})");
    stream >> TS::jsonImport(data);

    EXPECT_EQ(data.first, 22);
    EXPECT_EQ(data.second, 45.67);
}

