#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "ThorSerialize/Traits.h"
#include "ThorSerialize/JsonThor.h"



class Car1
{
    public:
        Car1(std::string color, uint16_t speed, uint32_t price) :
            Color(color),
            Speed(speed),
            Price(price){};

        std::string getColor(){return Color;};
        uint16_t getSpeed(){return Speed;};
        uint32_t getPrice(){return Price;};
    private:
        // Note: Member names must match JSON names.
        friend class ThorsAnvil::Serialize::Traits<Car1>;
        std::string Color;
        uint16_t    Speed;
        uint32_t    Price;
};
struct AllCars
{
    std::map<std::string, Car1>      myCars;
};


ThorsAnvil_MakeTrait(Car1, Color, Price, Speed);
ThorsAnvil_MakeTrait(AllCars, myCars);

int main() 
{
    std::map<std::string, Car1>      myGarage;
    myGarage.emplace("car1", Car1{"red", 200, 10000});
    myGarage.emplace("car2", Car1{"blue", 666, 16000});
    myGarage.emplace("car3", Car1{"yellow", 50, 7500});
    myGarage.emplace("car4", Car1{"green", 10, 750});

    std::ofstream outputJSONfile("pretty.json");

    using ThorsAnvil::Serialize::jsonExporter;
    outputJSONfile << jsonExporter(myGarage);
}
