
#ifndef THORS_ANVIL_SERIALZIE_SER_LIST_H
#define THORS_ANVIL_SERIALZIE_SER_LIST_H

#include "Traits.h"
#include "Serialize.h"
#include "SerUtil.h"
#include <list>

namespace ThorsAnvil
{
    namespace Serialize
    {

template<typename T>
class Traits<std::list<T>>
{
    public:
        static constexpr TraitType type = TraitType::Array;
        typedef ContainerMemberExtractor<std::list<T>>    MemberExtractor;
        static MemberExtractor const& getMembers()
        {
            static constexpr MemberExtractor    memberExtractor;
            return memberExtractor;
        }
};

    }
}

#endif



