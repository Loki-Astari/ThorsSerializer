#ifndef THORS_ANVIL_SERIALIZE_THASH_H
#define THORS_ANVIL_SERIALIZE_THASH_H
/*
 * Generates a (relatively) unique hash for a type T.
 *
 * Uses a very simple but fast hashing algorithm. It is not designed to be anything
 * but fast. It is designed to guard against accidental changes not deliberate attacks.
 */

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
#include "BinaryTHash.tpp"
#endif

#endif
