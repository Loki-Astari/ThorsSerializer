#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonThor.h"
#include "SerUtil.h"
#include <algorithm>

using namespace ThorsAnvil::Serialize;

TEST(SerArrayTest, ArrayEmpty)
{
    std::stringstream   stream("[]");
    std::array<int,0>   data;

    stream >> jsonImporter(data, false);

    EXPECT_EQ(data.empty(), true);
}

TEST(SerArrayTest, ArrayOfIntSerialize)
{
    std::array<int,12>  data{1,2,3,4,5,6,7,8,101,102,9,10};

    std::stringstream   stream;
    stream << jsonExporter(data, false);

    std::string result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ(result, R"([1,2,3,4,5,6,7,8,101,102,9,10])");
}

TEST(SerArrayTest, ArrayOfIntDeSerialize)
{
    std::array<int,12>  data;
    std::stringstream   stream("[1,2,3,4,5,6,7,8,101,102,9,10]");

    stream >> jsonImporter(data, false);

    auto loop = data.begin();

    EXPECT_EQ(*loop++, 1);
    EXPECT_EQ(*loop++, 2);
    EXPECT_EQ(*loop++, 3);
    EXPECT_EQ(*loop++, 4);
    EXPECT_EQ(*loop++, 5);
    EXPECT_EQ(*loop++, 6);
    EXPECT_EQ(*loop++, 7);
    EXPECT_EQ(*loop++, 8);
    EXPECT_EQ(*loop++, 101);
    EXPECT_EQ(*loop++, 102);
    EXPECT_EQ(*loop++, 9);
    EXPECT_EQ(*loop++, 10);
}

