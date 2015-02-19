
#ifndef THORS_ANVIL_SERIALIZE_TEST_THASH_TEST_H
#define THORS_ANVIL_SERIALIZE_TEST_THASH_TEST_H

#include "../Traits.h"

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

ThorsAnvil_MakeTrait(T1, x,y,z);
ThorsAnvil_MakeTrait(T2, x,y,z);
ThorsAnvil_MakeTrait(D1, x,y,z);


#endif

