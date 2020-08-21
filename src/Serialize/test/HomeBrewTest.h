#include "ThorSerialize/JsonThor.h"
#include "ThorSerialize/SerUtil.h"

struct HomeBrewBlock
{
    std::string             key;
    int                     code;
};

ThorsAnvil_MakeTrait(HomeBrewBlock, key, code);

