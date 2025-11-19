#ifndef THORSANVIL_SERIALIZE_TEST_POLYMORPHIC_TEST_H
#define THORSANVIL_SERIALIZE_TEST_POLYMORPHIC_TEST_H

#include "Serialize.h"
#include "Traits.h"
#include "SerUtil.h"

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
    ThorsAnvil_TypeFieldName(type)
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
    ThorsAnvil_TypeFieldName(type);
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
    ThorsAnvil_TypeFieldName(type);
    ThorsAnvil_PolyMorphicSerializerWithName(PolymorphicTest::HyperPod, static-pod);
};
struct VarHyperPod
{
    int     level;
    int     size;
    int     time;
    VarHyperPod() {}
    VarHyperPod(int size, int time)
        : level(12)
        , size(size)
        , time(time)
    {}
    ThorsAnvil_TypeFieldName(type);
    ThorsAnvil_VariantSerializerWithName(PolymorphicTest::HyperPod, hyper-pod);
};
struct VarStaticPod
{
    int     level;
    int     speed;
    int     skill;
    VarStaticPod() {}
    VarStaticPod(int speed, int skill)
        : level(88)
        , speed(speed)
        , skill(skill)
    {}
    ThorsAnvil_TypeFieldName(type);
    ThorsAnvil_VariantSerializerWithName(PolymorphicTest::HyperPod, static-pod);
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
ThorsAnvil_MakeTrait(PolymorphicTest::VarHyperPod, size, time, level);
ThorsAnvil_MakeTrait(PolymorphicTest::VarStaticPod, speed, skill, level);
ThorsAnvil_MakeTrait(PolymorphicTest::User, age, transport);
ThorsAnvil_MakeTrait(PolymorphicTest::UserUniquePtr, age, transport);
ThorsAnvil_MakeTrait(PolymorphicTest::UserSharedPtr, age, transport);

#endif
