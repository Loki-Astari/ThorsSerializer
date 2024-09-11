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

using namespace std::string_literals;

namespace Issue50Test
{
struct Vehicle
{
    Vehicle(){}
    virtual ~Vehicle() {}
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

TEST(Issue50TestString, JsonNullPointer)
{
    using namespace std::string_literals;

    Issue50Test::User    user1{10, nullptr};

    std::string         data;
    data << ThorsAnvil::Serialize::jsonExporter(user1, "$type"s);
    std::string result = data;

    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(result, R"({"age":10,"transport":null})");
}
TEST(Issue50TestString, JsonVehiclePointer)
{
    using namespace std::string_literals;

    Issue50Test::User    user1{10, new Issue50Test::Vehicle(12)};

    std::string         data;
    data << ThorsAnvil::Serialize::jsonExporter(user1, "$type"s);
    std::string result = data;

    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(result, R"({"age":10,"transport":{"$type":"Issue50Test::Vehicle","speed":12}})");
}
TEST(Issue50TestString, JsonCarPointer)
{
    using namespace std::string_literals;

    Issue50Test::User    user1{10, new Issue50Test::Car(16, "Turbo")};

    std::string         data;
    data << ThorsAnvil::Serialize::jsonExporter(user1, "$type"s);
    std::string result = data;

    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(result, R"({"age":10,"transport":{"$type":"Issue50Test::Car","make":"Turbo","speed":16}})");
}

TEST(Issue50TestString, JsonBikePointer)
{
    using namespace std::string_literals;

    Issue50Test::User    user1{10, new Issue50Test::Bike(18, 7)};

    std::string         data;
    data << ThorsAnvil::Serialize::jsonExporter(user1, "$type"s);
    std::string result = data;

    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(result, R"({"age":10,"transport":{"$type":"Issue50Test::Bike","stroke":7,"speed":18}})");
}

TEST(Issue50TestString, JsonReadNull)
{
    using namespace std::string_literals;

    std::string          stream(R"({"age":10,"transport":null})");
    Issue50Test::User                user1 {12, new Issue50Test::Vehicle(12)};

    stream >> ThorsAnvil::Serialize::jsonImporter(user1, "$type"s);
    EXPECT_EQ(user1.age, 10);
    EXPECT_EQ(user1.transport, nullptr);
}

TEST(Issue50TestString, JsonReadVehicle)
{
    using namespace std::string_literals;

    std::string          stream(R"({"age":10,"transport":{"$type":"Issue50Test::Vehicle","speed":12}})");
    Issue50Test::User                user1 {12, new Issue50Test::Vehicle(13)};

    stream >> ThorsAnvil::Serialize::jsonImporter(user1, "$type"s);
    EXPECT_EQ(user1.age, 10);
    ASSERT_NE(user1.transport, nullptr);
    EXPECT_EQ(user1.transport->speed, 12);
}

TEST(Issue50TestString, JsonReadCar)
{
    using namespace std::string_literals;

    std::string          stream(R"({"age":10,"transport":{"$type":"Issue50Test::Car","speed":16,"make":"Turbo"}})");
    Issue50Test::User                user1 {12, new Issue50Test::Vehicle(14)};

    stream >> ThorsAnvil::Serialize::jsonImporter(user1, "$type"s);
    EXPECT_EQ(user1.age, 10);
    ASSERT_NE(user1.transport, nullptr);
    EXPECT_EQ(user1.transport->speed, 16);

    Issue50Test::Car* car = dynamic_cast<Issue50Test::Car*>(user1.transport);
    ASSERT_NE(car, nullptr);
    EXPECT_EQ(car->make, "Turbo");
}

TEST(Issue50TestString, JsonReadBike)
{
    using namespace std::string_literals;

    std::string          stream(R"({"age":10,"transport":{"$type":"Issue50Test::Bike","speed":18,"stroke":7}})");
    Issue50Test::User                user1 {12, new Issue50Test::Vehicle(15)};

    stream >> ThorsAnvil::Serialize::jsonImporter(user1, "$type"s);
    EXPECT_EQ(user1.age, 10);
    ASSERT_NE(user1.transport, nullptr);
    EXPECT_EQ(user1.transport->speed, 18);

    Issue50Test::Bike* bike = dynamic_cast<Issue50Test::Bike*>(user1.transport);
    ASSERT_NE(bike, nullptr);
    EXPECT_EQ(bike->stroke, 7);
}
TEST(Issue50TestString, BsonNullPointer)
{
    using namespace std::string_literals;

    Issue50Test::User    user1{10, nullptr};

    std::string         data;
    data << ThorsAnvil::Serialize::bsonExporter(user1, "$type"s);
    std::string result = data;

    EXPECT_EQ(result, "\x19\x00\x00\x00"
                      "\x10" "age\x00"  "\x0A\x00\x00\x00"
                      "\x0A" "transport\x00"
                      "\x00"s);
    //NOTE OUTPUT (result, R"({"age":10,"transport":null})");
}
TEST(Issue50TestString, BsonVehiclePointer)
{
    using namespace std::string_literals;

    Issue50Test::User    user1{10, new Issue50Test::Vehicle(12)};

    std::string         data;
    data << ThorsAnvil::Serialize::bsonExporter(user1, "$type"s);
    std::string result = data;

    EXPECT_EQ(result, "\x49\x00\x00\x00"
                      "\x10" "age\x00"   "\x0A\x00\x00\x00"
                      "\x03" "transport\x00"
                            "\x30\x00\x00\x00"
                            "\x02" "$type\x00"  "\x15\x00\x00\x00" "Issue50Test::Vehicle\x00"
                            "\x10" "speed\x00"  "\x0C\x00\x00\x00"
                            "\x00"
                      "\x00"s);
    //NOTE OUTPUT (result, R"({"age":10,"transport":{"$type":"Issue50Test::Vehicle","speed":12}})");
}
TEST(Issue50TestString, BsonCarPointer)
{
    using namespace std::string_literals;

    Issue50Test::User    user1{10, new Issue50Test::Car(16, "Turbo")};

    std::string         data;
    data << ThorsAnvil::Serialize::bsonExporter(user1, "$type"s);
    std::string result = data;

    EXPECT_EQ(result, "\x55\x00\x00\x00"
                      "\x10" "age\x00"  "\x0A\x00\x00\x00"
                      "\x03" "transport\x00"
                            "\x3c\x00\x00\x00"
                            "\x02" "$type\x00"  "\x11\x00\x00\x00"  "Issue50Test::Car\x00"
                            "\x02" "make\x00"   "\x06\x00\x00\x00"  "Turbo\x00"
                            "\x10" "speed\x00"  "\x10\x00\x00\x00"
                            "\x00"
                      "\x00"s);
    //NOTE OUTPUT (result, R"({"age":10,"transport":{"$type":"Issue50Test::Car","speed":16,"make":"Turbo"}})");
}

TEST(Issue50TestString, BsonBikePointer)
{
    using namespace std::string_literals;

    Issue50Test::User    user1{10, new Issue50Test::Bike(18, 7)};

    std::string         data;
    data << ThorsAnvil::Serialize::bsonExporter(user1, "$type"s);
    std::string result = data;

    EXPECT_EQ(result, "\x52\x00\x00\x00"
                      "\x10" "age\x00"  "\x0A\x00\x00\x00"
                      "\x03" "transport\x00"
                            "\x39\x00\x00\x00"
                            "\x02" "$type\x00"  "\x12\x00\x00\x00"  "Issue50Test::Bike\x00"
                            "\x10" "stroke\x00" "\x07\x00\x00\x00"
                            "\x10" "speed\x00"  "\x12\x00\x00\x00"
                            "\x00"
                      "\x00"s);
    //NOTE OUTPUT (result, R"({"age":10,"transport":{"$type":"Issue50Test::Bike","speed":18,"stroke":7}})");
}

TEST(Issue50TestString, BsonReadNull)
{
    using namespace std::string_literals;

    //NOTE INPUT (R"({"age":10,"transport":null})");
    std::string input = "\x19\x00\x00\x00"
                        "\x10" "age\x00"  "\x0A\x00\x00\x00"
                        "\x0A" "transport\x00"
                        "\x00"s;
    std::string          stream(input);
    Issue50Test::User                user1 {12, new Issue50Test::Vehicle(12)};

    stream >> ThorsAnvil::Serialize::bsonImporter(user1, "$type"s);
    EXPECT_EQ(user1.age, 10);
    EXPECT_EQ(user1.transport, nullptr);
}

TEST(Issue50TestString, BsonReadVehicle)
{
    using namespace std::string_literals;

    //NOTE INPUT (R"({"age":10,"transport":{"$type":"Issue50Test::Vehicle","speed":12}})");
    std::string input = "\x49\x00\x00\x00"
                        "\x10" "age\x00"   "\x0A\x00\x00\x00"
                        "\x03" "transport\x00"
                            "\x30\x00\x00\x00"
                            "\x02" "$type\x00"  "\x15\x00\x00\x00" "Issue50Test::Vehicle\x00"
                            "\x10" "speed\x00"  "\x0C\x00\x00\x00"
                            "\x00"
                        "\x00"s;
    std::string          stream(input);
    Issue50Test::User                user1 {12, new Issue50Test::Vehicle(13)};

    stream >> ThorsAnvil::Serialize::bsonImporter(user1, "$type"s);
    EXPECT_EQ(user1.age, 10);
    ASSERT_NE(user1.transport, nullptr);
    EXPECT_EQ(user1.transport->speed, 12);
}

TEST(Issue50TestString, BsonReadCar)
{
    using namespace std::string_literals;

    //NOTE INPUT (R"({"age":10,"transport":{"$type":"Issue50Test::Car","speed":16,"make":"Turbo"}})");
    std::string input = "\x55\x00\x00\x00"
                        "\x10" "age\x00"  "\x0A\x00\x00\x00"
                        "\x03" "transport\x00"
                            "\x3c\x00\x00\x00"
                            "\x02" "$type\x00"  "\x11\x00\x00\x00"  "Issue50Test::Car\x00"
                            "\x10" "speed\x00"  "\x10\x00\x00\x00"
                            "\x02" "make\x00"   "\x06\x00\x00\x00"  "Turbo\x00"
                            "\x00"
                        "\x00"s;
    std::string          stream(input);
    Issue50Test::User                user1 {12, new Issue50Test::Vehicle(14)};

    stream >> ThorsAnvil::Serialize::bsonImporter(user1, "$type"s);
    EXPECT_EQ(user1.age, 10);
    ASSERT_NE(user1.transport, nullptr);
    EXPECT_EQ(user1.transport->speed, 16);

    Issue50Test::Car* car = dynamic_cast<Issue50Test::Car*>(user1.transport);
    ASSERT_NE(car, nullptr);
    EXPECT_EQ(car->make, "Turbo");
}

TEST(Issue50TestString, BsonReadBike)
{
    using namespace std::string_literals;

    //NOTE INPUT (R"({"age":10,"transport":{"$type":"Issue50Test::Bike","speed":18,"stroke":7}})");
    std::string input = "\x52\x00\x00\x00"
                        "\x10" "age\x00"  "\x0A\x00\x00\x00"
                        "\x03" "transport\x00"
                            "\x39\x00\x00\x00"
                            "\x02" "$type\x00"  "\x12\x00\x00\x00"  "Issue50Test::Bike\x00"
                            "\x10" "speed\x00"  "\x12\x00\x00\x00"
                            "\x10" "stroke\x00" "\x07\x00\x00\x00"
                            "\x00"
                        "\x00"s;
    std::string          stream(input);
    Issue50Test::User                user1 {12, new Issue50Test::Vehicle(15)};

    stream >> ThorsAnvil::Serialize::bsonImporter(user1, "$type"s);
    EXPECT_EQ(user1.age, 10);
    ASSERT_NE(user1.transport, nullptr);
    EXPECT_EQ(user1.transport->speed, 18);

    Issue50Test::Bike* bike = dynamic_cast<Issue50Test::Bike*>(user1.transport);
    ASSERT_NE(bike, nullptr);
    EXPECT_EQ(bike->stroke, 7);
}

