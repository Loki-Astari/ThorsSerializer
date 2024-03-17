
#include "ThorSerialize/Traits.h"
#include "ThorSerialize/JsonThor.h"

#include <vector>
#include <fstream>
#include <iostream>

class Identifier
{
    public:
    std::string     name;
    std::string     bar;
    std::string     foo;
};
class Properties
{
    public:
    std::string     category;
    std::string     time;
    std::string     shouldRetry;
    std::string     Id;
};
class Data
{
    public:
    std::string     operation;
    Identifier      identifier;
    Properties      properties;
};

ThorsAnvil_MakeTrait(Identifier, name, bar, foo);
ThorsAnvil_MakeTrait(Properties, category, time, shouldRetry, Id);
ThorsAnvil_MakeTrait(Data, operation, identifier, properties);

int main()
{
    using ThorsAnvil::Serialize::jsonImporter;
    using ThorsAnvil::Serialize::jsonExporter;

    std::vector<Data>   objects;

    std::ifstream       file("file.json");

    if (file >> jsonImporter(objects)) {
        std::cout << "Read Worked\n";

        std::cout << jsonExporter(objects);
    }
}



