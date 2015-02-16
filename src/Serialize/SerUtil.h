
#ifndef THORS_ANVIL_SERIALIZE_SER_UTIL_H
#define THORS_ANVIL_SERIALIZE_SER_UTIL_H

#include "Traits.h"
#include "Serialize.h"
#include <utility>
#include <string>
#include <map>
#include <vector>
#include <deque>
#include <list>
#include <array>

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
 * Traits<std::map<K,V>>
 *      Traits<std::map<std::string,V>>

 */

namespace ThorsAnvil
{
    namespace Serialize
    {

/* ------------------------------- GetValueType ------------------------------- */
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
template<typename T>
class MemberInserter;

template<typename K,typename V>
class MemberInserter<std::map<K,V>>
{
    std::map<K, V>& container;
    public:
        MemberInserter(std::map<K, V>& container)
            : container(container)
        {}
        void add(std::size_t const&, std::pair<K, V>&& value)
        {
            container.insert(std::forward<std::pair<K, V>>(value));
        }
};

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

/* ------------------------------- ContainerMemberExtractor ------------------------------- */
template<typename C, typename V = typename C::value_type>
class ContainerMemberExtractor
{
    public:
        constexpr ContainerMemberExtractor() {}
        void operator()(PrinterInterface& printer, C const& object) const
        {
            PutValueType<V>     valuePutter(printer);
            for(auto const& loop: object)
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
            //object.insert(std::move(data));
        }
};

/* ------------------------------- Traits<std::array<T, N>> ------------------------------- */
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

/* ------------------------------- Traits<std::pair<F, S>> ------------------------------- */
template<typename F, typename S>
class Traits<std::pair<F, S>>
{
    public:
        static constexpr TraitType type = TraitType::Map;
        typedef std::pair<F,S>  Self;

        using Members = std::tuple<
                        REP_N(TypeAction, Self, first, second)
                                    >;

        static Members const& getMembers()
        {
            static constexpr Members members{
                        REP_N(ValueAction, Self, first, second)
                                            };
            return members;
        }
};

/* ------------------------------- Traits<std::map<Key, Value>> ------------------------------- */
template<typename Key, typename Value>
class Traits<std::map<Key, Value>>
{
    public:
        static constexpr TraitType type = TraitType::Array;
        typedef ContainerMemberExtractor<std::map<Key, Value>, std::pair<Key,Value>>    MemberExtractor;
        static MemberExtractor const& getMembers()
        {
            static constexpr MemberExtractor    memberExtractor;
            return memberExtractor;
        }
};

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
                    for(auto const& loop: object)
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


    }
}

#endif

