#include "gtest/gtest.h"
#include "test/PolymorphicTest.h"
#include "JsonThor.h"
#include <variant>
#include <sstream>
#include <string>
#include <algorithm>


using Var1 = std::variant<PolymorphicTest::Car, PolymorphicTest::Bike>;
using Var2 = std::variant<PolymorphicTest::HyperPod, PolymorphicTest::StaticPod>;
using Var3 = std::variant<PolymorphicTest::VarHyperPod, PolymorphicTest::VarStaticPod>;


TEST(VariantTest, SerializeVariantPolyCar)
{
    Var1                v1{PolymorphicTest::Car{27, "BMW"}};
    std::stringstream   output;

    output << ThorsAnvil::Serialize::jsonExporter(v1);
    std::string result = output.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(R"({"__type":"PolymorphicTest::Car","make":"BMW","speed":27})", result);
}
TEST(VariantTest, SerializeVariantPolyBike)
{
    Var1                v1{PolymorphicTest::Bike{27, 33}};
    std::stringstream   output;

    output << ThorsAnvil::Serialize::jsonExporter(v1);
    std::string result = output.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(R"({"__type":"PolymorphicTest::Bike","stroke":33,"speed":27})", result);
}
TEST(VariantTest, DeSerializeVariantPolyCar)
{
    std::stringstream   input(R"({"__type":"PolymorphicTest::Car","make":"Audi","speed":345})");
    Var1                v1{PolymorphicTest::Bike{27, 22}};

    input >> ThorsAnvil::Serialize::jsonImporter(v1);
    ASSERT_TRUE(std::holds_alternative<PolymorphicTest::Car>(v1));
    EXPECT_EQ(std::get<PolymorphicTest::Car>(v1).make, "Audi");
    EXPECT_EQ(std::get<PolymorphicTest::Car>(v1).speed, 345);
}
TEST(VariantTest, DeSerializeVariantPolyBike)
{
    std::stringstream   input(R"({"__type":"PolymorphicTest::Bike","stroke":66,"speed":987})");
    Var1                v1{PolymorphicTest::Car{33, "Volvo"}};

    input >> ThorsAnvil::Serialize::jsonImporter(v1);
    ASSERT_TRUE(std::holds_alternative<PolymorphicTest::Bike>(v1));
    EXPECT_EQ(std::get<PolymorphicTest::Bike>(v1).stroke, 66);
    EXPECT_EQ(std::get<PolymorphicTest::Bike>(v1).speed, 987);
}
TEST(VariantTest, DeSerializeVariantPolyInvalid)
{
    std::stringstream   input(R"({"__type":"PolymorphicTest::BikeBad","stroke":66,"speed":987})");
    Var1                v1{PolymorphicTest::Car{33, "Volvo"}};

    input >> ThorsAnvil::Serialize::jsonImporter(v1);
    ASSERT_TRUE(std::holds_alternative<PolymorphicTest::Car>(v1));
    EXPECT_EQ(std::get<PolymorphicTest::Car>(v1).make, "Volvo");
    EXPECT_EQ(std::get<PolymorphicTest::Car>(v1).speed, 33);
}

TEST(VariantTest, SerializeVariantPolyHyper)
{
    Var2                v1{PolymorphicTest::HyperPod{12, 45}};
    std::stringstream   output;

    output << ThorsAnvil::Serialize::jsonExporter(v1);
    std::string result = output.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(R"({"type":"hyper-pod","size":12,"time":45,"level":12})", result);
}
TEST(VariantTest, SerializeVariantPolyStatic)
{
    Var2                v1{PolymorphicTest::StaticPod{345,22}};
    std::stringstream   output;

    output << ThorsAnvil::Serialize::jsonExporter(v1);
    std::string result = output.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(R"({"type":"static-pod","speed":345,"skill":22,"level":88})", result);
}
TEST(VariantTest, DeSerializeVariantPolyHyper)
{
    std::stringstream   input(R"({"type":"hyper-pod","size":12,"time":45,"level":12})");
    Var2                v1{PolymorphicTest::StaticPod{345,22}};

    input >> ThorsAnvil::Serialize::jsonImporter(v1);
    ASSERT_TRUE(std::holds_alternative<PolymorphicTest::HyperPod>(v1));
    EXPECT_EQ(std::get<PolymorphicTest::HyperPod>(v1).size, 12);
    EXPECT_EQ(std::get<PolymorphicTest::HyperPod>(v1).time, 45);
    EXPECT_EQ(std::get<PolymorphicTest::HyperPod>(v1).level, 12);
}
TEST(VariantTest, DeSerializeVariantPolyStatic)
{
    std::stringstream   input(R"({"type":"static-pod","speed":345,"skill":22,"level":88})");
    Var2                v1{PolymorphicTest::HyperPod{12, 45}};

    input >> ThorsAnvil::Serialize::jsonImporter(v1);
    ASSERT_TRUE(std::holds_alternative<PolymorphicTest::StaticPod>(v1));
    EXPECT_EQ(std::get<PolymorphicTest::StaticPod>(v1).speed, 345);
    EXPECT_EQ(std::get<PolymorphicTest::StaticPod>(v1).skill, 22);
    EXPECT_EQ(std::get<PolymorphicTest::StaticPod>(v1).level, 88);
}
TEST(VariantTest, SerializeVariantVarHyper)
{
    Var3                v1{PolymorphicTest::VarHyperPod{12, 45}};
    std::stringstream   output;

    output << ThorsAnvil::Serialize::jsonExporter(v1);
    std::string result = output.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(R"({"type":"hyper-pod","size":12,"time":45,"level":12})", result);
}
TEST(VariantTest, SerializeVariantVarStatic)
{
    Var3                v1{PolymorphicTest::VarStaticPod{345,22}};
    std::stringstream   output;

    output << ThorsAnvil::Serialize::jsonExporter(v1);
    std::string result = output.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(R"({"type":"static-pod","speed":345,"skill":22,"level":88})", result);
}
TEST(VariantTest, DeSerializeVariantVarHyper)
{
    std::stringstream   input(R"({"type":"hyper-pod","size":12,"time":45,"level":12})");
    Var3                v1{PolymorphicTest::VarStaticPod{345,22}};

    input >> ThorsAnvil::Serialize::jsonImporter(v1);
    ASSERT_TRUE(std::holds_alternative<PolymorphicTest::VarHyperPod>(v1));
    EXPECT_EQ(std::get<PolymorphicTest::VarHyperPod>(v1).size, 12);
    EXPECT_EQ(std::get<PolymorphicTest::VarHyperPod>(v1).time, 45);
    EXPECT_EQ(std::get<PolymorphicTest::VarHyperPod>(v1).level, 12);
}
TEST(VariantTest, DeSerializeVariantVarStatic)
{
    std::stringstream   input(R"({"type":"static-pod","speed":345,"skill":22,"level":88})");
    Var3                v1{PolymorphicTest::VarHyperPod{12, 45}};

    input >> ThorsAnvil::Serialize::jsonImporter(v1);
    ASSERT_TRUE(std::holds_alternative<PolymorphicTest::VarStaticPod>(v1));
    EXPECT_EQ(std::get<PolymorphicTest::VarStaticPod>(v1).speed, 345);
    EXPECT_EQ(std::get<PolymorphicTest::VarStaticPod>(v1).skill, 22);
    EXPECT_EQ(std::get<PolymorphicTest::VarStaticPod>(v1).level, 88);
}

