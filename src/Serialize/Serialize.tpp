
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
        throw std::runtime_error("ThorsAnvil::Serialize::ParserInterface::pushBackToken: Push only allows for single push back. More than one token has been pushed back between reads.");
    }
    pushBack    = token;
}
/* ------------ ApplyActionToParent ------------------------- */

template<typename T, typename I>
class ApplyActionToParent<TraitType::Parent, T, I>
{
    public:
        void printParentMembers(Serializer& serializer, T const& object)
        {
            serializer.printObjectMembers(static_cast<typename Traits<T>::Parent const&>(object));
        }
        void scanParentMember(DeSerializer& deSerializer, I const& key, T& object)
        {
            deSerializer.scanObjectMembers(key, static_cast<typename Traits<T>::Parent&>(object));
        }
};
/* ------------ DeSerializationForBlock ------------------------- */

template<TraitType traitType, typename T>
class DeSerializationForBlock
{
    static_assert(
        traitType != TraitType::Invalid,
        "Invalid Serialize TraitType. This usually means you have not define ThorsAnvil::Serialize::Traits<Your Type>"
    );
    DeSerializer&    parent;
    ParserInterface& parser;
    std::string      key;
    public:
        DeSerializationForBlock(DeSerializer& parent, ParserInterface& parser)
            : parent(parent)
            , parser(parser)
        {
            ParserInterface::ParserToken    tokenType = parser.getToken();

            if (tokenType != ParserInterface::ParserToken::MapStart)
            {   throw std::runtime_error("ThorsAnvil::Serialize::DeSerializationForBlock<Map>::DeSerializationForBlock: Invalid Object Start");
            }
        }

        void scanObject(T& object)
        {
            while(hasMoreValue())
            {
                parent.scanObjectMembers(key, object);
            }
        }
        bool hasMoreValue()
        {
            ParserInterface::ParserToken    tokenType = parser.getToken();
            bool                            result    = tokenType != ParserInterface::ParserToken::MapEnd;
            if (result)
            {
                if (tokenType != ParserInterface::ParserToken::Key)
                {   throw std::runtime_error("ThorsAnvil::Serialize::DeSerializationForBlock<Map>::hasMoreValue: Expecting key token");
                }
                key = parser.getKey();
            }

            return result;
        }
};

template<typename T>
class DeSerializationForBlock<TraitType::Value, T>
{
    DeSerializer&       parent;
    ParserInterface&    parser;
    public:
        DeSerializationForBlock(DeSerializer& parent, ParserInterface& parser)
            : parent(parent)
            , parser(parser)
        {}
        void scanObject(T& object)
        {
            parser.getValue(object);
        }
};

template<typename T>
class DeSerializationForBlock<TraitType::Array, T>
{
    DeSerializer&    parent;
    ParserInterface& parser;
    std::size_t      index;
    public:
        DeSerializationForBlock(DeSerializer& parent, ParserInterface& parser)
            : parent(parent)
            , parser(parser)
            , index(-1)
        {
            ParserInterface::ParserToken    tokenType = parser.getToken();

            if (tokenType != ParserInterface::ParserToken::ArrayStart)
            {   throw std::runtime_error("ThorsAnvil::Serialize::DeSerializationForBlock<Array>::DeSerializationForBlock: Invalid Object Start");
            }
        }

        void scanObject(T& object)
        {
            while(hasMoreValue())
            {
                parent.scanObjectMembers(index, object);
            }
        }
        bool hasMoreValue()
        {
            ParserInterface::ParserToken    tokenType = parser.getToken();
            bool                            result    = tokenType != ParserInterface::ParserToken::ArrayEnd;
            if (result)
            {
                parser.pushBackToken(tokenType);
                ++index;
            }
            return result;
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
                {   throw std::runtime_error("ThorsAnvil::Serialize::DeSerializeMember::DeSerializeMember: Expecting Value Token");
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
{
    if (root)
    {
        // Note:
        //  Note: all "root" elements are going to have a DocStart/DocEnd pair
        //  Just the outer set. So that is something that we will need to deal with
        //
        //  Note: We also need to take care of arrays at the top level
        //  We will get that in the next version
        if (parser.getToken() != ParserToken::DocStart)
        {   throw std::runtime_error("ThorsAnvil::Serialize::DeSerializer::DeSerializer: Invalid Doc Start");
        }
    }
}
inline DeSerializer::~DeSerializer()
{
    if (root)
    {
        if (parser.getToken() != ParserToken::DocEnd)
        {   throw std::runtime_error("ThorsAnvil::Serialize::DeSerializer::~DeSerializer: Expected Doc End");
        }
    }
}

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

template<typename T, typename I, typename Action>
inline void DeSerializer::scanMembers(I const& key, T& object, Action action)
{
    action(parser, key, object);
}

template<typename T, typename I>
inline void DeSerializer::scanObjectMembers(I const& key, T& object)
{
    ApplyActionToParent<Traits<T>::type, T, I>     parentScanner;
    
    parentScanner.scanParentMember(*this, key, object);
    scanMembers(key, object, Traits<T>::getMembers());
}

template<typename T>
inline void DeSerializer::parse(T& object)
{
    DeSerializationForBlock<Traits<T>::type, T>     block(*this, parser);
    block.scanObject(object);
}

/* ------------ SerializerForBlock ------------------------- */

template<TraitType traitType, typename T>
class SerializerForBlock
{
    static_assert(
        traitType != TraitType::Invalid,
        "Invalid Serialize TraitType. This usually means you have not define ThorsAnvil::Serialize::Traits<Your Type>"
    );

    Serializer&         parent;
    PrinterInterface&   printer;
    T const&            object;
    public:
        SerializerForBlock(Serializer& parent, PrinterInterface& printer, T const& object)
            : parent(parent)
            , printer(printer)
            , object(object)
        {
            printer.openMap();
        }
        ~SerializerForBlock()
        {
            printer.closeMap();
        }
        void printMembers()
        {
            parent.printObjectMembers(object);
        }
};

template<typename T>
class SerializerForBlock<TraitType::Value, T>
{
    PrinterInterface&   printer;
    T const&            object;
    public:
        SerializerForBlock(Serializer&, PrinterInterface& printer,T const& object)
            : printer(printer)
            , object(object)
        {}
        ~SerializerForBlock()   {}
        void printMembers()
        {
            printer.addValue(object);
        }
};

template<typename T>
class SerializerForBlock<TraitType::Array, T>
{
    Serializer&         parent;
    PrinterInterface& printer;
    T const&            object;
    public:
        SerializerForBlock(Serializer& parent, PrinterInterface& printer, T const& object)
            : parent(parent)
            , printer(printer)
            , object(object)
        {
            printer.openArray(object.size());
        }
        ~SerializerForBlock()
        {
            printer.closeArray();
        }
        void printMembers()
        {
            parent.printObjectMembers(object);
        }
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
    SerializerForBlock<Traits<T>::type, T>     block(*this, printer, object);
    block.printMembers();
}

template<TraitType type>
struct IndexType;

template<>
struct IndexType<TraitType::Map>
{
    typedef std::string     IndexInfoType;
};
template<>
struct IndexType<TraitType::Array>
{
    typedef std::size_t     IndexInfoType;
};
template<>
struct IndexType<TraitType::Parent>
{
    typedef std::string     IndexInfoType;
};


template<typename T>
inline void Serializer::printObjectMembers(T const& object)
{
    typedef typename IndexType<Traits<T>::type>::IndexInfoType IndexInfoType;

    ApplyActionToParent<Traits<T>::type, T, IndexInfoType>     parentPrinter;

    parentPrinter.printParentMembers(*this, object);
    printMembers(object, Traits<T>::getMembers());
}

    }
}

#endif

