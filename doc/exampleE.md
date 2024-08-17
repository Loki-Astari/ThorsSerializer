![ThorStream](../img/stream.jpg)

## Example-E [See doc/exampleE.cpp](exampleE.cpp)
```C++
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

    // ThorsAnvil_MakeEnum is still supported for backwards compatibility.
    // But this functionality has been replaces by magic_enum
    // Please see: https://github.com/Neargye/magic_enum

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
```

### Build and run
```bash
    > g++ -std=c++20 example0.cpp -lThorSerialize -lThorsLogging
    > # Note on mac you may need to add -I/opt/homebrew/include -L/opt/homebrew/lib/ on Mac's with M1 chip.
    > echo '{"e": "A", "s": "This string"}' | ./a.out
    {
        "e": "A",
        "s": "This string"
    }

```
