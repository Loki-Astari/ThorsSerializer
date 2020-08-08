#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "test/SerializeTest.h"
#include "Serialize.h"
#include "Serialize.tpp"
#include "Traits.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include <string>
#include <sstream>
#include <cctype>

namespace Issue50Test
{
struct Vehicle
{
    Vehicle(){}
    Vehicle(int speed)
        : speed(speed)
    {}
    int     speed;
    ThorsAnvil_PolyMorphicSerializer(Issue50Test::Vehicle);
};
struct Car: public Vehicle
{
    Car(){}
    Car(int speed, std::string const& make)
        : Vehicle(speed)
        , make(make)
    {}
    std::string     make;
    ThorsAnvil_PolyMorphicSerializer(Issue50Test::Car);
};
struct Bike: public Vehicle
{
    Bike(){}
    Bike(int speed, int stroke)
        : Vehicle(speed)
        , stroke(stroke)
    {}
    int     stroke;
    ThorsAnvil_PolyMorphicSerializer(Issue50Test::Bike);
};
struct User
{
    int         age;
    Vehicle*    transport;
};
}

ThorsAnvil_MakeTrait(Issue50Test::Vehicle, speed);
ThorsAnvil_ExpandTrait(Issue50Test::Vehicle, Issue50Test::Car, make);
ThorsAnvil_ExpandTrait(Issue50Test::Vehicle, Issue50Test::Bike, stroke);
ThorsAnvil_MakeTrait(Issue50Test::User, age, transport);

TEST(Issue50Test, JsonNullPointer)
{
    using namespace std::string_literals;

    Issue50Test::User    user1{10, nullptr};

    std::stringstream   data;
    data << ThorsAnvil::Serialize::jsonExporter(user1, "$type"s);
    std::string result = data.str();

    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(result, R"({"age":10,"transport":null})");
}
TEST(Issue50Test, JsonVehiclePointer)
{
    using namespace std::string_literals;

    Issue50Test::User    user1{10, new Issue50Test::Vehicle(12)};

    std::stringstream   data;
    data << ThorsAnvil::Serialize::jsonExporter(user1, "$type"s);
    std::string result = data.str();

    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(result, R"({"age":10,"transport":{"$type":"Issue50Test::Vehicle","speed":12}})");
}
TEST(Issue50Test, JsonCarPointer)
{
    using namespace std::string_literals;

    Issue50Test::User    user1{10, new Issue50Test::Car(16, "Turbo")};

    std::stringstream   data;
    data << ThorsAnvil::Serialize::jsonExporter(user1, "$type"s);
    std::string result = data.str();

    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(result, R"({"age":10,"transport":{"$type":"Issue50Test::Car","speed":16,"make":"Turbo"}})");
}

TEST(Issue50Test, JsonBikePointer)
{
    using namespace std::string_literals;

    Issue50Test::User    user1{10, new Issue50Test::Bike(18, 7)};

    std::stringstream   data;
    data << ThorsAnvil::Serialize::jsonExporter(user1, "$type"s);
    std::string result = data.str();

    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(result, R"({"age":10,"transport":{"$type":"Issue50Test::Bike","speed":18,"stroke":7}})");
}

TEST(Issue50Test, JsonReadNull)
{
    using namespace std::string_literals;

    std::stringstream   stream(R"({"age":10,"transport":null})");
    Issue50Test::User                user1 {12, new Issue50Test::Vehicle(12)};

    stream >> ThorsAnvil::Serialize::jsonImporter(user1, "$type"s);
    EXPECT_EQ(user1.age, 10);
    EXPECT_EQ(user1.transport, nullptr);
}

TEST(Issue50Test, JsonReadVehicle)
{
    using namespace std::string_literals;

    std::stringstream   stream(R"({"age":10,"transport":{"$type":"Issue50Test::Vehicle","speed":12}})");
    Issue50Test::User                user1 {12, new Issue50Test::Vehicle(13)};

    stream >> ThorsAnvil::Serialize::jsonImporter(user1, "$type"s);
    EXPECT_EQ(user1.age, 10);
    ASSERT_NE(user1.transport, nullptr);
    EXPECT_EQ(user1.transport->speed, 12);
}

TEST(Issue50Test, JsonReadCar)
{
    using namespace std::string_literals;

    std::stringstream   stream(R"({"age":10,"transport":{"$type":"Issue50Test::Car","speed":16,"make":"Turbo"}})");
    Issue50Test::User                user1 {12, new Issue50Test::Vehicle(14)};

    stream >> ThorsAnvil::Serialize::jsonImporter(user1, "$type"s);
    EXPECT_EQ(user1.age, 10);
    ASSERT_NE(user1.transport, nullptr);
    EXPECT_EQ(user1.transport->speed, 16);

    Issue50Test::Car* car = dynamic_cast<Issue50Test::Car*>(user1.transport);
    ASSERT_NE(car, nullptr);
    EXPECT_EQ(car->make, "Turbo");
}

TEST(Issue50Test, JsonReadBike)
{
    using namespace std::string_literals;

    std::stringstream   stream(R"({"age":10,"transport":{"$type":"Issue50Test::Bike","speed":18,"stroke":7}})");
    Issue50Test::User                user1 {12, new Issue50Test::Vehicle(15)};

    stream >> ThorsAnvil::Serialize::jsonImporter(user1, "$type"s);
    EXPECT_EQ(user1.age, 10);
    ASSERT_NE(user1.transport, nullptr);
    EXPECT_EQ(user1.transport->speed, 18);

    Issue50Test::Bike* bike = dynamic_cast<Issue50Test::Bike*>(user1.transport);
    ASSERT_NE(bike, nullptr);
    EXPECT_EQ(bike->stroke, 7);
}
TEST(Issue50Test, BsonNullPointer)
{
    using namespace std::string_literals;

    Issue50Test::User    user1{10, nullptr};

    std::stringstream   data;
    data << ThorsAnvil::Serialize::bsonExporter(user1, "$type"s);
    std::string result = data.str();

    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(result, R"({"age":10,"transport":null})");
}
TEST(Issue50Test, BsonVehiclePointer)
{
    using namespace std::string_literals;

    Issue50Test::User    user1{10, new Issue50Test::Vehicle(12)};

    std::stringstream   data;
    data << ThorsAnvil::Serialize::bsonExporter(user1, "$type"s);
    std::string result = data.str();

    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(result, R"({"age":10,"transport":{"$type":"Issue50Test::Vehicle","speed":12}})");
}
TEST(Issue50Test, BsonCarPointer)
{
    using namespace std::string_literals;

    Issue50Test::User    user1{10, new Issue50Test::Car(16, "Turbo")};

    std::stringstream   data;
    data << ThorsAnvil::Serialize::bsonExporter(user1, "$type"s);
    std::string result = data.str();

    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(result, R"({"age":10,"transport":{"$type":"Issue50Test::Car","speed":16,"make":"Turbo"}})");
}

TEST(Issue50Test, BsonBikePointer)
{
    using namespace std::string_literals;

    Issue50Test::User    user1{10, new Issue50Test::Bike(18, 7)};

    std::stringstream   data;
    data << ThorsAnvil::Serialize::bsonExporter(user1, "$type"s);
    std::string result = data.str();

    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(result, R"({"age":10,"transport":{"$type":"Issue50Test::Bike","speed":18,"stroke":7}})");
}

TEST(Issue50Test, BsonReadNull)
{
    using namespace std::string_literals;

    std::stringstream   stream(R"({"age":10,"transport":null})");
    Issue50Test::User                user1 {12, new Issue50Test::Vehicle(12)};

    stream >> ThorsAnvil::Serialize::bsonImporter(user1, "$type"s);
    EXPECT_EQ(user1.age, 10);
    EXPECT_EQ(user1.transport, nullptr);
}

TEST(Issue50Test, BsonReadVehicle)
{
    using namespace std::string_literals;

    std::stringstream   stream(R"({"age":10,"transport":{"$type":"Issue50Test::Vehicle","speed":12}})");
    Issue50Test::User                user1 {12, new Issue50Test::Vehicle(13)};

    stream >> ThorsAnvil::Serialize::bsonImporter(user1, "$type"s);
    EXPECT_EQ(user1.age, 10);
    ASSERT_NE(user1.transport, nullptr);
    EXPECT_EQ(user1.transport->speed, 12);
}

TEST(Issue50Test, BsonReadCar)
{
    using namespace std::string_literals;

    std::stringstream   stream(R"({"age":10,"transport":{"$type":"Issue50Test::Car","speed":16,"make":"Turbo"}})");
    Issue50Test::User                user1 {12, new Issue50Test::Vehicle(14)};

    stream >> ThorsAnvil::Serialize::bsonImporter(user1, "$type"s);
    EXPECT_EQ(user1.age, 10);
    ASSERT_NE(user1.transport, nullptr);
    EXPECT_EQ(user1.transport->speed, 16);

    Issue50Test::Car* car = dynamic_cast<Issue50Test::Car*>(user1.transport);
    ASSERT_NE(car, nullptr);
    EXPECT_EQ(car->make, "Turbo");
}

TEST(Issue50Test, BsonReadBike)
{
    using namespace std::string_literals;

    std::stringstream   stream(R"({"age":10,"transport":{"$type":"Issue50Test::Bike","speed":18,"stroke":7}})");
    Issue50Test::User                user1 {12, new Issue50Test::Vehicle(15)};

    stream >> ThorsAnvil::Serialize::bsonImporter(user1, "$type"s);
    EXPECT_EQ(user1.age, 10);
    ASSERT_NE(user1.transport, nullptr);
    EXPECT_EQ(user1.transport->speed, 18);

    Issue50Test::Bike* bike = dynamic_cast<Issue50Test::Bike*>(user1.transport);
    ASSERT_NE(bike, nullptr);
    EXPECT_EQ(bike->stroke, 7);
}

