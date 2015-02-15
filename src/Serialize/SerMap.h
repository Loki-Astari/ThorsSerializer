
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
                void operator()(PrinterInterface& printer, std::map<Key, Value> const& object)
                {
                    Serializer  serializer(printer, false);
                    for(auto const& loop: object)
                    {
                        serializer.print(loop);
                    }
                }
                void operator()(ParserInterface& parser, std::string const&, std::map<Key, Value>& object)
                {
                    DeSerializer            deSerializer(parser, false);

                    std::pair<Key, Value>   data;
                    deSerializer.parse(data);
                    object.insert(data);
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
    public:
        static constexpr TraitType type = TraitType::Map;

        class MemberExtractor
        {
            public:
                constexpr MemberExtractor(){}
                void operator()(PrinterInterface& printer, std::map<std::string, Value> const& object)
                {
                    for(auto const& loop: object)
                    {
                        printer.addKey(loop.first);
                        printer.addValue(loop.second);
                    }
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

