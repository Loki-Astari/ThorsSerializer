
#ifndef THORS_ANVIL_SERIALIZE_SER_UTIL_H
#define THORS_ANVIL_SERIALIZE_SER_UTIL_H

#include <map>
#include <vector>
#include <list>
#include <utility>

namespace ThorsAnvil
{
    namespace Serialize
    {

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
        void add(std::pair<K, V>&& value)
        {
            container.insert(std::forward<std::pair<K, V>>(value));
        }
};
template<typename T>
class MemberInserter<std::vector<T>>
{
    std::vector<T>& container;
    public:
        MemberInserter(std::vector<T>& container)
            : container(container)
        {}
        void add(T&& value)
        {
            container.push_back(std::forward<T>(value));
        }
};
template<typename T>
class MemberInserter<std::list<T>>
{
    std::list<T>& container;
    public:
        MemberInserter(std::list<T>& container)
            : container(container)
        {}
        void add(T&& value)
        {
            container.push_back(std::forward<T>(value));
        }
};
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
        void operator()(ParserInterface& parser, std::string const&, C& object) const
        {
            V                   data;
            GetValueType<V>     valueGetter(parser, data);

            MemberInserter<C>   inserter(object);
            inserter.add(std::move(data));
            //object.insert(std::move(data));
        }
};

    }
}

#endif
