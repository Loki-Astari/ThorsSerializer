#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "test/SerializeTest.h"
#include "Serialize.h"
#include "Serialize.tpp"
#include "Traits.h"
#include "SerUtil.h"
#include "JsonThor.h"
#include "BsonThor.h"
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
    virtual ~Vehicle(){}
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

struct Pod
{
    int level;
    Pod():level(57) {}
    Pod(int level): level(level) {}
    static std::string polyname() {return "type";}
    ThorsAnvil_PolyMorphicSerializerWithName(PolymorphicTest::Pod, pod);
};
struct HyperPod: public Pod
{
    int     size;
    int     time;
    HyperPod() {}
    HyperPod(int size, int time)
        : Pod(12)
        , size(size)
        , time(time)
    {}
    static std::string polyname() {return "type";}
    ThorsAnvil_PolyMorphicSerializerWithName(PolymorphicTest::HyperPod, hyper-pod);
};
struct StaticPod: public Pod
{
    int     speed;
    int     skill;
    StaticPod() {}
    StaticPod(int speed, int skill)
        : Pod(88)
        , speed(speed)
        , skill(skill)
    {}
    static std::string polyname() {return "type";}
    ThorsAnvil_PolyMorphicSerializerWithName(PolymorphicTest::HyperPod, static-pod);
};
struct User
{
    ~User() { delete transport; }
    int         age;
    Vehicle*    transport;
};
struct UserUniquePtr
{
  int age;
  std::unique_ptr<Vehicle> transport;
};
struct UserSharedPtr
{
  int age;
  std::shared_ptr<Vehicle> transport;
};
}

ThorsAnvil_MakeTrait(PolymorphicTest::Vehicle, speed);
ThorsAnvil_ExpandTrait(PolymorphicTest::Vehicle, PolymorphicTest::Car, make);
ThorsAnvil_ExpandTrait(PolymorphicTest::Vehicle, PolymorphicTest::Bike, stroke);
ThorsAnvil_MakeTrait(PolymorphicTest::Pod, level);
ThorsAnvil_ExpandTrait(PolymorphicTest::Pod, PolymorphicTest::HyperPod, size, time);
ThorsAnvil_ExpandTrait(PolymorphicTest::Pod, PolymorphicTest::StaticPod, speed, skill);
ThorsAnvil_MakeTrait(PolymorphicTest::User, age, transport);
ThorsAnvil_MakeTrait(PolymorphicTest::UserUniquePtr, age, transport);
ThorsAnvil_MakeTrait(PolymorphicTest::UserSharedPtr, age, transport);

ThorsAnvil_RegisterPolyMorphicTypeNamed(PolymorphicTest::Pod, pod)
ThorsAnvil_RegisterPolyMorphicTypeNamed(PolymorphicTest::HyperPod, hyper-pod)
ThorsAnvil_RegisterPolyMorphicTypeNamed(PolymorphicTest::StaticPod, static-pod)

TEST(PolymorphicTest, JsonNullPointer)
{
    PolymorphicTest::User    user1{10, nullptr};

    std::stringstream   data;
    data << ThorsAnvil::Serialize::jsonExporter(user1, false);
    std::string result = data.str();

    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(result, R"({"age":10,"transport":null})");
}
TEST(PolymorphicTest, JsonVehiclePointer)
{
    PolymorphicTest::User    user1{10, new PolymorphicTest::Vehicle(12)};

    std::stringstream   data;
    data << ThorsAnvil::Serialize::jsonExporter(user1, false);
    std::string result = data.str();

    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(result, R"({"age":10,"transport":{"__type":"PolymorphicTest::Vehicle","speed":12}})");
}
TEST(PolymorphicTest, JsonCarPointer)
{
    PolymorphicTest::User    user1{10, new PolymorphicTest::Car(16, "Turbo")};

    std::stringstream   data;
    data << ThorsAnvil::Serialize::jsonExporter(user1, false);
    std::string result = data.str();

    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(result, R"({"age":10,"transport":{"__type":"PolymorphicTest::Car","make":"Turbo","speed":16}})");
}

TEST(PolymorphicTest, JsonBikePointer)
{
    PolymorphicTest::User    user1{10, new PolymorphicTest::Bike(18, 7)};

    std::stringstream   data;
    data << ThorsAnvil::Serialize::jsonExporter(user1, false);
    std::string result = data.str();

    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(result, R"({"age":10,"transport":{"__type":"PolymorphicTest::Bike","stroke":7,"speed":18}})");
}

TEST(PolymorphicTest, JsonHyperPodPointer)
{
    std::unique_ptr<PolymorphicTest::Pod> pod(new PolymorphicTest::HyperPod{18, 7});

    std::stringstream   data;
    data << ThorsAnvil::Serialize::jsonExporter(pod, false);
    std::string result = data.str();

    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){ return std::isspace(x);}), std::end(result));
    EXPECT_EQ(result, R"({"type":"hyper-pod","size":18,"time":7,"level":12})");
}

TEST(PolymorphicTest, JsonReadNull)
{
    std::stringstream   stream(R"({"age":10,"transport":null})");
    PolymorphicTest::User                user1 {12, new PolymorphicTest::Vehicle(12)};

    stream >> ThorsAnvil::Serialize::jsonImporter(user1, false);
    EXPECT_EQ(user1.age, 10);
    EXPECT_EQ(user1.transport, nullptr);
}

TEST(PolymorphicTest, JsonReadVehicle)
{
    std::stringstream   stream(R"({"age":10,"transport":{"__type":"PolymorphicTest::Vehicle","speed":12}})");
    PolymorphicTest::User                user1 {12, new PolymorphicTest::Vehicle(13)};

    stream >> ThorsAnvil::Serialize::jsonImporter(user1, false);
    EXPECT_EQ(user1.age, 10);
    ASSERT_NE(user1.transport, nullptr);
    EXPECT_EQ(user1.transport->speed, 12);
}

TEST(PolymorphicTest, JsonReadCar)
{
    std::stringstream   stream(R"({"age":10,"transport":{"__type":"PolymorphicTest::Car","speed":16,"make":"Turbo"}})");
    PolymorphicTest::User                user1 {12, new PolymorphicTest::Vehicle(14)};

    stream >> ThorsAnvil::Serialize::jsonImporter(user1, false);
    EXPECT_EQ(user1.age, 10);
    ASSERT_NE(user1.transport, nullptr);
    EXPECT_EQ(user1.transport->speed, 16);

    PolymorphicTest::Car* car = dynamic_cast<PolymorphicTest::Car*>(user1.transport);
    ASSERT_NE(car, nullptr);
    EXPECT_EQ(car->make, "Turbo");
}

TEST(PolymorphicTest, JsonReadBike)
{
    std::stringstream   stream(R"({"age":10,"transport":{"__type":"PolymorphicTest::Bike","speed":18,"stroke":7}})");
    PolymorphicTest::User                user1 {12, new PolymorphicTest::Vehicle(15)};

    stream >> ThorsAnvil::Serialize::jsonImporter(user1, false);
    EXPECT_EQ(user1.age, 10);
    ASSERT_NE(user1.transport, nullptr);
    EXPECT_EQ(user1.transport->speed, 18);

    PolymorphicTest::Bike* bike = dynamic_cast<PolymorphicTest::Bike*>(user1.transport);
    ASSERT_NE(bike, nullptr);
    EXPECT_EQ(bike->stroke, 7);
}

TEST(PolymorphicTest, JsonReadHyperPod)
{
    std::stringstream       stream(R"({"type":"hyper-pod","size":18,"time":7,"level":12})");
    PolymorphicTest::Pod*    pod(new PolymorphicTest::Pod(15));

    stream >> ThorsAnvil::Serialize::jsonImporter(pod, false);
    ASSERT_NE(pod, nullptr);
    EXPECT_EQ(pod->level, 12);

    PolymorphicTest::HyperPod* hp = dynamic_cast<PolymorphicTest::HyperPod*>(pod);
    ASSERT_NE(hp, nullptr);
    EXPECT_EQ(hp->size, 18);
    EXPECT_EQ(hp->time, 7);
}

TEST(PolymorphicTest, BsonNullPointer)
{
    PolymorphicTest::User    user1{10, nullptr};

    std::stringstream   data(std::ios_base::out | std::ios_base::binary);;
    data << ThorsAnvil::Serialize::bsonExporter(user1, false);
    std::string result = data.str();

    static const char expectedRaw[]
                    = "\x19\x00\x00\x00"
                      "\x10" "age\x00" "\x0A\x00\x00\x00"
                      "\x0A" "transport\x00"
                      "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(result, expected);
    //NOTE INPUT ":10,"transport":null})");
}
TEST(PolymorphicTest, BsonVehiclePointer)
{
    PolymorphicTest::User    user1{10, new PolymorphicTest::Vehicle(12)};

    std::stringstream   data;
    data << ThorsAnvil::Serialize::bsonExporter(user1, false);
    std::string result = data.str();

    static const char expectedRaw[]
                    = "\x4E\x00\x00\x00"
                      "\x10" "age\x00" "\x0A\x00\x00\x00"
                      "\x03" "transport\x00"
                            "\x35\x00\x00\x00"
                            "\x02" "__type\x00" "\x19\x00\x00\x00" "PolymorphicTest::Vehicle\x00"
                            "\x10" "speed\x00"  "\x0C\x00\x00\x00"
                            "\x00"
                      "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(result, expected);
    //NOTE OUTPUT (result, R"({"age":10,"transport":{"__type":"PolymorphicTest::Vehicle","speed":12}})");
}
TEST(PolymorphicTest, BsonCarPointer)
{
    PolymorphicTest::User    user1{10, new PolymorphicTest::Car(16, "Turbo")};

    std::stringstream   data;
    data << ThorsAnvil::Serialize::bsonExporter(user1, false);
    std::string result = data.str();

    static const char expectedRaw[]
                    = "\x5A\x00\x00\x00"
                      "\x10" "age\x00" "\x0A\x00\x00\x00"
                      "\x03" "transport\x00"
                            "\x41\x00\x00\x00"
                            "\x02" "__type\x00" "\x15\x00\x00\x00" "PolymorphicTest::Car\x00"
                            "\x02" "make\x00"   "\x06\x00\x00\x00" "Turbo\x00"
                            "\x10" "speed\x00"  "\x10\x00\x00\x00"
                            "\x00"
                      "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(result, expected);
    //NOTE OUTPUT (result, R"({"age":10,"transport":{"__type":"PolymorphicTest::Car","speed":16,"make":"Turbo"}})");
}

TEST(PolymorphicTest, BsonBikePointer)
{
    PolymorphicTest::User    user1{10, new PolymorphicTest::Bike(18, 7)};

    std::stringstream   data;
    data << ThorsAnvil::Serialize::bsonExporter(user1, false);
    std::string result = data.str();

    static const char expectedRaw[]
                    = "\x57\x00\x00\x00"
                      "\x10" "age\x00" "\x0A\x00\x00\x00"
                      "\x03" "transport\x00"
                            "\x3E\x00\x00\x00"
                            "\x02" "__type\x00" "\x16\x00\x00\x00" "PolymorphicTest::Bike\x00"
                            "\x10" "stroke\x00" "\x07\x00\x00\x00"
                            "\x10" "speed\x00"  "\x12\x00\x00\x00"
                            "\x00"
                      "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(result, expected);
    //NOTE OUTPUT (result, R"({"age":10,"transport":{"__type":"PolymorphicTest::Bike","speed":18,"stroke":7}})");
}

TEST(PolymorphicTest, BsonReadNull)
{
    static const char inputRaw[]
                    = "\x19\x00\x00\x00"
                      "\x10" "age\x00" "\x0A\x00\x00\x00"
                      "\x0A" "transport\x00"
                      "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    //NOTE INPUT (R"({"age":10,"transport":null})");
    std::stringstream stream(input);
    PolymorphicTest::User                user1 {12, new PolymorphicTest::Vehicle(12)};

    stream >> ThorsAnvil::Serialize::bsonImporter(user1, false);
    EXPECT_EQ(user1.age, 10);
    EXPECT_EQ(user1.transport, nullptr);
}

TEST(PolymorphicTest, BsonReadVehicle)
{
    static const char inputRaw[]
                    = "\x4E\x00\x00\x00"
                      "\x10" "age\x00" "\x0A\x00\x00\x00"
                      "\x03" "transport\x00"
                            "\x35\x00\x00\x00"
                            "\x02" "__type\x00" "\x19\x00\x00\x00" "PolymorphicTest::Vehicle\x00"
                            "\x10" "speed\x00"  "\x0C\x00\x00\x00"
                            "\x00"
                      "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    //NOTE INPUT (R"({"age":10,"transport":{"__type":"PolymorphicTest::Vehicle","speed":12}})");
    std::stringstream stream(input);
    PolymorphicTest::User                user1 {12, new PolymorphicTest::Vehicle(13)};

    stream >> ThorsAnvil::Serialize::bsonImporter(user1, false);
    EXPECT_EQ(user1.age, 10);
    ASSERT_NE(user1.transport, nullptr);
    EXPECT_EQ(user1.transport->speed, 12);
}

TEST(PolymorphicTest, BsonReadCar)
{
    static const char inputRaw[]
                    = "\x5A\x00\x00\x00"
                      "\x10" "age\x00" "\x0A\x00\x00\x00"
                      "\x03" "transport\x00"
                            "\x41\x00\x00\x00"
                            "\x02" "__type\x00" "\x15\x00\x00\x00" "PolymorphicTest::Car\x00"
                            "\x10" "speed\x00"  "\x10\x00\x00\x00"
                            "\x02" "make\x00"   "\x06\x00\x00\x00" "Turbo\x00"
                            "\x00"
                      "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    //NOTE INPUT (R"({"age":10,"transport":{"__type":"PolymorphicTest::Car","speed":16,"make":"Turbo"}})");
    std::stringstream stream(input);
    PolymorphicTest::User                user1 {12, new PolymorphicTest::Vehicle(14)};

    stream >> ThorsAnvil::Serialize::bsonImporter(user1, false);
    EXPECT_EQ(user1.age, 10);
    ASSERT_NE(user1.transport, nullptr);
    EXPECT_EQ(user1.transport->speed, 16);

    PolymorphicTest::Car* car = dynamic_cast<PolymorphicTest::Car*>(user1.transport);
    ASSERT_NE(car, nullptr);
    EXPECT_EQ(car->make, "Turbo");
}

TEST(PolymorphicTest, BsonReadBike)
{
    static const char inputRaw[]
                    = "\x57\x00\x00\x00"
                      "\x10" "age\x00" "\x0A\x00\x00\x00"
                      "\x03" "transport\x00"
                            "\x3E\x00\x00\x00"
                            "\x02" "__type\x00" "\x16\x00\x00\x00" "PolymorphicTest::Bike\x00"
                            "\x10" "speed\x00"  "\x12\x00\x00\x00"
                            "\x10" "stroke\x00" "\x07\x00\x00\x00"
                            "\x00"
                      "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    //NOTE INPUT (R"({"age":10,"transport":{"__type":"PolymorphicTest::Bike","speed":18,"stroke":7}})");
    std::stringstream stream(input);
    PolymorphicTest::User                user1 {12, new PolymorphicTest::Vehicle(15)};

    stream >> ThorsAnvil::Serialize::bsonImporter(user1, false);
    EXPECT_EQ(user1.age, 10);
    ASSERT_NE(user1.transport, nullptr);
    EXPECT_EQ(user1.transport->speed, 18);

    PolymorphicTest::Bike* bike = dynamic_cast<PolymorphicTest::Bike*>(user1.transport);
    ASSERT_NE(bike, nullptr);
    EXPECT_EQ(bike->stroke, 7);
}


TEST(PolymorphicTest, UsingUniquePtr)
{
  std::stringstream data;

  { // Export
    PolymorphicTest::UserUniquePtr user1 { 10, std::make_unique<PolymorphicTest::Bike>(18, 7) };
    data << ThorsAnvil::Serialize::jsonExporter(user1);

    std::string result = data.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x) {return std::isspace(x);}), std::end(result));
    EXPECT_EQ(result, R"({"age":10,"transport":{"__type":"PolymorphicTest::Bike","stroke":7,"speed":18}})");
  }

  { // Import
    PolymorphicTest::UserUniquePtr user2;
    data >> ThorsAnvil::Serialize::jsonImporter(user2);

    EXPECT_EQ(user2.age, 10);
    PolymorphicTest::Bike& bike = dynamic_cast<PolymorphicTest::Bike&>(*user2.transport);
    EXPECT_EQ(bike.speed, 18);
    EXPECT_EQ(bike.stroke, 7);
  }
}

TEST(PolymorphicTest, UsingSharedPtrOldVersion)
{
  std::stringstream data;

  { // Export
    PolymorphicTest::UserSharedPtr user1 { 10, std::make_shared<PolymorphicTest::Bike>(18, 7) };
    data << ThorsAnvil::Serialize::jsonExporter(user1, ThorsAnvil::Serialize::PrinterConfig{}.setUseOldSharedPtr());

    std::string result = data.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x) {return std::isspace(x);}), std::end(result));
    EXPECT_EQ(result, R"({"age":10,"transport":{"__type":"PolymorphicTest::Bike","stroke":7,"speed":18}})");
  }

  { // Import
    PolymorphicTest::UserSharedPtr user2;
    data >> ThorsAnvil::Serialize::jsonImporter(user2, ThorsAnvil::Serialize::ParserConfig{}.setUseOldSharedPtr());

    EXPECT_EQ(user2.age, 10);
    PolymorphicTest::Bike& bike = dynamic_cast<PolymorphicTest::Bike&>(*user2.transport);
    EXPECT_EQ(bike.speed, 18);
    EXPECT_EQ(bike.stroke, 7);
  }
}
TEST(PolymorphicTest, UsingSharedPtr)
{
  std::stringstream data;

  { // Export
    PolymorphicTest::UserSharedPtr user1 { 10, std::make_shared<PolymorphicTest::Bike>(18, 7) };
    data << ThorsAnvil::Serialize::jsonExporter(user1);

    std::string result = data.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x) {return std::isspace(x);}), std::end(result));
    auto findS = result.find("sharedPtrName");
    auto findD = result.find("data");
    result.erase(findS + 15, findD - 1 - (findS + 15));
    EXPECT_EQ(result, R"({"age":10,"transport":{"sharedPtrName":"data":{"__type":"PolymorphicTest::Bike","stroke":7,"speed":18}}})");
  }

  { // Import
    PolymorphicTest::UserSharedPtr user2;
    data >> ThorsAnvil::Serialize::jsonImporter(user2);

    EXPECT_EQ(user2.age, 10);
    PolymorphicTest::Bike& bike = dynamic_cast<PolymorphicTest::Bike&>(*user2.transport);
    EXPECT_EQ(bike.speed, 18);
    EXPECT_EQ(bike.stroke, 7);
  }
}
