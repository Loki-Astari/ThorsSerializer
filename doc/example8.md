![ThorStream](../img/stream.jpg)

## Example-1 [See doc/example1.cpp](example1.cpp)
Input File: **file.json**

```json
[
    {
        "operation": "test",
        "identifier": {
            "name": "1",
            "bar": "sandbox",
            "foo": "foo"
        },
        "properties": {
            "category": "xxx",
            "time": "yyy",
            "shouldRetry": "False",
            "Id": "vvvv"
        }
    }
]
```

Source file: **example8.cpp**

```C++
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
```

### Build and run
```bash
    > # Assume you have installed ThorsAnvil from Brew
    > # brew install ThorsSerializer
    > g++ -std=c++20 example8.cpp -lThorSerialize -lThorsLogging
    > # Note on mac you may need to add -I/opt/homebrew/include -L/opt/homebrew/lib/ on Mac's with M1 chip.
    > ./a.out
Object Read OK

    Read Worked
     [
            {
                "operation": "test",
                "identifier":
                {
                    "name": "1",
                    "bar": "sandbox",
                    "foo": "foo"
                },
                "properties":
                {
                    "category": "xxx",
                    "time": "yyy",
                    "shouldRetry": "False",
                    "Id": "vvvv"
                }
            }]

```

Alternative Build using header only library:
```bash
    > git clone https://github.com/Neargye/magic_enum.git ~/MyHeaders/MagicEnum
    > git clone --single-branch --branch header-only https://github.com/Loki-Astari/ThorsSerializer.git ~/MyHeaders/ThorsSerializer
    > 
    > g++ -std=c++20 example8.cpp -I ~/MyHeaders/MagicEnum/include/magic_enum -I ~/MyHeaders/ThorsSerializer
    > ./a.out
Object Read OK

    Read Worked
     [
            {
                "operation": "test",
                "identifier":
                {
                    "name": "1",
                    "bar": "sandbox",
                    "foo": "foo"
                },
                "properties":
                {
                    "category": "xxx",
                    "time": "yyy",
                    "shouldRetry": "False",
                    "Id": "vvvv"
                }
            }]

```
