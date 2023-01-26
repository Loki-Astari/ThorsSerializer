#include <iostream>
#include <vector>
#include "ThorSerialize/JsonThor.h"

int main()
{
    std::vector<int>    data;
    using ThorsAnvil::Serialize::jsonImporter;
    using ThorsAnvil::Serialize::jsonExporter;

    std::cin >> jsonImporter(data);
    std::cout << jsonExporter(data) << "\n";
}
