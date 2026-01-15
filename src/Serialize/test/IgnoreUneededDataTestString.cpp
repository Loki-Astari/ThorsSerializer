#include "gtest/gtest.h"
#include "IgnoreUneededDataTest.h"
#include "JsonThor.h"
#include "BsonThor.h"

TEST(IgnoreUneededDataTestString, JsonArrayEmpty)
{
    IgnoreUneededDataTest::Thing obj;
    obj.name = "Test";

    std::string   data;
    data << TA::jsonExporter(obj, false);

    IgnoreUneededDataTest::ThingVersion objver;
    data >> TA::jsonImporter(objver, false);

    EXPECT_EQ(3, objver.version);
}
TEST(IgnoreUneededDataTestString, BsonArrayEmpty)
{
    IgnoreUneededDataTest::Thing obj;
    obj.name = "Test";

    std::string   data;
    data << TA::bsonExporter(obj, false);

    IgnoreUneededDataTest::ThingVersion objver;
    data >> TA::bsonImporter(objver, false);

    EXPECT_EQ(3, objver.version);
}

