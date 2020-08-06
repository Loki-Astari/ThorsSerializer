
#include "ThorSerialize/Serialize.h"
#include "ThorSerialize/Serialize.tpp"
#include "ThorSerialize/Traits.h"
#include "ThorSerialize/JsonThor.h"
#include <string>
#include <sstream>
#include <iostream>

struct Vehicle
{
    Vehicle(){}
    Vehicle(int speed)
        : speed(speed)
    {}
    virtual ~Vehicle() {}
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

int main()
{
    Vehicle*    init = new Bike(15, 2);

    std::stringstream   stream;
    stream << ThorsAnvil::Serialize::jsonExporter(init);
    std::cout << ThorsAnvil::Serialize::jsonExporter(init) << "\n\n";

    Vehicle*    result = nullptr;
    std::cout << ThorsAnvil::Serialize::jsonExporter(result) << "\n\n";
    stream >> ThorsAnvil::Serialize::jsonImporter(result);

    std::cout << ThorsAnvil::Serialize::jsonExporter(result) << "\n\n";
}

