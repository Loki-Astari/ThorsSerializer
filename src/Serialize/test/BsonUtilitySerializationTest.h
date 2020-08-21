#include "Traits.h"
#include "MongoUtility.h"

struct MongoObjectID
{
    ThorsAnvil::Serialize::MongoUtility::ObjectID id;
    friend class ThorsAnvil::Serialize::Traits<MongoObjectID>;
    public:
        MongoObjectID(std::int32_t timestamp, std::int64_t random, std::int32_t counter)
            : id(timestamp, random, counter)
        {}
};
struct MongoUTCDateTime
{
    ThorsAnvil::Serialize::MongoUtility::UTCDateTime dt;
    friend class ThorsAnvil::Serialize::Traits<MongoUTCDateTime>;
    public:
        MongoUTCDateTime(std::int64_t timestamp)
            : dt(timestamp)
        {}
};
struct MongoBsonTimeStamp
{
    ThorsAnvil::Serialize::MongoUtility::BsonTimeStamp ts;
    friend class ThorsAnvil::Serialize::Traits<MongoBsonTimeStamp>;
    public:
        MongoBsonTimeStamp(std::int32_t timestamp, int inc)
            : ts(timestamp, inc)
        {}
};

ThorsAnvil_MakeTrait(MongoObjectID,        id);
ThorsAnvil_MakeTrait(MongoUTCDateTime,     dt);
ThorsAnvil_MakeTrait(MongoBsonTimeStamp,   ts);
