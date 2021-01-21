#include "gtest/gtest.h"
#include "Traits.h"

namespace Issue51
{

    template<typename T1, typename T2>
    struct Data
    {
        T1          data1;
        T2          data2;
    };
    // If you uncomment this it should fail to compile.
    // Because it is not in the global scope.
    // ThorsAnvil_Template_MakeTrait(2, Issue51::Data, data1, data2);
}

// The test is this line compiling correctly.
ThorsAnvil_Template_MakeTrait(2, Issue51::Data, data1, data2);

#include <iostream>

TEST(Issue51Test, JsonConnection)
{
}
