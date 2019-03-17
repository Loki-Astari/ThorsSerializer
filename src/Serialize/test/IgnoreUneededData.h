
#ifndef THORS_ANVIL_SERIALIZE_TEST_IGNORE_UNEEDED_DATA
#define THORS_ANVIL_SERIALIZE_TEST_IGNORE_UNEEDED_DATA

#include "../Serialize.h"

namespace TA=ThorsAnvil::Serialize;

namespace IgnoreUneededData
{

class Thing
{
public:
    Thing(): version(3) {}
    long version;
    std::string name;
};

class ThingVersion
{
public:
    ThingVersion(): version(0) {}
    long version;
};

}


ThorsAnvil_MakeTrait(IgnoreUneededData::ThingVersion, version);
ThorsAnvil_MakeTrait(IgnoreUneededData::Thing, name, version);

#endif

