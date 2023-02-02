[![Build Status](https://travis-ci.org/Loki-Astari/ThorsSerializer.svg?branch=master)](https://travis-ci.org/Loki-Astari/ThorsSerializer)

![ThorStream](../img/stream.jpg)

## Example-E [See doc/exampleE.cpp](exampleE.cpp)
````c++
    #include <iostream>
    #include <vector>
    #include "ThorSerialize/JsonThor.h"

    enum class EnumType : int {
        A, B, C
    };

    struct MyStruct {
        EnumType    e;
        std::string s;
    };

    ThorsAnvil_MakeEnum(EnumType, A, B, C);
    ThorsAnvil_MakeTrait(MyStruct, e, s);

    int main()
    {
        using ThorsAnvil::Serialize::jsonImporter;
        using ThorsAnvil::Serialize::jsonExporter;

        MyStruct    val;
        std::cin >> jsonImporter(val);
        std::cout << jsonExporter(val) << "\n";
    }
````

### Build and run
````bash
    > g++ -std=c++17 example0.cpp -lThorSerialize17 -lThorsLogging17
    > # Note on mac you may need to add -I/opt/homebrew/include -L/opt/homebrew/lib/ on Mac's with M1 chip.
    > echo '{"e": "A", "s": "This string"}' | ./a.out
    {
        "e": "A",
        "s": "This string"
    }

````
