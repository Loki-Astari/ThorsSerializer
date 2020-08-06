#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonThor.h"
#include "SerUtil.h"
#include <algorithm>

using namespace ThorsAnvil::Serialize;

TEST(SerInitializerListTest, InitListOfIntSerialize)
{
    std::initializer_list<int>  data{1,2,3,4,5,6,7,8,101,102,9,10};

    std::stringstream   stream;
    stream << jsonExporter(data, false);

    std::string result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ(result, R"([1,2,3,4,5,6,7,8,101,102,9,10])");
}


