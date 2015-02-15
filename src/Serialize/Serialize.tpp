
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

/* ------------ ParserInterface ------------------------- */
inline ParserInterface::ParserToken ParserInterface::getToken()
{
    ParserToken result  = ParserToken::Error;

    if (pushBack != ParserToken::Error)
    {
        std::swap(pushBack, result);
    }
    else
    {
        result = this->getNextToken();
    }
    return result;
}
inline void ParserInterface::pushBackToken(ParserToken token)
{
    if (pushBack != ParserToken::Error)
    {
        throw std::runtime_error("Push only allows for single push back. More than one token has been pushed back between reads.");
    }
    pushBack    = token;
}
/* ------------ ApplyActionToParent ------------------------- */

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

/* ------------ DeSerializeMember ------------------------- */

template<typename T, typename M, TraitType type>
DeSerializeMember<T, M, type>::DeSerializeMember(ParserInterface& parser, std::string const& key, T& object, std::pair<char const*, M T::*> const& memberInfo)
{
    static_assert(type != TraitType::Invalid, "Trying to de-serialize an object that does not have a ThorsAnvil::Serialize::Trait<> defined."
                                              "Look at macro ThorsAnvil_MakeTrait() for more information.");

    if (key.compare(memberInfo.first) == 0)
    {
        DeSerializer    deSerializer(parser, false);
        deSerializer.parse(object.*(memberInfo.second));
    }
}

template<typename T, typename M>
class DeSerializeMember<T, M, TraitType::Value>
{
    public:
        DeSerializeMember(ParserInterface& parser, std::string const& key, T& object, std::pair<char const*, M T::*> const& memberInfo)
        {
            if (key.compare(memberInfo.first) == 0)
            {
                ParserInterface::ParserToken tokenType = parser.getToken();
                if (tokenType != ParserInterface::ParserToken::Value)
                {   throw std::runtime_error("ThorsAnvil::Serialize::Serialize: Expecting Value Token");
                }

                parser.getValue(object.*(memberInfo.second));
            }
        }
};

template<typename T, typename M>
DeSerializeMember<T, M> make_DeSerializeMember(ParserInterface& parser, std::string const& key, T& object, std::pair<char const*, M T::*> const& memberInfo)
{
    return DeSerializeMember<T, M>(parser, key, object, memberInfo);
}

/* ------------ DeSerializer ------------------------- */

inline DeSerializer::DeSerializer(ParserInterface& parser, bool root)
    : parser(parser)
    , root(root)
{}

template<typename T, typename Members, std::size_t... Seq>
inline void DeSerializer::scanEachMember(std::string const& key, T& object, Members const& member, std::index_sequence<Seq...> const&)
{
    std::make_tuple(make_DeSerializeMember(parser, key, object, std::get<Seq>(member))...);
}

template<typename T, typename... Members>
inline void DeSerializer::scanMembers(std::string const& key, T& object, std::tuple<Members...> const& members)
{
    scanEachMember(key, object, members, std::make_index_sequence<sizeof...(Members)>());
}

template<typename T, typename Action>
inline void DeSerializer::scanMembers(std::string const& key, T& object, Action action)
{
    action(parser, key, object);
}

template<typename T>
inline void DeSerializer::scanObjectMembers(std::string const& key, T& object)
{
    ApplyActionToParent<Traits<T>::type, T>     parentScanner;
    
    parentScanner.scanParentMember(*this, key, object);
    scanMembers(key, object, Traits<T>::getMembers());
}

template<typename T>
inline void DeSerializer::parse(T& object)
{
    ParserToken     tokenType;
    if (root)
    {
        // Note:
        //  Note: all "root" elements are going to have a DocStart/DocEnd pair
        //  Just the outer set. So that is something that we will need to deal with
        //
        //  Note: We also need to take care of arrays at the top level
        //  We will get that in the next version
        tokenType = parser.getToken();
        if (tokenType != ParserToken::DocStart)
        {   throw std::runtime_error("ThorsAnvil::Serialize::Serialize: Invalid Doc Start");
        }
    }

    tokenType = parser.getToken();
    if (tokenType == ParserToken::MapStart)
    {
        while((tokenType = parser.getToken()) != ParserToken::MapEnd)
        {
            if (tokenType != ParserToken::Key)
            {   throw std::runtime_error("ThorsAnvil::Serialize::Serialize: Expecting key token");
            }
            std::string key = parser.getKey();
            scanObjectMembers(key, object);
        }
    }
    else if (tokenType == ParserToken::ArrayStart)
    {
        while((tokenType = parser.getToken()) != ParserToken::ArrayEnd)
        {
            scanObjectMembers("", object);
        }
    }
    else
    {   throw std::runtime_error("ThorsAnvil::Serialize::Serialize: Invalid Object Start");
    }


    if (tokenType == ParserToken::DocEnd)
    {   throw std::runtime_error("ThorsAnvil::Serialize::Serialize: Expected Doc End");
    }
}

/* ------------ SerializerForBlock ------------------------- */

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

/* ------------ SerializeMember ------------------------- */

template<typename T, typename M, TraitType type>
SerializeMember<T, M, type>::SerializeMember(PrinterInterface& printer, T const& object, std::pair<char const*, M T::*> const& memberInfo)
{
    static_assert(type != TraitType::Invalid, "Trying to serialize an object that does not have a ThorsAnvil::Serialize::Trait<> defined."
                                              "Look at macro ThorsAnvil_MakeTrait() for more information.");

    printer.addKey(memberInfo.first);

    Serializer      serialzier(printer, false);
    serialzier.print(object.*(memberInfo.second));
}
template<typename T, typename M>
class SerializeMember<T, M, TraitType::Value>
{
    public:
        SerializeMember(PrinterInterface& printer, T const& object, std::pair<char const*, M T::*> const& memberInfo)
        {
            printer.addKey(memberInfo.first);
            printer.addValue(object.*(memberInfo.second));
        }
};

template<typename T, typename M>
SerializeMember<T, M> make_SerializeMember(PrinterInterface& printer, T const& object, std::pair<char const*, M T::*> const& memberInfo)
{
    return SerializeMember<T,M>(printer, object, memberInfo);
}

/* ------------ Serializer ------------------------- */

inline Serializer::Serializer(PrinterInterface& printer, bool root)
    : printer(printer)
    , root(root)
{
    if (root)
    {
        printer.openDoc();
    }
}
inline Serializer::~Serializer()
{
    if (root)
    {
        printer.closeDoc();
    }
}

template<typename T, typename Members, std::size_t... Seq>
inline void Serializer::printEachMember(T const& object, Members const& member, std::index_sequence<Seq...> const&)
{
    std::make_tuple(make_SerializeMember(printer, object, std::get<Seq>(member))...);
}

template<typename T, typename... Members>
inline void Serializer::printMembers(T const& object, std::tuple<Members...> const& members)
{
    printEachMember(object, members, std::make_index_sequence<sizeof...(Members)>());
}

template<typename T, typename Action>
inline void Serializer::printMembers(T const& object, Action action)
{
    action(printer, object);
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

