
#include "gtest/gtest.h"
#include "THash.h"

namespace TS=ThorsAnvil::Serialize;

TEST(THashTest, hashint)
{
    std::cout << TS::thash<int>() << "\n";
}
