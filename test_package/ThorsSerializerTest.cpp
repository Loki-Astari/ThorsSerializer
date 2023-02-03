#include "ThorSerialize/JsonThor.h"
#include "ThorSerialize/SerUtil.h"
#include <sstream>
#include <iostream>
#include <string>

struct HomeBrewBlock
{
    std::string             key;
    int                     code;
};
ThorsAnvil_MakeTrait(HomeBrewBlock, key, code);

int main()
{
    using ThorsAnvil::Serialize::jsonImporter;
    using ThorsAnvil::Serialize::jsonExporter;

    std::stringstream   inputData(R"({"key":"XYZ","code":37373})");

    HomeBrewBlock    object;
    inputData >> jsonImporter(object);

    if (object.key != "XYZ" || object.code != 37373)
    {
        std::cerr << "Fail\n";
        return 1;
    }
    std::cerr << "OK\n";
    return 0;
}
