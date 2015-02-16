
#ifndef THORS_ANVIL_SERIALZIE_SER_MAP_H
#define THORS_ANVIL_SERIALZIE_SER_MAP_H

#include "Traits.h"
#include "Serialize.h"
#include "SerMemory.h"
#include "SerUtil.h"
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

