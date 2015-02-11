
#ifndef THORS_ANVIL_SERIALIZE_SERIALIZE_H
#define THORS_ANVIL_SERIALIZE_SERIALIZE_H

#include <iostream>
#include <vector>
#include <cstdlib>

namespace ThorsAnvil
{
    namespace Serialize
    {

class ParserInterface
{
    public:
        enum class ParserToken {Error, DocStart, DocEnd, MapStart, MapEnd, ArrayStart, ArrayEnd, Key, Value};
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
        virtual void    getValue(char*& value)          = 0;
        virtual void    getValue(std::string& value)    = 0;
};
class PrinterInterface
{
    public:
        enum class OutputType {Default, Stream, Config};
        // Default:     What ever the implementation likes.
        // Stream:      Compressed for over the wire protocol.
        // Config:      Human readable (potentially config file like)

        std::ostream&   output;
        OutputType      characteristics;

        PrinterInterface(std::ostream& output, OutputType characteristics = OutputType::Default)
            : output(output)
            , characteristics(characteristics)
        {}
        virtual ~PrinterInterface() {}
        virtual void openDoc()      = 0;
        virtual void closeDoc()     = 0;
        virtual void openMap()      = 0;
        virtual void closeMap()     = 0;
        virtual void openArray()    = 0;
        virtual void closeArray()   = 0;

        virtual void addKey(std::string const& key)     = 0;
        virtual void addValue(bool value)               = 0;
        virtual void addValue(int value)                = 0;
        virtual void addValue(double value)             = 0;
        virtual void addValue(std::nullptr_t)           = 0;
        virtual void addValue(char const* value)        = 0;
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
            // Note:
            //  Note: all elements are going to have a DocStart/DocEnd pair
            //  Just the outer set. So that is something that we will need to deal with
            //
            //  Note: We also need to take care of arrays at the top level
            //  We will get that in the next version
            ParserToken     tokenType = parser.getToken();
            if (tokenType != ParserToken::DocStart)
            {   throw std::runtime_error("ThorsAnvil::Serialize::Serialize: Invalid Doc Start");
            }

            tokenType = parser.getToken();
            if (tokenType != ParserToken::MapStart)
            {   throw std::runtime_error("ThorsAnvil::Serialize::Serialize: Invalid Object Start");
            }

            while((tokenType = parser.getToken()) != ParserToken::MapEnd)
            {
                if (tokenType != ParserToken::Key)
                {   throw std::runtime_error("ThorsAnvil::Serialize::Serialize: Expecting key token");
                }
                std::string key = parser.getKey();

                tokenType = parser.getToken();
                if (tokenType != ParserToken::Value)
                {   throw std::runtime_error("ThorsAnvil::Serialize::Serialize: Expecting Value Token");
                }
                scanMembers(key, object, Traits<T>::getMembers());
            }

            if (tokenType == ParserToken::DocEnd)
            {   throw std::runtime_error("ThorsAnvil::Serialize::Serialize: Expected Doc End");
            }
        }
};

template<TraitType traitType>
class SerializerForBlock
{
    static_assert(traitType != TraitType::Invalid, "Invalid Serialize TraitType. This usually means you have not define ThorsAnvil::Serialize::Traits<Your Type>");
    PrinterInterface&     printer;
    public:
         SerializerForBlock(PrinterInterface& printer);
        ~SerializerForBlock();
};

// Need to define this for TraitType::Parent
// But have not examined that yet

template<> inline SerializerForBlock<TraitType::Value>::SerializerForBlock(PrinterInterface& printer)   :printer(printer)   {}
template<> inline SerializerForBlock<TraitType::Value>::~SerializerForBlock()                                               {}

template<> inline SerializerForBlock<TraitType::Map>::SerializerForBlock(PrinterInterface& printer)     :printer(printer)   {printer.openMap();}
template<> inline SerializerForBlock<TraitType::Map>::~SerializerForBlock()                                                 {printer.closeMap();}

template<> inline SerializerForBlock<TraitType::Array>::SerializerForBlock(PrinterInterface& printer)   :printer(printer)   {printer.openArray();}
template<> inline SerializerForBlock<TraitType::Array>::~SerializerForBlock()                                               {printer.closeArray();}

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
        {
            printer.openDoc();
        }
        ~Serializer()
        {
            printer.closeDoc();
        }

        void print(T const& object)
        {
            SerializerForBlock<Traits<T>::type>     block(printer);

            printMembers(object, Traits<T>::getMembers());
        }
};

    }
}

#endif

