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

int main()
{
    using ThorsAnvil::Serialize::jsonExporter;
    using ThorsAnvil::Serialize::PrinterInterface;

    MyClass   data {56, 23.456, "Hi there"};


    // This generates a simple Json Object (wordy)
    std::cout << "Version 1\n";
    std::cout << jsonExporter(data) << "\n\n\n";

    // This generates a compact Json 
    std::cout << "Version 2 (Stream)\n";
    std::cout << jsonExporter(data, PrinterInterface::OutputType::Stream) << "\n\n\n";

    // Standard containers work automatically.
    // As long as the type held by the container has had an appropriate
    // Traits declaration.
    std::vector<MyClass>   vec(4, data);
    std::cout << "Vector\n";
    std::cout << jsonExporter(vec) << "\n";
}


