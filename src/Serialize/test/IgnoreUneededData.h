
#ifndef THORS_ANVIL_SERIALIZE_TEST_IGNORE_UNEEDED_DATA
#define THORS_ANVIL_SERIALIZE_TEST_IGNORE_UNEEDED_DATA

#include "../Serialize.h"

namespace TA=ThorsAnvil::Serialize;

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


ThorsAnvil_MakeTrait(ThingVersion, version);
ThorsAnvil_MakeTrait(Thing, name, version);

#endif

