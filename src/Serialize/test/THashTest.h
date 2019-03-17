
#ifndef THORS_ANVIL_SERIALIZE_TEST_THASH_TEST_H
#define THORS_ANVIL_SERIALIZE_TEST_THASH_TEST_H

#include "../Traits.h"

namespace THashTest
{

struct T1
{
    int x;
    int y;
    int z;
};
struct T2
{
    int x;
    int y;
    int z;
};
struct D1
{
    int x;
    int y;
    double z;
};

}

ThorsAnvil_MakeTrait(THashTest::T1, x,y,z);
ThorsAnvil_MakeTrait(THashTest::T2, x,y,z);
ThorsAnvil_MakeTrait(THashTest::D1, x,y,z);


#endif

