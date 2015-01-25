

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

namespace ThorsAnvil
{
    namespace Serialization
    {
template<>
class Traits<Test>
{
    public:
        using Members = std::tuple<std::pair<char const*, int Test::*>, std::pair<char const*, float Test::*>>;
        static constexpr TraitType  type = TraitType::Map;
        static Members const& getMember()
        {
            static constexpr Members    members{{"anInt", &Test::anInt}, {"aFloat", &Test::aFloat}};
            return members;
        }
};
    }
}


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

