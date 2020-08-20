#include "Traits.h"
#include "BsonThor.h"

struct MarvinObject
{
    ThorsAnvil::Serialize::ObjectID id;
    friend class ThorsAnvil::Serialize::Traits<MarvinObject>;
    public:
        MarvinObject(std::int32_t timestamp, std::int64_t random, std::int32_t counter)
            : id(timestamp, random, counter)
        {}
};

ThorsAnvil_MakeTrait(MarvinObject, id);
