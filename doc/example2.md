![ThorStream](../img/stream.jpg)

## Example-2: [see doc/example2.cpp](example2.cpp)
```C++
    #include <string>
    #include "ThorSerialize/Traits.h"
    #include "ThorSerialize/SerUtil.h"
    #include "ThorSerialize/JsonThor.h"

    /* A class that you want to serialize. */
    class MyClass
    {
        int         data1;
        float       data2;
        std::string data3;
        public:
            MyClass(int data1, float data2, std::string const& data3)
                : data1(data1)
                , data2(data2)
                , data3(data3)
            {}

        // This is only required if the members are private.
        friend struct ThorsAnvil::Serialize::Traits<MyClass>;
    };


    /*
     * Though there is no code involved, you do need to set up
     * this structure to tell the library what fields need to be serialized.
     * To do this use the macro:  ThorsAnvil_MakeTrait()
     * Specifying your class, and a list of members to serialize.
     */
    ThorsAnvil_MakeTrait(MyClass, data1, data2, data3);
```
This allows us to import and export object of the above class really easily.
```C++
    int main()
    {
        using ThorsAnvil::Serialize::jsonExporter;
        using ThorsAnvil::Serialize::OutputType;

        MyClass   data {56, 23.456, "Hi there"};


        // This generates a simple JSON Object (wordy)
        std::cout << "Version 1";
        std::cout << jsonExporter(data) << "\n\n\n";

        // This generates a compact JSON 
        std::cout << "Version 2 (Stream)\n";
        std::cout << jsonExporter(data, OutputType::Stream) << "\n\n\n";

        // Standard containers work automatically.
        // As long as the type held by the container has had an appropriate
        // Traits declaration.
        std::vector<MyClass>   vec(4, data);
        std::cout << "Vector";
        std::cout << jsonExporter(vec) << "\n";
    }
```

This generates:

```bash
    > g++ -std=c++20 -o example2 example2.cpp -lThorSerialize -lThorsLogging
    > # Note on mac you may need to add -I/opt/homebrew/include -L/opt/homebrew/lib/ on Mac's with M1 chip.
    > ./example2
    Version 1
    {
        "data1": 56,
        "data2": 23.456,
        "data3": "Hi there"
    }


    Version 2 (Stream)
    {"data1":56,"data2":23.456,"data3":"Hi there"}


    Vector
    [
        {
            "data1": 56,
            "data2": 23.456,
            "data3": "Hi there"
        },
        {
            "data1": 56,
            "data2": 23.456,
            "data3": "Hi there"
        },
        {
            "data1": 56,
            "data2": 23.456,
            "data3": "Hi there"
        },
        {
            "data1": 56,
            "data2": 23.456,
            "data3": "Hi there"
        }
    ]
```
