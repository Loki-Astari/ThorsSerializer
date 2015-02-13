
#ifndef THORS_ANVIL_SERIALIZE_SERIALIZE_H
#define THORS_ANVIL_SERIALIZE_SERIALIZE_H

#include <iostream>
#include <vector>
#include <cstdlib>
#include "Traits.h"

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

class Serializer;
class DeSerializer;

template<TraitType type, typename T>
class ApplyActionToParent
{
    public:
        // Default do nothing.
        void printParentMembers(Serializer&, T const&)                      {}
        void scanParentMember(DeSerializer&, std::string const&, T const&)  {}
};

template<typename T>
class ApplyActionToParent<TraitType::Parent, T>
{
    public:
        void printParentMembers(Serializer& serializer, T const&);
        void scanParentMember(DeSerializer&, std::string const&, T const&);
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

class DeSerializer
{
    using ParserToken = ParserInterface::ParserToken;
    ParserInterface&    parser;

    template<typename T, typename Members, std::size_t... Seq>
    void scanEachMember(std::string const& key, T& object, Members const& member, std::index_sequence<Seq...> const&)
    {
        std::make_tuple(DeSerializeMember(parser, key, object, std::get<Seq>(member))...);
    }
    template<typename T, typename Members>
    void scanMembers(std::string const& key, T& object, Members& members)
    {
        scanEachMember(key, object, members, std::make_index_sequence<std::tuple_size<Members>::value>());
    }
    public:
        DeSerializer(ParserInterface& parser)
            : parser(parser)
        {}

        template<typename T>
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
                scanObjectMembers(key, object);
            }

            if (tokenType == ParserToken::DocEnd)
            {   throw std::runtime_error("ThorsAnvil::Serialize::Serialize: Expected Doc End");
            }
        }

        template<typename T>
        void scanObjectMembers(std::string const& key, T const& object)
        {
            ApplyActionToParent<Traits<T>::type, T>     parentScanner;
            
            parentScanner.scanParentMember(*this, key, object);
            scanMembers(key, object, Traits<T>::getMembers());
        }
};

template<TraitType traitType, typename T>
class SerializerForBlock
{
    static_assert(traitType != TraitType::Invalid, "Invalid Serialize TraitType. This usually means you have not define ThorsAnvil::Serialize::Traits<Your Type>");
};

template<typename T>
class SerializerForBlock<TraitType::Value, T>
{
    public:
         SerializerForBlock(PrinterInterface&)  {}
        ~SerializerForBlock()                   {}
};

template<typename T>
class SerializerForBlock<TraitType::Map, T>
{
    PrinterInterface& printer;
    public:
        SerializerForBlock(PrinterInterface& printer): printer(printer)     {printer.openMap(); }
        ~SerializerForBlock()                                               {printer.closeMap();}
};

template<typename T>
class SerializerForBlock<TraitType::Array, T>
{
    PrinterInterface& printer;
    public:
        SerializerForBlock(PrinterInterface& printer): printer(printer)     {printer.openArray();}
        ~SerializerForBlock()                                               {printer.closeArray();}
};

template<typename T>
class SerializerForBlock<TraitType::Parent, T>: public SerializerForBlock<Traits<typename Traits<T>::Parent>::type, typename Traits<T>::Parent>
{
    public:
        using SerializerForBlock<Traits<typename Traits<T>::Parent>::type, typename Traits<T>::Parent>::SerializerForBlock;
};

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

class Serializer
{
    PrinterInterface& printer;

    template<typename T, typename Members, std::size_t... Seq>
    void printEachMember(T const& object, Members const& member, std::index_sequence<Seq...> const&)
    {
        std::make_tuple(SerializeMember(printer, object, std::get<Seq>(member))...);
    }
    template<typename T, typename Members>
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

        template<typename T>
        void print(T const& object)
        {
            SerializerForBlock<Traits<T>::type, T>     block(printer);
            printObjectMembers(object);
        }
        template<typename T>
        void printObjectMembers(T const& object)
        {
            ApplyActionToParent<Traits<T>::type, T>     parentPrinter;

            parentPrinter.printParentMembers(*this, object);
            printMembers(object, Traits<T>::getMembers());
        }
};

template<typename T>
inline void ApplyActionToParent<TraitType::Parent, T>::printParentMembers(Serializer& serializer, T const& object)
{
    serializer.printObjectMembers(static_cast<typename Traits<T>::Parent const&>(object));
}

template<typename T>
inline void ApplyActionToParent<TraitType::Parent, T>::scanParentMember(DeSerializer& deSerializer, std::string const& key, T const& object)
{
    deSerializer.scanObjectMembers(key, static_cast<typename Traits<T>::Parent const&>(object));
}

    }
}

#endif

