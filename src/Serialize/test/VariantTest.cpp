#include "gtest/gtest.h"
#include "test/PolymorphicTest.h"
#include "JsonThor.h"
#include <variant>
#include <sstream>
#include <string>
#include <algorithm>


using Var1 = std::variant<PolymorphicTest::Car, PolymorphicTest::Bike>;
using Var2 = std::variant<PolymorphicTest::HyperPod, PolymorphicTest::StaticPod>;


TEST(VariantTest, SerializeVariantCar)
{
    Var1                v1{PolymorphicTest::Car{27, "BMW"}};
    std::stringstream   output;

    output << ThorsAnvil::Serialize::jsonExporter(v1);
    std::string result = output.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(R"({"__type":"PolymorphicTest::Car","make":"BMW","speed":27})", result);
}
TEST(VariantTest, SerializeVariantBike)
{
    Var1                v1{PolymorphicTest::Bike{27, 33}};
    std::stringstream   output;

    output << ThorsAnvil::Serialize::jsonExporter(v1);
    std::string result = output.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(R"({"__type":"PolymorphicTest::Bike","stroke":33,"speed":27})", result);
}
TEST(VariantTest, DeSerializeVariantCar)
{
    std::stringstream   input(R"({"__type":"PolymorphicTest::Car","make":"Audi","speed":345})");
    Var1                v1{PolymorphicTest::Bike{27, 22}};

    input >> ThorsAnvil::Serialize::jsonImporter(v1);
    ASSERT_TRUE(std::holds_alternative<PolymorphicTest::Car>(v1));
    EXPECT_EQ(std::get<PolymorphicTest::Car>(v1).make, "Audi");
    EXPECT_EQ(std::get<PolymorphicTest::Car>(v1).speed, 345);
}
TEST(VariantTest, DeSerializeVariantBike)
{
    std::stringstream   input(R"({"__type":"PolymorphicTest::Bike","stroke":66,"speed":987})");
    Var1                v1{PolymorphicTest::Car{33, "Volvo"}};

    input >> ThorsAnvil::Serialize::jsonImporter(v1);
    ASSERT_TRUE(std::holds_alternative<PolymorphicTest::Bike>(v1));
    EXPECT_EQ(std::get<PolymorphicTest::Bike>(v1).stroke, 66);
    EXPECT_EQ(std::get<PolymorphicTest::Bike>(v1).speed, 987);
}
TEST(VariantTest, DeSerializeVariantInvalid)
{
    std::stringstream   input(R"({"__type":"PolymorphicTest::BikeBad","stroke":66,"speed":987})");
    Var1                v1{PolymorphicTest::Car{33, "Volvo"}};

    input >> ThorsAnvil::Serialize::jsonImporter(v1);
    ASSERT_TRUE(std::holds_alternative<PolymorphicTest::Car>(v1));
    EXPECT_EQ(std::get<PolymorphicTest::Car>(v1).make, "Volvo");
    EXPECT_EQ(std::get<PolymorphicTest::Car>(v1).speed, 33);
}

