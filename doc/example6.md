![ThorStream](../img/stream.jpg)

## Example-6: [see doc/example6.cpp](example6.cpp)
```C++
#include <string>
#include "ThorSerialize/Traits.h"
#include "ThorSerialize/SerUtil.h"
#include "ThorSerialize/JsonThor.h"

/* A class that you want to serialize. */
class MyClass1
{
    std::string     H;
    int             N;
    int             D1;
    int             D2;
    friend struct ThorsAnvil::Serialize::Traits<MyClass1>;

    public:
        MyClass1(std::string const& h, int n, int d1, int d2)
            : H(h)
            , N(n)
            , D1(d1)
            , D2(d2)
        {}
};


/*
 * Though there is no code involved, you do need to set up
 * this structure to tell the library what fields need to be serialized.
 * To do this use the macro:  ThorsAnvil_MakeTrait()
 * Specifying your class, and a list of members to serialize.
 */
ThorsAnvil_MakeTrait(MyClass1, H, N, D1, D2);

```
This allows us to import and export object of the above class really easily.
```C++
int main()
{
    using ThorsAnvil::Serialize::jsonExporter;
    using ThorsAnvil::Serialize::OutputType;
    using namespace std::string_literals;

    MyClass1   data {"1"s, 3, 3, 150};


    // This generates a simple JSON Object (wordy)
    std::cout << "Version 1";
    std::cout << jsonExporter(data) << "\n\n\n";

    // This generates a compact JSON 
    std::cout << "Version 2 (Stream)\n";
    std::cout << jsonExporter(data, OutputType::Stream) << "\n\n\n";
}
```

This generates:

```bash
    > g++ -std=c++20 -o example6 example6.cpp -lThorSerialize -lThorsLogging
    > # Note on mac you may need to add -I/opt/homebrew/include -L/opt/homebrew/lib/ on Mac's with M1 chip.
    > ./example6
    Version 1
    {
        "H": "1",
        "N": 3,
        "D1": 3,
        "D2": 150
    }


    Version 2 (Stream)
    {"H":"1","N":3,"D1":3,"D2":150}
```
