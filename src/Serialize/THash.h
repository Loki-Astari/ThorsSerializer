
#ifndef THORS_ANVIL_SERIALIZE_THASH_H
#define THORS_ANVIL_SERIALIZE_THASH_H

#include <cstdlib>

namespace ThorsAnvil
{
    namespace Serialize
    {

template<typename T>
std::size_t thash(std::size_t restul = 0);

    }
}

#ifndef COVERAGE_TEST
#include "THash.tpp"
#endif

#endif


