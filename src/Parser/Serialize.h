
#ifndef THORS_ANVIL_SERIALIZATION_SERIALIZE_H
#define THORS_ANVIL_SERIALIZATION_SERIALIZE_H

#include <iostream>
#include <vector>

namespace ThorsAnvil
{
    namespace Serialization
    {

class ParserInterface
{
    public:
        enum class ParserToken {Error, MapStart, MapEnd, ArrayStart, ArrayEnd, Key, Value};
        std::istream&   input;

        ParserInterface(std::istream& input)
            : input(input)
        {}
        virtual ~ParserInterface() {}
        virtual ParserToken     getToken()              = 0;
        virtual std::string     getKey()                = 0;
        virtual void    getValue(bool& value)           = 0;
        virtual void    getValue(int& value)            = 0;
        virtual void    getValue(double& value)         = 0;
        virtual void    getValue(std::nullptr_t)        = 0;
        virtual void    getValue(std::string& value)    = 0;
};
class PrinterInterface
{
    public:
        std::ostream&   output;

        PrinterInterface(std::ostream& output)
            : output(output)
        {}
        virtual ~PrinterInterface() {}
        virtual void openMap()      = 0;
        virtual void closeMap()     = 0;
        virtual void openArray()    = 0;
        virtual void closeArray()   = 0;

        virtual void addKey(std::string const& key)     = 0;
        virtual void addValue(bool value)               = 0;
        virtual void addValue(int value)                = 0;
        virtual void addValue(double value)             = 0;
        virtual void addValue(std::nullptr_t)           = 0;
        virtual void addValue(std::string const& value) = 0;
};

enum class TraitType {Invalid, Parent, Value, Map, Array};
template<typename T>
class Traits
{
    public:
        static constexpr TraitType type = TraitType::Invalid;
};

class DeSerializeMember
{
    using ParserToken = ParserInterface::ParserToken;
    public:
        template<typename T, typename Member>
        DeSerializeMember(ParserInterface& parser, std::string const& key, T& object, Member const& memberInfo)
        {
            if (key.compare(memberInfo.first) == 0)
            {
                parser.getValue(object.*(memberInfo.second));
            }
        }
};

template<typename T>
class DeSerializer
{
    using ParserToken = ParserInterface::ParserToken;
    ParserInterface&    parser;

    template<typename Members, std::size_t... Seq>
    void scanEachMember(std::string const& key, T& object, Members const& member, std::index_sequence<Seq...> const&)
    {
        std::make_tuple(DeSerializeMember(parser, key, object, std::get<Seq>(member))...);
    }
    template<typename Members>
    void scanMembers(std::string const& key, T& object, Members& members)
    {
        scanEachMember(key, object, members, std::make_index_sequence<std::tuple_size<Members>::value>());
    }
    public:
        DeSerializer(ParserInterface& parser)
            : parser(parser)
        {}

        void parse(T& object)
        {

            ParserToken     tokenType = parser.getToken();
            if (tokenType != ParserToken::MapStart)
            {   throw "Invalid Object Start";
            }

            while((tokenType = parser.getToken()) != ParserToken::MapEnd)
            {
                if (tokenType != ParserToken::Key)
                {   throw "Expecting key token";
                }
                std::string key = parser.getKey();
                scanMembers(key, object, Traits<T>::getMembers());
            }
        }
};

template<TraitType traitType>
class SerializerForBlock
{
    static_assert(traitType != TraitType::Invalid, "Invalid Serialization TraitType. This usually means you have not define ThorsAnvil::Serialization::Traits<Your Type>");
    PrinterInterface&     printer;
    public:
         SerializerForBlock(PrinterInterface& printer);
        ~SerializerForBlock();
};

// Need to define this for TraitType::Parent
// But have not examined that yet

template<> SerializerForBlock<TraitType::Value>::SerializerForBlock(PrinterInterface& printer)   :printer(printer)   {}
template<> SerializerForBlock<TraitType::Value>::~SerializerForBlock()                                               {}

template<> SerializerForBlock<TraitType::Map>::SerializerForBlock(PrinterInterface& printer)     :printer(printer)   {printer.openMap();}
template<> SerializerForBlock<TraitType::Map>::~SerializerForBlock()                                                 {printer.closeMap();}

template<> SerializerForBlock<TraitType::Array>::SerializerForBlock(PrinterInterface& printer)   :printer(printer)   {printer.openArray();}
template<> SerializerForBlock<TraitType::Array>::~SerializerForBlock()                                               {printer.closeArray();}

class SerializeMember
{
    public:
        template<typename T, typename M>
        SerializeMember(PrinterInterface& printer, T const& object, M const& memberInfo)
        {
            printer.addKey(memberInfo.first);
            printer.addValue(object.*(memberInfo.second));
        }
};

template<typename T>
class Serializer
{
    PrinterInterface& printer;

    template<typename Members, std::size_t... Seq>
    void printEachMember(T const& object, Members const& member, std::index_sequence<Seq...> const&)
    {
        std::make_tuple(SerializeMember(printer, object, std::get<Seq>(member))...);
    }
    template<typename Members>
    void printMembers(T const& object, Members const& members)
    {
        printEachMember(object, members, std::make_index_sequence<std::tuple_size<Members>::value>());
    }
    public:
        Serializer(PrinterInterface& printer)
            : printer(printer)
        {}

        void print(T const& object)
        {
            SerializerForBlock<Traits<T>::type>     block(printer);

            printMembers(object, Traits<T>::getMembers());
        }
};

    }
}

#endif

