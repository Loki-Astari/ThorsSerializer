

#include "Serialize.h"
#include <string>

namespace TA = ThorsAnvil::Serialization;

class JsonParser: public TA::ParserInterface
{
    public:
        using TA::ParserInterface::ParserInterface;
        virtual ParserToken getToken()              {return ParserInterface::ParserToken::Error;}
        virtual std::string getKey()                {return "XX";}
        virtual void    getValue(bool& value)       {value = true;}
        virtual void    getValue(int& value)        {value = 5;}
        virtual void    getValue(double& value)     {value = 6.7;}
        virtual void    getValue(std::nullptr_t)    {}
        virtual void    getValue(std::string& value){value = "10 is a number";}
};

class YamlPrinter: public TA::PrinterInterface
{
    class Indent
    {
        int     size;
        public:
            Indent(int size) : size(size) {}
            friend std::ostream& operator<<(std::ostream& stream, Indent const& data)
            {
                return stream << std::string(data.size, '\t');
            }
    };
    struct Comma
    {
        bool& needComma;
        Comma(bool& needComma): needComma(needComma) {}
        friend std::ostream& operator<<(std::ostream& stream, Comma const& data)
        {
            stream << (data.needComma ? "," : " ");
            data.needComma = true;
            return stream;
        }
    };

    std::vector<std::pair<bool, TA::TraitType>> state;
    public:
        using TA::PrinterInterface::PrinterInterface;
        virtual void openMap()
        {
            output << Indent(state.size()) << "{\n";
            state.emplace_back(false, TA::TraitType::Map);
        }
        virtual void closeMap()
        {
            state.pop_back();
            output << Indent(state.size()) << "}\n";
        }
        virtual void openArray()
        {
            output << Indent(state.size()) << "[\n";
            state.emplace_back(false, TA::TraitType::Map);
        }
        virtual void closeArray()
        {
            state.pop_back();
            output << Indent(state.size()) << "]\n";
        }

        virtual void addKey(std::string const& key)         {output << Indent(state.size()) << Comma(state.back().first) << '"' << key << '"' << ':';}
        virtual void addValue(bool value)                   {output << std::boolalpha << value << "\n";}
        virtual void addValue(int value)                    {output << value << "\n";}
        virtual void addValue(double value)                 {output << value << "\n";}
        virtual void addValue(std::nullptr_t)               {output << "Null\n";}
        virtual void addValue(std::string const& value)     {output << '"' << value << '"' << "\n";}
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


int main()
{
    Test                        object1{5, 6.7, 8.9, true, "Test"};
    Test                        object2{3, 0.14159269, 8, false, "This is a string"};

    JsonParser                  jsonParser(std::cin);
    TA::DeSerializer<Test>      parser(jsonParser);

    parser.parse(object1);
    parser.parse(object2);

    YamlPrinter                 yamlPrinter(std::cout);
    TA::Serializer<Test>        printer(yamlPrinter);

    printer.print(object1);
    printer.print(object2);
}

