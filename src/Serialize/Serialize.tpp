
#ifndef THORS_ANVIL_SERIALIZE_SERIALIZE_TPP
#define THORS_ANVIL_SERIALIZE_SERIALIZE_TPP

//#include <iostream>
//#include <vector>
//#include <cstdlib>
//#include "Traits.h"

namespace ThorsAnvil
{
    namespace Serialize
    {

template<typename T>
class ApplyActionToParent<TraitType::Parent, T>
{
    public:
        void printParentMembers(Serializer& serializer, T const& object)
        {
            serializer.printObjectMembers(static_cast<typename Traits<T>::Parent const&>(object));
        }
        void scanParentMember(DeSerializer& deSerializer, std::string const& key, T& object)
        {
            deSerializer.scanObjectMembers(key, static_cast<typename Traits<T>::Parent&>(object));
        }
};

template<typename T, typename Member>
DeSerializeMember::DeSerializeMember(ParserInterface& parser, std::string const& key, T& object, Member const& memberInfo)
{
    if (key.compare(memberInfo.first) == 0)
    {
        parser.getValue(object.*(memberInfo.second));
    }
}

template<typename T, typename Members, std::size_t... Seq>
inline void DeSerializer::scanEachMember(std::string const& key, T& object, Members const& member, std::index_sequence<Seq...> const&)
{
    std::make_tuple(DeSerializeMember(parser, key, object, std::get<Seq>(member))...);
}

template<typename T, typename Members>
inline void DeSerializer::scanMembers(std::string const& key, T& object, Members& members)
{
    scanEachMember(key, object, members, std::make_index_sequence<std::tuple_size<Members>::value>());
}

INLINE DeSerializer::DeSerializer(ParserInterface& parser)
    : parser(parser)
{}

template<typename T>
inline void DeSerializer::parse(T& object)
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
inline void DeSerializer::scanObjectMembers(std::string const& key, T& object)
{
    ApplyActionToParent<Traits<T>::type, T>     parentScanner;
    
    parentScanner.scanParentMember(*this, key, object);
    scanMembers(key, object, Traits<T>::getMembers());
}

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

template<typename T, typename M>
inline SerializeMember::SerializeMember(PrinterInterface& printer, T const& object, M const& memberInfo)
{
    printer.addKey(memberInfo.first);
    printer.addValue(object.*(memberInfo.second));
}

template<typename T, typename Members, std::size_t... Seq>
inline void Serializer::printEachMember(T const& object, Members const& member, std::index_sequence<Seq...> const&)
{
    std::make_tuple(SerializeMember(printer, object, std::get<Seq>(member))...);
}

template<typename T, typename Members>
inline void Serializer::printMembers(T const& object, Members const& members)
{
    printEachMember(object, members, std::make_index_sequence<std::tuple_size<Members>::value>());
}

INLINE Serializer::Serializer(PrinterInterface& printer)
    : printer(printer)
{
    printer.openDoc();
}
INLINE Serializer::~Serializer()
{
    printer.closeDoc();
}

template<typename T>
inline void Serializer::print(T const& object)
{
    SerializerForBlock<Traits<T>::type, T>     block(printer);
    printObjectMembers(object);
}

template<typename T>
inline void Serializer::printObjectMembers(T const& object)
{
    ApplyActionToParent<Traits<T>::type, T>     parentPrinter;

    parentPrinter.printParentMembers(*this, object);
    printMembers(object, Traits<T>::getMembers());
}

    }
}

#endif

