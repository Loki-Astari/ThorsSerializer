
#ifndef THORS_ANVIL_SERIALZIE_SER_MEMORY_H
#define THORS_ANVIL_SERIALZIE_SER_MEMORY_H

#include "Traits.h"

namespace ThorsAnvil
{
    namespace Serialize
    {

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


    }
}

#endif

