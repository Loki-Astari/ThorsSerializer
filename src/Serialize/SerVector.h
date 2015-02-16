
#ifndef THORS_ANVIL_SERIALZIE_SER_VECTOR_H
#define THORS_ANVIL_SERIALZIE_SER_VECTOR_H

#include "Traits.h"
#include "Serialize.h"
#include "SerUtil.h"
#include <vector>

namespace ThorsAnvil
{
    namespace Serialize
    {

template<typename T>
class Traits<std::vector<T>>
{
    public:
        static constexpr TraitType type = TraitType::Array;

        class MemberExtractor
        {
            public:
                constexpr MemberExtractor() {}
                void operator()(PrinterInterface& printer, std::vector<T> const& object) const
                {
                    PutValueType<T>    putter(printer);
                    for(auto const& loop: object)
                    {
                        putter.putValue(loop);
                    }
                }
                void operator()(ParserInterface& parser, std::string const&, std::vector<T>& object) const
                {
                    T                       value;
                    GetValueType<T>         valueGetter(parser, value);
                    object.push_back(std::move(value));
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


