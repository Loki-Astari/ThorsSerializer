
#ifndef THORSANVIL_SERIALIZE_TEST_IGNORE_UNEEDED_DATA
#define THORSANVIL_SERIALIZE_TEST_IGNORE_UNEEDED_DATA

#include "../SerUtil.h"

namespace TA=ThorsAnvil::Serialize;

namespace IgnoreUneededDataTest
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


ThorsAnvil_MakeTrait(IgnoreUneededDataTest::ThingVersion, version);
ThorsAnvil_MakeTrait(IgnoreUneededDataTest::Thing, name, version);

#endif

