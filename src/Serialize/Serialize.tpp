#ifndef THORS_ANVIL_SERIALIZE_SERIALIZE_TPP
#define THORS_ANVIL_SERIALIZE_SERIALIZE_TPP

//#include <iostream>
//#include <vector>
//#include <cstdlib>
//#include "Traits.h"
#include <algorithm>
#include <sstream>


namespace ThorsAnvil
{
    namespace Serialize
    {

/* ------------ ApplyActionToParent ------------------------- */

template<typename T, typename I>
class ApplyActionToParent<TraitType::Parent, T, I>
{
    public:
        void printParentMembers(Serializer& serializer, T const& object)
        {
            serializer.printObjectMembers(static_cast<typename Traits<T>::Parent const&>(object));
        }
        bool scanParentMember(DeSerializer& deSerializer, I const& key, T& object)
        {
            return deSerializer.scanObjectMembers(key, static_cast<typename Traits<T>::Parent&>(object));
        }
};
/* ------------ DeSerializationForBlock ------------------------- */

/*
 * The default Block is a mapping of "Map" to "Object"
 * We expect an OpenMap followed by a set of Key/Value pairs followed by CloseMap
 */
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
            while (hasMoreValue())
            {
                if (!parent.scanObjectMembers(key, object))
                {
                    parser.ignoreValue();
                }
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

/*
 * Specialization for Value.
 * This is only used at the top level.
 * There is no open or close. Just a single value is expected.
 */
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
            ParserInterface::ParserToken    tokenType = parser.getToken();
            if (tokenType != ParserInterface::ParserToken::Value)
            {   throw std::runtime_error("ThorsAnvil::Serialize::DeSerializationForBlock<Value>::DeSerializationForBlock: Invalid Object");
            }
            parser.getValue(object);
        }
};
template<typename T>
class DeSerializationForBlock<TraitType::Serialize, T>
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
            ParserInterface::ParserToken    tokenType = parser.getToken();
            if (tokenType != ParserInterface::ParserToken::Value)
            {   throw std::runtime_error("ThorsAnvil::Serialize::DeSerializationForBlock<Value>::DeSerializationForBlock: Invalid Object");
            }
            std::stringstream valueStream(parser.getRawValue());
            valueStream >> object;
        }
};
template<typename T>
class DeSerializationForBlock<TraitType::Pointer, T>
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
            ParserInterface::ParserToken    tokenType = parser.getToken();
            if (parser.isValueNull())
            {
                object = nullptr;
                return;
            }

            using BaseType = typename std::remove_pointer<T>::type;
            using TraitBase = Traits<BaseType>;
            using TraitPoint = Traits<T>;
            parser.pushBackToken(tokenType);
            object = TraitPoint::alloc();
            DeSerializationForBlock<TraitBase::type, BaseType>   pointerDeSerializer(parent, parser);
            pointerDeSerializer.scanObject(*object);
        }
};
/*
 * Specialization for Enum.
 * This is only used at the top level.
 * There is no open or close. Just a single value is expected.
 */
template<typename T>
class DeSerializationForBlock<TraitType::Enum, T>
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
            ParserInterface::ParserToken    tokenType = parser.getToken();
            if (tokenType != ParserInterface::ParserToken::Value)
            {   throw std::runtime_error("ThorsAnvil::Serialize::DeSerializationForBlock<Enum>::DeSerializationForBlock: Invalid Object");
            }
            std::string     objectValue;
            parser.getValue(objectValue);

            object = Traits<T>::getValue(objectValue, "ThorsAnvil::Serialize::DeSerializationForBlock<Enum>::DeSerializationForBlock:");
        }
};

/*
 * Specialization for Array.
 * It is like Map expect that there are no Keys.
 * This made it different enough that combining this into a single
 * function was messy.
 */
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
            while (hasMoreValue())
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

template<typename T, typename M>
DeSerializeMemberContainer<T, M>::DeSerializeMemberContainer(DeSerializer&, ParserInterface& parser, std::string const& key, T& object, std::pair<char const*, M T::*> const& memberInfo)
{
    if (key.compare(memberInfo.first) == 0)
    {
        used = true;
        DeSerializer    deSerializer(parser, false);
        deSerializer.parse(object.*(memberInfo.second));
    }
}

template<typename T, typename M, TraitType Type>
DeSerializeMemberValue<T, M, Type>::DeSerializeMemberValue(DeSerializer& parent, ParserInterface& parser, std::string const& key, T& object, std::pair<char const*, M T::*> const& memberInfo)
{
    init(parent, parser, key, memberInfo.first, object.*(memberInfo.second));
}

template<typename T, typename M, TraitType Type>
DeSerializeMemberValue<T, M, Type>::DeSerializeMemberValue(DeSerializer& parent, ParserInterface& parser, std::string const& key, T&, std::pair<char const*, M*> const& memberInfo)
{
    init(parent, parser, key, memberInfo.first, *(memberInfo.second));
}

template<typename T, typename M, TraitType Type>
void DeSerializeMemberValue<T, M, Type>::init(DeSerializer& parent, ParserInterface& parser, std::string const& key, char const* name, M& object)
{
    if (key.compare(name) == 0)
    {
        used = true;
        DeSerializationForBlock<Type, M>    deserializer(parent, parser);
        deserializer.scanObject(object);
    }
}

template<typename T, typename M, TraitType Type = Traits<M>::type>
class DeSerializeMember: public TraitsInfo<T, M, Type>::DeSerializeMember
{
    using Parent = typename TraitsInfo<T, M, Type>::DeSerializeMember;
    public:
        using Parent::Parent;
};

template<typename T, typename M>
DeSerializeMember<T, M> make_DeSerializeMember(DeSerializer& parent, ParserInterface& parser, std::string const& key, T& object, std::pair<char const*, M*> const& memberInfo)
{
    return DeSerializeMember<T, M>(parent, parser, key, object, memberInfo);
}

template<typename T, typename M>
DeSerializeMember<T, M> make_DeSerializeMember(DeSerializer& parent, ParserInterface& parser, std::string const& key, T& object, std::pair<char const*, M T::*> const& memberInfo)
{
    return DeSerializeMember<T, M>(parent, parser, key, object, memberInfo);
}

/* ------------ DeSerializer ------------------------- */
template<typename T, typename Members, std::size_t... Seq>
inline bool DeSerializer::scanEachMember(std::string const& key, T& object, Members const& member, std::index_sequence<Seq...> const&)
{
    auto memberCheck = {static_cast<bool>(make_DeSerializeMember(*this, parser, key, object, std::get<Seq>(member)))...};
    return std::find(std::begin(memberCheck), std::end(memberCheck), true) != std::end(memberCheck);
}

template<typename T, typename... Members>
inline bool DeSerializer::scanMembers(std::string const& key, T& object, std::tuple<Members...> const& members)
{
    return scanEachMember(key, object, members, std::make_index_sequence<sizeof...(Members)>());
}

template<typename T, typename I, typename Action>
inline bool DeSerializer::scanMembers(I const& key, T& object, Action action)
{
    action(parser, key, object);
    return true;
}

template<typename T, typename I>
inline bool DeSerializer::scanObjectMembers(I const& key, T& object)
{
    ApplyActionToParent<Traits<T>::type, T, I>     parentScanner;

    bool result =  parentScanner.scanParentMember(*this, key, object)
                || scanMembers(key, object, Traits<T>::getMembers());
    return result;
}

template<typename T>
inline void DeSerializer::parse(T& object)
{
    try
    {
        DeSerializationForBlock<Traits<T>::type, T>     block(*this, parser);
        block.scanObject(object);
    }
    catch (...)
    {
        root = false;
        throw;
    }
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
    Serializer&         parent;
    PrinterInterface&   printer;
    T const&            object;
    public:
        SerializerForBlock(Serializer& parent, PrinterInterface& printer,T const& object)
            : parent(parent)
            , printer(printer)
            , object(object)
        {}
        ~SerializerForBlock()   {}
        void printMembers()
        {
            printer.addValue(object);
        }
};
template<typename T>
class SerializerForBlock<TraitType::Serialize, T>
{
    Serializer&         parent;
    PrinterInterface&   printer;
    T const&            object;
    public:
        SerializerForBlock(Serializer& parent, PrinterInterface& printer,T const& object)
            : parent(parent)
            , printer(printer)
            , object(object)
        {}
        ~SerializerForBlock()   {}
        void printMembers()
        {
            std::stringstream buffer;
            buffer << object;
            printer.addRawValue(buffer.str());
        }
};
template<typename T>
class SerializerForBlock<TraitType::Pointer, T>
{
    Serializer&         parent;
    PrinterInterface&   printer;
    T const&            object;
    public:
        SerializerForBlock(Serializer& parent, PrinterInterface& printer,T const& object)
            : parent(parent)
            , printer(printer)
            , object(object)
        {}
        ~SerializerForBlock()   {}
        void printMembers()
        {
            if (object == nullptr)
            {
                printer.addNull();
            }
            else
            {
                using BaseType = typename std::remove_pointer<T>::type;
                SerializerForBlock<Traits<BaseType>::type, BaseType>  block(parent, printer, *object);
                block.printMembers();
            }
        }
};

template<typename T>
class SerializerForBlock<TraitType::Enum, T>
{
    Serializer&         parent;
    PrinterInterface&   printer;
    T const&            object;
    public:
        SerializerForBlock(Serializer& parent, PrinterInterface& printer,T const& object)
            : parent(parent)
            , printer(printer)
            , object(object)
        {}
        ~SerializerForBlock()   {}
        void printMembers()
        {
            printer.addValue(std::string(Traits<T>::getValues()[static_cast<int>(object)]));
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
            printer.openArray(SerializeArraySize<T>::size(object));
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

template<typename T, typename M>
SerializeMemberContainer<T, M>::SerializeMemberContainer(Serializer&, PrinterInterface& printer, T const& object, std::pair<char const*, M T::*> const& memberInfo)
{
    printer.addKey(memberInfo.first);

    Serializer      serialzier(printer, false);
    serialzier.print(object.*(memberInfo.second));
}

template<typename T, typename M, TraitType Type>
SerializeMemberValue<T, M, Type>::SerializeMemberValue(Serializer& parent, PrinterInterface& printer, T const& object, std::pair<char const*, M T::*> const& memberInfo)
{
    init(parent, printer, memberInfo.first, object.*(memberInfo.second));
}

template<typename T, typename M, TraitType Type>
SerializeMemberValue<T, M, Type>::SerializeMemberValue(Serializer& parent, PrinterInterface& printer, T const&, std::pair<char const*, M*> const& memberInfo)
{
    init(parent, printer, memberInfo.first, *(memberInfo.second));
}

template<typename T, typename M, TraitType Type>
void SerializeMemberValue<T, M, Type>::init(Serializer& parent, PrinterInterface& printer, char const* member, M const& object)
{
    printer.addKey(member);
    SerializerForBlock<Type, M>  serializer(parent, printer, object);
    serializer.printMembers();
}

template<typename T, typename M, TraitType Type = Traits<typename std::remove_cv<M>::type>::type>
class SerializeMember: public TraitsInfo<T, M, Type>::SerializeMember
{
    using Parent = typename TraitsInfo<T, M, Type>::SerializeMember;
    public:
        using Parent::Parent;
};

template<typename T, typename M>
SerializeMember<T, M> make_SerializeMember(Serializer& ser, PrinterInterface& printer, T const& object, std::pair<char const*, M*> const& memberInfo)
{
    return SerializeMember<T,M>(ser, printer, object, memberInfo);
}
template<typename T, typename M>
SerializeMember<T, M> make_SerializeMember(Serializer& ser, PrinterInterface& printer, T const& object, std::pair<char const*, M T::*> const& memberInfo)
{
    return SerializeMember<T,M>(ser, printer, object, memberInfo);
}

/* ------------ Serializer ------------------------- */

template<typename T, typename Members, std::size_t... Seq>
inline void Serializer::printEachMember(T const& object, Members const& member, std::index_sequence<Seq...> const&)
{
    auto discard = {(make_SerializeMember(*this, printer, object, std::get<Seq>(member)),1)...};
    (void)discard;
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
