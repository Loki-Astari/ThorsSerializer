#ifndef THORS_ANVIL_SERIALIZE_SER_UTIL_H
#define THORS_ANVIL_SERIALIZE_SER_UTIL_H

#include "Traits.h"
#include "Serialize.h"
#include "BinaryTHash.h"
#include <utility>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <vector>
#include <deque>
#include <list>
#include <array>
#include <tuple>
#include <initializer_list>

/*
 * GetValueType
 * PutValueType
 * MemberInserter
 * ContainerMemberExtractor
 *
 * Traits<std::array<T,N>>
 * Traits<std::list<T>>
 * Traits<std::vector<T, Allocator>>
 * Traits<std::deque<T, Allocator>>
 * Traits<std::pair<A,B>>
 * Traits<std::set<K>>
 * Traits<std::multiset<K>>
 * Traits<std::map<K,V>>
 *      Traits<std::map<std::string,V>>
 * Traits<std::multimap<K,V>>
 *      Traits<std::multimap<std::string,V>>
 *
 * C++ 14 Containers
 * Traits<std::tuple<Args...>>
 * Traits<std::unordered_set<K,V>>
 * Traits<std::unordered_multiset<K>>
 * Traits<std::unordered_map<K,V>>
 *      Traits<std::unordered_map<std::string,V>>
 * Traits<std::unordered_multimap<K,V>>
 *      Traits<std::unordered_multimap<std::string,V>>
 * Traits<std::initializer_list<T>>
 *
 */

namespace ThorsAnvil
{
    namespace Serialize
    {

/* ------------------------------- GetValueType ------------------------------- */
/*
 * Used to retrieve a value from a stream.
 * A normal value is retrieved directly from the stream (via the parser object).
 * A compound type Map/Array is retrieved from the stream using a DeSerializer.
 */
template<typename V, TraitType type = Traits<V>::type>
class GetValueType
{
    public:
        GetValueType(ParserInterface& parser, V& value)
        {
            DeSerializer            deSerializer(parser, false);
            deSerializer.parse(value);
        }
};

template<typename V>
class GetValueType<V, TraitType::Value>
{
    public:
        GetValueType(ParserInterface& parser, V& value)
        {
            if (parser.getToken() != ThorsAnvil::Serialize::ParserInterface::ParserToken::Value)
            {   throw std::runtime_error("ThorsAnvil::Serializer::SerMap::GetValueType::GetValueType<Value>: Expecting a normal value after the key");
            }
            parser.getValue(value);
        }
};

/* ------------------------------- PutValueType ------------------------------- */
/*
 * Used to put a values onto a stream.
 * A normal value is put directly onto the stream (via the printer object).
 * A compound type Map/Array is printed to the stream using a Serializer.
 */
template<typename V, TraitType type = Traits<V>::type>
class PutValueType
{
    Serializer      serializer;
    public:
        PutValueType(PrinterInterface& printer)
            : serializer(printer, false)
        {}
        void putValue(V const& value)
        {
            serializer.print(value);
        }
};

template<typename V>
class PutValueType<V, TraitType::Value>
{
    PrinterInterface&   printer;
    public:
        PutValueType(PrinterInterface& printer)
            : printer(printer)
        {}

        void putValue(V const& value)
        {
            printer.addValue(value);
        }
};

/* ------------------------------- MemberInserter ------------------------------- */
/*
 * Defines how a value is inserted into a container.
 * Overloaded for each container type (no generic definition)
 */
template<typename T>
class MemberInserter;

/* ------------------------------- ContainerMemberExtractor ------------------------------- */
/*
 * A generic contain manipulator class
 *
 * The operator()(printer) prints all the values in the container using PutValueType class.
 * The PutValueType will call the printer directly for value types but recursively use
 * the Serializer class for Map/Array types.
 *
 * The operator()(parser) reads a single value from the parser and puts it in the container
 * using the GetValueType class. The GetValueType will call the parser directly for value types
 * but recursively use the DeSerializer class for Map/Array types.
 *
 * Note each container has differences in the insert technique thus we use a MemberInserter
 * object to do the inserting of values after they have been read. The class attempts to do this
 * using move semantics.
 */
template<typename C, typename V = typename C::value_type>
class ContainerMemberExtractor
{
    public:
        constexpr ContainerMemberExtractor() {}
        constexpr std::size_t getHash(std::size_t start) const
        {
            return thash<C>(start);
        }
        void operator()(PrinterInterface& printer, C const& object) const
        {
            PutValueType<V>     valuePutter(printer);
            for (auto const& loop: object)
            {
                valuePutter.putValue(loop);
            }
        }
        void operator()(ParserInterface& parser, std::size_t const& index, C& object) const
        {
            V                   data;
            GetValueType<V>     valueGetter(parser, data);

            MemberInserter<C>   inserter(object);
            inserter.add(index, std::move(data));
        }
};

/* ------------------------------- Traits<std::pair<F, S>> ------------------------------- */
template<typename F, typename S>
class Traits<std::pair<F, S>>
{
    public:
        static constexpr TraitType type = TraitType::Map;
        typedef std::pair<F,S>  Self;

        using Members = std::tuple< REP_N(THOR_TYPEACTION, 0, Self, first, second, 1) >;

        static Members const& getMembers()
        {
            static constexpr Members members{ REP_N(THOR_VALUEACTION, 0, Self, first, second, 1) };
            return members;
        }
};

/* ------------------------------- Traits<std::initializer_list<T>> ------------------------------- */
template<typename T>
class MemberInserter<std::initializer_list<T>>
{
    std::initializer_list<T>& container;
    public:
        MemberInserter(std::initializer_list<T>& container)
            : container(container)
        {}
        void add(std::size_t const& , T&& )
        {
            //static_assert(false, "Can not de-serialize and initializer list");
        }
};

template<typename T>
class Traits<std::initializer_list<T>>
{
    public:
        static constexpr TraitType type = TraitType::Array;
        typedef ContainerMemberExtractor<std::initializer_list<T>>    MemberExtractor;
        static MemberExtractor const& getMembers()
        {
            static constexpr MemberExtractor    memberExtractor;
            return memberExtractor;
        }
};

/* ------------------------------- Traits<std::array<T, N>> ------------------------------- */
template<typename T, std::size_t N>
class MemberInserter<std::array<T, N>>
{
    std::array<T, N>& container;
    public:
        MemberInserter(std::array<T, N>& container)
            : container(container)
        {}
        void add(std::size_t const& index, T&& value)
        {
            container[index] = std::forward<T>(value);
        }
};

template<typename T, std::size_t N>
class Traits<std::array<T, N>>
{
    public:
        static constexpr TraitType type = TraitType::Array;
        typedef ContainerMemberExtractor<std::array<T, N>>    MemberExtractor;
        static MemberExtractor const& getMembers()
        {
            static constexpr MemberExtractor    memberExtractor;
            return memberExtractor;
        }
};

/* ------------------------------- Traits<std::list<T>> ------------------------------- */
template<typename T, typename Allocator>
class MemberInserter<std::list<T, Allocator>>
{
    std::list<T, Allocator>& container;
    public:
        MemberInserter(std::list<T, Allocator>& container)
            : container(container)
        {}
        void add(std::size_t const&, T&& value)
        {
            container.push_back(std::forward<T>(value));
        }
};

template<typename T, typename Allocator>
class Traits<std::list<T, Allocator>>
{
    public:
        static constexpr TraitType type = TraitType::Array;
        typedef ContainerMemberExtractor<std::list<T, Allocator>>    MemberExtractor;
        static MemberExtractor const& getMembers()
        {
            static constexpr MemberExtractor    memberExtractor;
            return memberExtractor;
        }
};

/* ------------------------------- Traits<std::vector<T>> ------------------------------- */
template<typename T, typename Allocator>
class MemberInserter<std::vector<T, Allocator>>
{
    std::vector<T, Allocator>& container;
    public:
        MemberInserter(std::vector<T, Allocator>& container)
            : container(container)
        {}
        void add(std::size_t const&, T&& value)
        {
            container.push_back(std::forward<T>(value));
        }
};

template<typename T, typename Allocator>
class Traits<std::vector<T, Allocator>>
{
    public:
        static constexpr TraitType type = TraitType::Array;
        typedef ContainerMemberExtractor<std::vector<T, Allocator>>    MemberExtractor;
        static MemberExtractor const& getMembers()
        {
            static constexpr MemberExtractor    memberExtractor;
            return memberExtractor;
        }
};

/* ------------------------------- Traits<std::deque<T>> ------------------------------- */
template<typename T, typename Allocator>
class MemberInserter<std::deque<T, Allocator>>
{
    std::deque<T, Allocator>& container;
    public:
        MemberInserter(std::deque<T, Allocator>& container)
            : container(container)
        {}
        void add(std::size_t const&, T&& value)
        {
            container.push_back(std::forward<T>(value));
        }
};

template<typename T, typename Allocator>
class Traits<std::deque<T, Allocator>>
{
    public:
        static constexpr TraitType type = TraitType::Array;
        typedef ContainerMemberExtractor<std::deque<T, Allocator>>    MemberExtractor;
        static MemberExtractor const& getMembers()
        {
            static constexpr MemberExtractor    memberExtractor;
            return memberExtractor;
        }
};

/* ------------------------------- Traits<std::set<Key>> ------------------------------- */
template<typename Key, typename Compare, typename Allocator>
class MemberInserter<std::set<Key, Compare, Allocator>>
{
    std::set<Key, Compare, Allocator>& container;
    public:
        MemberInserter(std::set<Key, Compare, Allocator>& container)
            : container(container)
        {}
        void add(std::size_t const&, Key&& value)
        {
            container.insert(std::forward<Key>(value));
        }
};

template<typename Key, typename Compare, typename Allocator>
class Traits<std::set<Key, Compare, Allocator>>
{
    public:
        static constexpr TraitType type = TraitType::Array;
        typedef ContainerMemberExtractor<std::set<Key, Compare, Allocator>>    MemberExtractor;
        static MemberExtractor const& getMembers()
        {
            static constexpr MemberExtractor    memberExtractor;
            return memberExtractor;
        }
};

/* ------------------------------- Traits<std::unordered_set<Key>> ------------------------------- */
template<typename Key, typename Hash, typename KeyEqual, typename Allocator>
class MemberInserter<std::unordered_set<Key, Hash, KeyEqual, Allocator>>
{
    std::unordered_set<Key, Hash, KeyEqual, Allocator>& container;
    public:
        MemberInserter(std::unordered_set<Key, Hash, KeyEqual, Allocator>& container)
            : container(container)
        {}
        void add(std::size_t const&, Key&& value)
        {
            container.insert(std::forward<Key>(value));
        }
};

template<typename Key, typename Hash, typename KeyEqual, typename Allocator>
class Traits<std::unordered_set<Key, Hash, KeyEqual, Allocator>>
{
    public:
        static constexpr TraitType type = TraitType::Array;
        typedef ContainerMemberExtractor<std::unordered_set<Key, Hash, KeyEqual, Allocator>>    MemberExtractor;
        static MemberExtractor const& getMembers()
        {
            static constexpr MemberExtractor    memberExtractor;
            return memberExtractor;
        }
};

/* ------------------------------- Traits<std::multiset<Key>> ------------------------------- */
template<typename Key, typename Compare, typename Allocator>
class MemberInserter<std::multiset<Key, Compare, Allocator>>
{
    std::multiset<Key, Compare, Allocator>& container;
    public:
        MemberInserter(std::multiset<Key, Compare, Allocator>& container)
            : container(container)
        {}
        void add(std::size_t const&, Key&& value)
        {
            container.insert(std::forward<Key>(value));
        }
};

template<typename Key, typename Compare, typename Allocator>
class Traits<std::multiset<Key, Compare, Allocator>>
{
    public:
        static constexpr TraitType type = TraitType::Array;
        typedef ContainerMemberExtractor<std::multiset<Key, Compare, Allocator>>    MemberExtractor;
        static MemberExtractor const& getMembers()
        {
            static constexpr MemberExtractor    memberExtractor;
            return memberExtractor;
        }
};

/* ------------------------------- Traits<std::unordered_multiset<Key>> ------------------------------- */
template<typename Key, typename Hash, typename KeyEqual, typename Allocator>
class MemberInserter<std::unordered_multiset<Key, Hash, KeyEqual, Allocator>>
{
    std::unordered_multiset<Key, Hash, KeyEqual, Allocator>& container;
    public:
        MemberInserter(std::unordered_multiset<Key, Hash, KeyEqual, Allocator>& container)
            : container(container)
        {}
        void add(std::size_t const&, Key&& value)
        {
            container.insert(std::forward<Key>(value));
        }
};

template<typename Key, typename Hash, typename KeyEqual, typename Allocator>
class Traits<std::unordered_multiset<Key, Hash, KeyEqual, Allocator>>
{
    public:
        static constexpr TraitType type = TraitType::Array;
        typedef ContainerMemberExtractor<std::unordered_multiset<Key, Hash, KeyEqual, Allocator>>    MemberExtractor;
        static MemberExtractor const& getMembers()
        {
            static constexpr MemberExtractor    memberExtractor;
            return memberExtractor;
        }
};

/* ------------------------------- Traits<std::map<Key, Value>> ------------------------------- */
template<typename Key,typename T, typename Compare, typename Allocator>
class MemberInserter<std::map<Key, T, Compare, Allocator>>
{
    std::map<Key, T, Compare, Allocator>& container;
    public:
        MemberInserter(std::map<Key, T, Compare, Allocator>& container)
            : container(container)
        {}
        void add(std::size_t const&, std::pair<Key, T>&& value)
        {
            container.insert(std::forward<std::pair<Key, T>>(value));
        }
};

template<typename Key, typename T, typename Compare, typename Allocator>
class Traits<std::map<Key, T, Compare, Allocator>>
{
    public:
        static constexpr TraitType type = TraitType::Array;
        typedef ContainerMemberExtractor<std::map<Key, T, Compare, Allocator>, std::pair<Key, T>>    MemberExtractor;
        static MemberExtractor const& getMembers()
        {
            static constexpr MemberExtractor    memberExtractor;
            return memberExtractor;
        }
};

/*
 * std::map<> we use a specialization when the key is a std::string.
 * This allows maps that have string keys to be represented directly by Json Map objects.
 */
template<typename Value>
class Traits<std::map<std::string, Value>>
{
    public:
        static constexpr TraitType type = TraitType::Map;

        class MemberExtractor
        {
            public:
                constexpr MemberExtractor(){}
                void operator()(PrinterInterface& printer, std::map<std::string, Value> const& object) const
                {
                    PutValueType<Value>     valuePutter(printer);
                    for (auto const& loop: object)
                    {
                        printer.addKey(loop.first);
                        valuePutter.putValue(loop.second);
                    }
                }
                void operator()(ParserInterface& parser, std::string const& key, std::map<std::string, Value>& object) const
                {
                    Value                   data;
                    GetValueType<Value>     valueGetter(parser, data);
                    object.insert(std::make_pair(std::move(key), std::move(data)));
                }
        };

        static MemberExtractor const& getMembers()
        {
            static constexpr MemberExtractor    memberExtractor;
            return memberExtractor;
        }
};

/* ------------------------------- Traits<std::unordered_map<Key, Value>> ------------------------------- */
template<typename Key,typename T, typename Hash, typename KeyEqual, typename Allocator>
class MemberInserter<std::unordered_map<Key, T, Hash, KeyEqual, Allocator>>
{
    std::unordered_map<Key, T, Hash, KeyEqual, Allocator>& container;
    public:
        MemberInserter(std::unordered_map<Key, T, Hash, KeyEqual, Allocator>& container)
            : container(container)
        {}
        void add(std::size_t const&, std::pair<Key, T>&& value)
        {
            container.insert(std::forward<std::pair<Key, T>>(value));
        }
};

template<typename Key, typename T, typename Hash, typename KeyEqual, typename Allocator>
class Traits<std::unordered_map<Key, T, Hash, KeyEqual, Allocator>>
{
    public:
        static constexpr TraitType type = TraitType::Array;
        typedef ContainerMemberExtractor<std::unordered_map<Key, T, Hash, KeyEqual, Allocator>, std::pair<Key, T>>    MemberExtractor;
        static MemberExtractor const& getMembers()
        {
            static constexpr MemberExtractor    memberExtractor;
            return memberExtractor;
        }
};

/*
 * std::unordered_map<> we use a specialization when the key is a std::string.
 * This allows unordered_maps that have string keys to be represented directly by Json Map objects.
 */
template<typename Value>
class Traits<std::unordered_map<std::string, Value>>
{
    public:
        static constexpr TraitType type = TraitType::Map;

        class MemberExtractor
        {
            public:
                constexpr MemberExtractor(){}
                void operator()(PrinterInterface& printer, std::unordered_map<std::string, Value> const& object) const
                {
                    PutValueType<Value>     valuePutter(printer);
                    for (auto const& loop: object)
                    {
                        printer.addKey(loop.first);
                        valuePutter.putValue(loop.second);
                    }
                }
                void operator()(ParserInterface& parser, std::string const& key, std::unordered_map<std::string, Value>& object) const
                {
                    Value                   data;
                    GetValueType<Value>     valueGetter(parser, data);
                    object.insert(std::make_pair(std::move(key), std::move(data)));
                }
        };

        static MemberExtractor const& getMembers()
        {
            static constexpr MemberExtractor    memberExtractor;
            return memberExtractor;
        }
};

/* ------------------------------- Traits<std::unordered_multimap<Key, Value>> ------------------------------- */
template<typename Key,typename T, typename Hash, typename KeyEqual, typename Allocator>
class MemberInserter<std::unordered_multimap<Key, T, Hash, KeyEqual, Allocator>>
{
    std::unordered_multimap<Key, T, Hash, KeyEqual, Allocator>& container;
    public:
        MemberInserter(std::unordered_multimap<Key, T, Hash, KeyEqual, Allocator>& container)
            : container(container)
        {}
        void add(std::size_t const&, std::pair<Key, T>&& value)
        {
            container.insert(std::forward<std::pair<Key, T>>(value));
        }
};

template<typename Key, typename T, typename Hash, typename KeyEqual, typename Allocator>
class Traits<std::unordered_multimap<Key, T, Hash, KeyEqual, Allocator>>
{
    public:
        static constexpr TraitType type = TraitType::Array;
        typedef ContainerMemberExtractor<std::unordered_multimap<Key, T, Hash, KeyEqual, Allocator>, std::pair<Key, T>>    MemberExtractor;
        static MemberExtractor const& getMembers()
        {
            static constexpr MemberExtractor    memberExtractor;
            return memberExtractor;
        }
};

template<typename Value>
class Traits<std::unordered_multimap<std::string, Value>>
{
    public:
        static constexpr TraitType type = TraitType::Map;

        class MemberExtractor
        {
            public:
                constexpr MemberExtractor(){}
                void operator()(PrinterInterface& printer, std::unordered_multimap<std::string, Value> const& object) const
                {
                    PutValueType<Value>     valuePutter(printer);
                    for (auto const& loop: object)
                    {
                        printer.addKey(loop.first);
                        valuePutter.putValue(loop.second);
                    }
                }
                void operator()(ParserInterface& parser, std::string const& key, std::unordered_multimap<std::string, Value>& object) const
                {
                    Value                   data;
                    GetValueType<Value>     valueGetter(parser, data);
                    object.insert(std::make_pair(std::move(key), std::move(data)));
                }
        };

        static MemberExtractor const& getMembers()
        {
            static constexpr MemberExtractor    memberExtractor;
            return memberExtractor;
        }
};

/* ------------------------------- Traits<std::multimap<Key, Value>> ------------------------------- */
template<typename Key,typename T, typename Compare, typename Allocator>
class MemberInserter<std::multimap<Key, T, Compare, Allocator>>
{
    std::multimap<Key, T, Compare, Allocator>& container;
    public:
        MemberInserter(std::multimap<Key, T, Compare, Allocator>& container)
            : container(container)
        {}
        void add(std::size_t const&, std::pair<Key, T>&& value)
        {
            container.insert(std::forward<std::pair<Key, T>>(value));
        }
};

template<typename Key, typename T, typename Compare, typename Allocator>
class Traits<std::multimap<Key, T, Compare, Allocator>>
{
    public:
        static constexpr TraitType type = TraitType::Array;
        typedef ContainerMemberExtractor<std::multimap<Key, T, Compare, Allocator>, std::pair<Key, T>>    MemberExtractor;
        static MemberExtractor const& getMembers()
        {
            static constexpr MemberExtractor    memberExtractor;
            return memberExtractor;
        }
};

template<typename Value>
class Traits<std::multimap<std::string, Value>>
{
    public:
        static constexpr TraitType type = TraitType::Map;

        class MemberExtractor
        {
            public:
                constexpr MemberExtractor(){}
                void operator()(PrinterInterface& printer, std::multimap<std::string, Value> const& object) const
                {
                    PutValueType<Value>     valuePutter(printer);
                    for (auto const& loop: object)
                    {
                        printer.addKey(loop.first);
                        valuePutter.putValue(loop.second);
                    }
                }
                void operator()(ParserInterface& parser, std::string const& key, std::multimap<std::string, Value>& object) const
                {
                    Value                   data;
                    GetValueType<Value>     valueGetter(parser, data);
                    object.insert(std::make_pair(std::move(key), std::move(data)));
                }
        };

        static MemberExtractor const& getMembers()
        {
            static constexpr MemberExtractor    memberExtractor;
            return memberExtractor;
        }
};

/* ------------------------------- Traits<std::tupple<Type...>> ------------------------------- */

/* Since we treat a tupple like an array.
 * We need some way to get the size of the expected array.
 */
template<typename... Args>
class SerializeArraySize<std::tuple<Args...>>
{
    public:
        static std::size_t size(std::tuple<Args...> const&)
        {
            return sizeof...(Args);
        }
};

/*
 * This is the object that parses/prints data from/to the stream
 */
template<typename... Args>
class ContainerTuppleExtractor
{
        using C = std::tuple<Args...>;

        template<std::size_t index, typename V>
        void printTupleValue(PrinterInterface& printer, C const& object) const
        {
            PutValueType<V>     valuePutter(printer);
            valuePutter.putValue(std::get<index>(object));
        }
        template<std::size_t... index>
        void printTupleValues(PrinterInterface& printer, C const& object, std::index_sequence<index...> const&) const
        {
            auto discard = {(printTupleValue<index, typename std::tuple_element_t<index, C>>(printer, object),1)...};
            (void)discard;
        }
        template<std::size_t index, typename V>
        void parseTupleValue(ParserInterface& parser, C& object) const
        {
            V&                  data(std::get<index>(object));
            GetValueType<V>     valueGetter(parser, data);
        }
        template<std::size_t... index>
        void parseTupleValues(ParserInterface& parser, std::size_t const& id, C& object,  std::index_sequence<index...> const&) const
        {
            using MemberDecoder = decltype(&ContainerTuppleExtractor::parseTupleValue<0, typename std::tuple_element_t<0, C>>);
            static std::initializer_list<MemberDecoder> parseTuppleValue = {&ContainerTuppleExtractor::parseTupleValue<index, typename std::tuple_element_t<index, C>>...};
            auto iteratorToFunction = parseTuppleValue.begin() + id;
            auto function = *iteratorToFunction;
            (this->*function)(parser, object);
        }
    public:
        constexpr ContainerTuppleExtractor() {}
        constexpr std::size_t getHash(std::size_t start) const
        {
            return thash<int>(start);
        }
        void operator()(PrinterInterface& printer, C const& object) const
        {
            printTupleValues(printer, object, std::make_index_sequence<sizeof...(Args)>());
        }
        void operator()(ParserInterface& parser, std::size_t const& index, C& object) const
        {
            parseTupleValues(parser, index, object, std::make_index_sequence<sizeof...(Args)>());
        }
};

/*
 * A traits class for tupple that uses the above ContainerTuppleExtractor
 */
template<typename... Args>
class Traits<std::tuple<Args...>>
{
    public:
        static constexpr TraitType type = TraitType::Array;
        
        static ContainerTuppleExtractor<Args...> const& getMembers()
        {
            static constexpr ContainerTuppleExtractor<Args...> members;
            return members;
        }
};


    }
}

#endif
