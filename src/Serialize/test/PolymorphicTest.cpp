
#include "gtest/gtest.h"
#include "test/SerializeTest.h"
#include "Serialize.h"
#include "Serialize.tpp"
#include "Traits.h"
#include "JsonThor.h"
#include <string>
#include <sstream>
#include <cctype>

struct Vehicle
{
    Vehicle(){}
    Vehicle(int speed)
        : speed(speed)
    {}
    int     speed;
    ThorsAnvil_PolyMorphicSerializer(Vehicle);
};
struct Car: public Vehicle
{
    Car(){}
    Car(int speed, std::string const& make)
        : Vehicle(speed)
        , make(make)
    {}
    std::string     make;
    ThorsAnvil_PolyMorphicSerializer(Car);
};
struct Bike: public Vehicle
{
    Bike(){}
    Bike(int speed, int stroke)
        : Vehicle(speed)
        , stroke(stroke)
    {}
    int     stroke;
    ThorsAnvil_PolyMorphicSerializer(Bike);
};

ThorsAnvil_MakeTrait(Vehicle, speed);
ThorsAnvil_ExpandTrait(Vehicle, Car, make);
ThorsAnvil_ExpandTrait(Vehicle, Bike, stroke);


struct User
{
    int         age;
    Vehicle*    transport;
};
ThorsAnvil_MakeTrait(User, age, transport);

namespace ThorsAnvil
{
    namespace Serialize
    {

    }
}

TEST(PolymorphicTest, NullPointer)
{
    User    user1{10, nullptr};

    std::stringstream   data;
    data << ThorsAnvil::Serialize::jsonExport(user1);
    std::string result = data.str();

    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(result, R"({"age":10,"transport":null})");
}
TEST(PolymorphicTest, VehiclePointer)
{
    User    user1{10, new Vehicle(12)};

    std::stringstream   data;
    data << ThorsAnvil::Serialize::jsonExport(user1);
    std::string result = data.str();

    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(result, R"({"age":10,"transport":{"__type":"Vehicle","speed":12}})");
}
TEST(PolymorphicTest, CarPointer)
{
    User    user1{10, new Car(16, "Turbo")};

    std::stringstream   data;
    data << ThorsAnvil::Serialize::jsonExport(user1);
    std::string result = data.str();

    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(result, R"({"age":10,"transport":{"__type":"Car","speed":16,"make":"Turbo"}})");
}

TEST(PolymorphicTest, BikePointer)
{
    User    user1{10, new Bike(18, 7)};

    std::stringstream   data;
    data << ThorsAnvil::Serialize::jsonExport(user1);
    std::string result = data.str();

    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(result, R"({"age":10,"transport":{"__type":"Bike","speed":18,"stroke":7}})");
}

TEST(PolymorphicTest, ReadNull)
{
    std::stringstream   stream(R"({"age":10,"transport":null})");
    User                user1 {12, new Vehicle(12)};

    stream >> ThorsAnvil::Serialize::jsonImport(user1);
    EXPECT_EQ(user1.age, 10);
    EXPECT_EQ(user1.transport, nullptr);
}

TEST(PolymorphicTest, ReadVehicle)
{
    std::stringstream   stream(R"({"age":10,"transport":{"__type":"Vehicle","speed":12}})");
    User                user1 {12, new Vehicle(13)};

    stream >> ThorsAnvil::Serialize::jsonImport(user1);
    EXPECT_EQ(user1.age, 10);
    ASSERT_NE(user1.transport, nullptr);
    EXPECT_EQ(user1.transport->speed, 12);
}

TEST(PolymorphicTest, ReadCar)
{
    std::stringstream   stream(R"({"age":10,"transport":{"__type":"Car","speed":16,"make":"Turbo"}})");
    User                user1 {12, new Vehicle(14)};

    stream >> ThorsAnvil::Serialize::jsonImport(user1);
    EXPECT_EQ(user1.age, 10);
    ASSERT_NE(user1.transport, nullptr);
    EXPECT_EQ(user1.transport->speed, 16);

    Car* car = dynamic_cast<Car*>(user1.transport);
    ASSERT_NE(car, nullptr);
    EXPECT_EQ(car->make, "Turbo");
}

TEST(PolymorphicTest, ReadBike)
{
    std::stringstream   stream(R"({"age":10,"transport":{"__type":"Bike","speed":18,"stroke":7}})");
    User                user1 {12, new Vehicle(15)};

    stream >> ThorsAnvil::Serialize::jsonImport(user1);
    EXPECT_EQ(user1.age, 10);
    ASSERT_NE(user1.transport, nullptr);
    EXPECT_EQ(user1.transport->speed, 18);

    Bike* bike = dynamic_cast<Bike*>(user1.transport);
    ASSERT_NE(bike, nullptr);
    EXPECT_EQ(bike->stroke, 7);
}

