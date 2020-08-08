#include "SerializeConfig.h"
#include "IgnoreUneededData.h"
#include "gtest/gtest.h"
#include "JsonThor.h"
#include "BsonThor.h"

TEST(IgnoreUneededData, JsonArrayEmpty)
{
    IgnoreUneededData::Thing obj;
    obj.name = "Test";

    std::stringstream data;
    data << TA::jsonExporter(obj, false);

    IgnoreUneededData::ThingVersion objver;
    data >> TA::jsonImporter(objver, false);
/*
    EXPECT_EQ(3, objver.version);
*/
}
TEST(IgnoreUneededData, BsonArrayEmpty)
{
    IgnoreUneededData::Thing obj;
    obj.name = "Test";

    std::stringstream data;
    data << TA::bsonExporter(obj, false);

    IgnoreUneededData::ThingVersion objver;
    data >> TA::bsonImporter(objver, false);
/*
    EXPECT_EQ(3, objver.version);
*/
}

