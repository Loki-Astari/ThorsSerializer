#include <string>
#include "ThorSerialize/Traits.h"
#include "ThorSerialize/SerUtil.h"
#include "ThorSerialize/JsonThor.h"

/* A class that you want to serialize. */
class MyClass
{
    std::string     H;
    int             N;
    int             D1;
    int             D2;
    friend struct ThorsAnvil::Serialize::Traits<MyClass>;

    public:
        MyClass(std::string const& h, int n, int d1, int d2)
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
ThorsAnvil_MakeTrait(MyClass, H, N, D1, D2);

int main()
{
    using ThorsAnvil::Serialize::jsonExporter;
    using ThorsAnvil::Serialize::PrinterInterface;
    using namespace std::string_literals;

    MyClass   data {"1"s, 3, 3, 150};


    // This generates a simple Json Object (wordy)
    std::cout << "Version 1\n";
    std::cout << jsonExporter(data) << "\n\n\n";

    // This generates a compact Json 
    std::cout << "Version 2 (Stream)\n";
    std::cout << jsonExporter(data, PrinterInterface::OutputType::Stream) << "\n\n\n";
}


