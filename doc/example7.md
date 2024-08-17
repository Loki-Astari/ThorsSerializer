![ThorStream](../img/stream.jpg)

## Example-1 [See doc/example1.cpp](example1.cpp)
```C++
    #include <iostream>
    #include <fstream>
    #include <vector>
    #include <string>
    #include "ThorSerialize/Traits.h"
    #include "ThorSerialize/JsonThor.h"

    struct Component
    {
        std::string                 type;
        std::vector<std::string>    axis;
    };
    struct Data
    {
        std::vector<Component>      components;
    };

    // Declare the traits.
    // Specifying what members need to be serialized.
    ThorsAnvil_MakeTrait(Component, type, axis);
    ThorsAnvil_MakeTrait(Data, components);

    int main()
    {
        using ThorsAnvil::Serialize::jsonImporter;
        using ThorsAnvil::Serialize::jsonExporter;

        Data                data1;
        Data                data2;
        // See: https://github.com/Loki-Astari/ThorsSerializer/blob/master/doc/example7.json
        std::ifstream       file("example7.json");

        if (file >> jsonImporter(data1)) {
            std::cout << "Object Read OK\n";
            std::cout << jsonExporter(data1) << "\n";
        }
        else {
            std::cout << "Object Read FAIL\n";
        }


        if (file >> jsonImporter(data2)) {
            std::cout << "Object Read OK\n";
            std::cout << jsonExporter(data2) < "\n";
        }
        else {
            std::cout << "Object Read FAIL\n";
        }
    }
```

### Build and run
```bash
    > g++ -std=c++20 example7.cpp -lThorSerialize -lThorsLogging
    > # Note on mac you may need to add -I/opt/homebrew/include -L/opt/homebrew/lib/ on Mac's with M1 chip.
    > ./a.out
Object Read OK

    {
        "components": [
            {
                "type": "mesh",
                "axis": [ "x", "y", "z"]
            }]
    }
Object Read FAIL

```
