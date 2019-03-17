
#include "IgnoreUneededData.h"
#include "gtest/gtest.h"
#include "JsonThor.h"

TEST(IgnoreUneededData, ArrayEmpty)
{
    IgnoreUneededData::Thing obj;
    obj.name = "Test";

    std::stringstream data;
    data << TA::jsonExport(obj);

    IgnoreUneededData::ThingVersion objver;
    data >> TA::jsonImport(objver);
/*
    EXPECT_EQ(3, objver.version);
*/
}

