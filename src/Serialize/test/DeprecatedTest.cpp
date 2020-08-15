#include "SerializeConfig.h"
#include "IgnoreUneededDataTest.h"
#include "gtest/gtest.h"
#include "JsonThor.h"
#include "YamlThor.h"

TEST(DeprecatedTest, Json)
{
    IgnoreUneededDataTest::Thing obj;

    std::stringstream data;
    data << TA::jsonExport(obj);

    IgnoreUneededDataTest::Thing objver;
    data >> TA::jsonImport(objver);
}
TEST(DeprecatedTest, Yaml)
{
    IgnoreUneededDataTest::Thing obj;

    std::stringstream data;
    data << TA::yamlExport(obj);

    IgnoreUneededDataTest::Thing objver;
    data >> TA::yamlImport(objver);
}

