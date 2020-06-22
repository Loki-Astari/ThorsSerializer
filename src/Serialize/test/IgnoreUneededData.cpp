#include "SerializeConfig.h"
#include "IgnoreUneededData.h"
#include "gtest/gtest.h"
#include "JsonThor.h"

TEST(IgnoreUneededData, ArrayEmpty)
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

