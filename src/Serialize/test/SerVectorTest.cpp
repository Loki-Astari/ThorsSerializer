

#include "gtest/gtest.h"
#include "Json.h"
#include "SerVector.h"
#include <algorithm>

using namespace ThorsAnvil::Serialize;

TEST(SerVectorTest, ArrayEmpty)
{
    std::stringstream   stream("[]");
    std::vector<int>    data;

    stream >> jsonImport(data);

    EXPECT_EQ(data.empty(), true);
}

TEST(SerVectorTest, VectorOfIntSerialize)
{
    std::vector<int>    data{1,2,3,4,5,6,7,8,101,102,9,10};

    std::stringstream   stream;
    stream << jsonExport(data);

    std::string result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ(result, R"([1,2,3,4,5,6,7,8,101,102,9,10])");
}

