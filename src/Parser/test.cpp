

#include "Serialize.h"
#include <string>

namespace TA = ThorsAnvil::Serialization;

class JsonParser: public TA::ParserInterface
{
};

class YamlPrinter: public TA::PrinterInterface
{
};

class Test
{
    public:
        int             anInt;
        float           aFloat;
        double          aDouble;
        bool            aBool;
        std::string     aString;
};


int main()
{
    Test                        object1{5, 6.7, 8.9, true, "Test"};
    Test                        object2{3, 0.14159269, 8, false, "This is a string"};

    JsonParser                  jsonParser;
    TA::DeSerializer<Test>      parser(jsonParser);

    parser.parse(object1);
    parser.parse(object2);

    YamlPrinter                 yamlPrinter;
    TA::Serializer<Test>        printer(yamlPrinter);

    printer.print(object1);
    printer.print(object2);
}

