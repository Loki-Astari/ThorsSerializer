#include "Traits.h"
#include "Serialize.h"
#include <string>
#include <memory>

namespace SmartPtrTest
{
    struct Object
    {
        int         id;
        std::string name;
    };
}
ThorsAnvil_MakeTrait(SmartPtrTest::Object, id, name);

