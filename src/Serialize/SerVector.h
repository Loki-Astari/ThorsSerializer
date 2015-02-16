
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
        typedef ContainerMemberExtractor<std::vector<T>>    MemberExtractor;
        static MemberExtractor const& getMembers()
        {
            static constexpr MemberExtractor    memberExtractor;
            return memberExtractor;
        }
};

    }
}

#endif


