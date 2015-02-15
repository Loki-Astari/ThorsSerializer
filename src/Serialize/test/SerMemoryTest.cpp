
#include "gtest/gtest.h"
#include "SerMemory.h"
#include "Json.h"
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

