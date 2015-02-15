
#ifndef THORS_ANVIL_SERIALZIE_SER_MAP_H
#define THORS_ANVIL_SERIALZIE_SER_MAP_H

#include "Traits.h"
#include "SerMemory.h"
#include "Serialize.h"
#include <map>
#include <string>

namespace ThorsAnvil
{
    namespace Serialize
    {

template<typename Key, typename Value>
class Traits<std::map<Key, Value>>
{
    public:
        static constexpr TraitType type = TraitType::Array;

        class MemberExtractor
        {
            public:
                constexpr MemberExtractor() {}
                void operator()(PrinterInterface& printer, std::map<Key, Value> const& object) const
                {
                    Serializer  serializer(printer, false);
                    for(auto const& loop: object)
                    {
                        serializer.print(loop);
                    }
                }
                void operator()(ParserInterface& parser, std::string const&, std::map<Key, Value>& object) const
                {
                    DeSerializer            deSerializer(parser, false);

                    std::pair<Key, Value>   data;
                    deSerializer.parse(data);
                    object.insert(std::move(data));
                }
        };
        using Members = std::tuple<MemberExtractor>;

        static MemberExtractor const& getMembers()
        {
            static constexpr MemberExtractor    memberExtractor;
            return memberExtractor;
        }
};

template<typename Value>
class Traits<std::map<std::string, Value>>
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

    public:
        static constexpr TraitType type = TraitType::Map;

        class MemberExtractor
        {
            public:
                constexpr MemberExtractor(){}
                void operator()(PrinterInterface& printer, std::map<std::string, Value> const& object) const
                {
                    for(auto const& loop: object)
                    {
                        printer.addKey(loop.first);
                        printer.addValue(loop.second);
                    }
                }
                void operator()(ParserInterface& parser, std::string const& key, std::map<std::string, Value>& object) const
                {
                    Value                   data;
                    GetValueType<Value>     valueGetter(parser, data);
                    object.insert(std::make_pair(std::move(key), std::move(data)));
                }
        };
        using Members = std::tuple<MemberExtractor>;

        static MemberExtractor const& getMembers()
        {
            static constexpr MemberExtractor    memberExtractor;
            return memberExtractor;
        }
};


    }
}

#endif

