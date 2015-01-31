

#include "Serialize.h"
#include "JsonParser.h"
#include "JsonPrinter.h"
#include <string>
#include <sstream>

namespace TA = ThorsAnvil::Serialization;


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
        using Members = std::tuple< std::pair<char const*, int Test::*>,
 //                                   std::pair<char const*, float Test::*>,
                                    std::pair<char const*, double Test::*>,
                                    std::pair<char const*, bool Test::*>,
                                    std::pair<char const*, std::string Test::*>
                                  >;
        static constexpr TraitType  type = TraitType::Map;
        static Members const& getMembers()
        {
            static constexpr Members    members{{"anInt", &Test::anInt},
//                                                {"aFloat", &Test::aFloat},
                                                {"aDouble", &Test::aDouble},
                                                {"aBool", &Test::aBool},
                                                {"aString", &Test::aString}
                                               };
            return members;
        }
};
    }
}


void test()
{
    Test                        object1{1, 2.3, 4.5, true, "Test"};
    Test                        object2{6, 7.8, 9.10, false, "This is a string"};

    std::stringstream           data("{\"anInt\": 11, \"aFloat\": 12.13, \"aDouble\": 14.15, \"aBool\": true, \"aString\": \"String from a stream\"}");
    TA::JsonParser              jsonParser(data);
    TA::DeSerializer<Test>      parser(jsonParser);

    parser.parse(object1);
    //parser.parse(object2);

    TA::JsonPrinter             yamlPrinter(std::cout);
    TA::Serializer<Test>        printer(yamlPrinter);

    printer.print(object1);
    printer.print(object2);
}

int main()
{
    try
    {
        test();
    }
    catch(char const* msg)
    {
        std::cerr << "Exception: " << msg << "\n";
    }
}

