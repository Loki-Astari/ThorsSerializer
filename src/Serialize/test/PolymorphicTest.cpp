
#include "gtest/gtest.h"
#include "test/SerializeTest.h"
#include "Serialize.h"
#include "Serialize.tpp"
#include "Traits.h"
#include "JsonThor.h"
#include <string>
#include <sstream>
#include <cctype>

namespace PolymorphicTest
{
struct Vehicle
{
    Vehicle(){}
    Vehicle(int speed)
        : speed(speed)
    {}
    int     speed;
    ThorsAnvil_PolyMorphicSerializer(PolymorphicTest::Vehicle);
};
struct Car: public Vehicle
{
    Car(){}
    Car(int speed, std::string const& make)
        : Vehicle(speed)
        , make(make)
    {}
    std::string     make;
    ThorsAnvil_PolyMorphicSerializer(PolymorphicTest::Car);
};
struct Bike: public Vehicle
{
    Bike(){}
    Bike(int speed, int stroke)
        : Vehicle(speed)
        , stroke(stroke)
    {}
    int     stroke;
    ThorsAnvil_PolyMorphicSerializer(PolymorphicTest::Bike);
};
struct User
{
    int         age;
    Vehicle*    transport;
};
}

ThorsAnvil_MakeTrait(PolymorphicTest::Vehicle, speed);
ThorsAnvil_ExpandTrait(PolymorphicTest::Vehicle, PolymorphicTest::Car, make);
ThorsAnvil_ExpandTrait(PolymorphicTest::Vehicle, PolymorphicTest::Bike, stroke);
ThorsAnvil_MakeTrait(PolymorphicTest::User, age, transport);

TEST(PolymorphicTest, NullPointer)
{
    PolymorphicTest::User    user1{10, nullptr};

    std::stringstream   data;
    data << ThorsAnvil::Serialize::jsonExport(user1);
    std::string result = data.str();

    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(result, R"({"age":10,"transport":null})");
}
TEST(PolymorphicTest, VehiclePointer)
{
    PolymorphicTest::User    user1{10, new PolymorphicTest::Vehicle(12)};

    std::stringstream   data;
    data << ThorsAnvil::Serialize::jsonExport(user1);
    std::string result = data.str();

    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(result, R"({"age":10,"transport":{"__type":"PolymorphicTest::Vehicle","speed":12}})");
}
TEST(PolymorphicTest, CarPointer)
{
    PolymorphicTest::User    user1{10, new PolymorphicTest::Car(16, "Turbo")};

    std::stringstream   data;
    data << ThorsAnvil::Serialize::jsonExport(user1);
    std::string result = data.str();

    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(result, R"({"age":10,"transport":{"__type":"PolymorphicTest::Car","speed":16,"make":"Turbo"}})");
}

TEST(PolymorphicTest, BikePointer)
{
    PolymorphicTest::User    user1{10, new PolymorphicTest::Bike(18, 7)};

    std::stringstream   data;
    data << ThorsAnvil::Serialize::jsonExport(user1);
    std::string result = data.str();

    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(result, R"({"age":10,"transport":{"__type":"PolymorphicTest::Bike","speed":18,"stroke":7}})");
}

TEST(PolymorphicTest, ReadNull)
{
    std::stringstream   stream(R"({"age":10,"transport":null})");
    PolymorphicTest::User                user1 {12, new PolymorphicTest::Vehicle(12)};

    stream >> ThorsAnvil::Serialize::jsonImport(user1);
    EXPECT_EQ(user1.age, 10);
    EXPECT_EQ(user1.transport, nullptr);
}

TEST(PolymorphicTest, ReadVehicle)
{
    std::stringstream   stream(R"({"age":10,"transport":{"__type":"PolymorphicTest::Vehicle","speed":12}})");
    PolymorphicTest::User                user1 {12, new PolymorphicTest::Vehicle(13)};

    stream >> ThorsAnvil::Serialize::jsonImport(user1);
    EXPECT_EQ(user1.age, 10);
    ASSERT_NE(user1.transport, nullptr);
    EXPECT_EQ(user1.transport->speed, 12);
}

TEST(PolymorphicTest, ReadCar)
{
    std::stringstream   stream(R"({"age":10,"transport":{"__type":"PolymorphicTest::Car","speed":16,"make":"Turbo"}})");
    PolymorphicTest::User                user1 {12, new PolymorphicTest::Vehicle(14)};

    stream >> ThorsAnvil::Serialize::jsonImport(user1);
    EXPECT_EQ(user1.age, 10);
    ASSERT_NE(user1.transport, nullptr);
    EXPECT_EQ(user1.transport->speed, 16);

    PolymorphicTest::Car* car = dynamic_cast<PolymorphicTest::Car*>(user1.transport);
    ASSERT_NE(car, nullptr);
    EXPECT_EQ(car->make, "Turbo");
}

TEST(PolymorphicTest, ReadBike)
{
    std::stringstream   stream(R"({"age":10,"transport":{"__type":"PolymorphicTest::Bike","speed":18,"stroke":7}})");
    PolymorphicTest::User                user1 {12, new PolymorphicTest::Vehicle(15)};

    stream >> ThorsAnvil::Serialize::jsonImport(user1);
    EXPECT_EQ(user1.age, 10);
    ASSERT_NE(user1.transport, nullptr);
    EXPECT_EQ(user1.transport->speed, 18);

    PolymorphicTest::Bike* bike = dynamic_cast<PolymorphicTest::Bike*>(user1.transport);
    ASSERT_NE(bike, nullptr);
    EXPECT_EQ(bike->stroke, 7);
}

