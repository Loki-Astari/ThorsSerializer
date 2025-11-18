#include "gtest/gtest.h"
#include "test/PolymorphicTest.h"
#include "JsonThor.h"
#include <variant>
#include <sstream>
#include <string>
#include <algorithm>


using Var1 = std::variant<PolymorphicTest::Car, PolymorphicTest::Bike>;
using Var2 = std::variant<PolymorphicTest::HyperPod, PolymorphicTest::StaticPod>;


TEST(VariantTest, VariantCar)
{
    Var1                v1{PolymorphicTest::Car{27, "BMW"}};
    std::stringstream   output;

    output << ThorsAnvil::Serialize::jsonExporter(v1);
    std::string result = output.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(R"({"__type":"PolymorphicTest::Car","make":"BMW","speed":27})", result);
}
TEST(VariantTest, VariantBike)
{
    Var1                v1{PolymorphicTest::Bike{27, 33}};
    std::stringstream   output;

    output << ThorsAnvil::Serialize::jsonExporter(v1);
    std::string result = output.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(R"({"__type":"PolymorphicTest::Bike","stroke":33,"speed":27})", result);
}

