

#include "gtest/gtest.h"
#include "Json.h"
#include "SerList.h"
#include <algorithm>

using namespace ThorsAnvil::Serialize;

TEST(SerListTest, ArrayEmpty)
{
    std::stringstream   stream("[]");
    std::list<int>      data;

    stream >> jsonImport(data);

    EXPECT_EQ(data.empty(), true);
}

TEST(SerListTest, ListOfIntSerialize)
{
    std::list<int>      data{1,2,3,4,5,6,7,8,101,102,9,10};

    std::stringstream   stream;
    stream << jsonExport(data);

    std::string result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ(result, R"([1,2,3,4,5,6,7,8,101,102,9,10])");
}

TEST(SerListTest, ListOfIntDeSerialize)
{
    std::list<int>    data;
    std::stringstream   stream("[1,2,3,4,5,6,7,8,101,102,9,10]");

    stream >> jsonImport(data);

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

