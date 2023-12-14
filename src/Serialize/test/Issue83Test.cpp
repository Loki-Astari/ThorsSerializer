#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "test/SerializeTest.h"
#include "Serialize.h"
#include "Traits.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include "SerUtil.h"
#include <memory>
#include <iostream>

struct Example
{
    int x{0};
};
struct Adeek
{
    std::shared_ptr<const Example> member;
};

ThorsAnvil_MakeTrait(Example, x);
ThorsAnvil_MakeTrait(Adeek, member);



TEST(Issue83Test, test1)
{
    using ThorsAnvil::Serialize::jsonExporter;

    Adeek obj;
    std::stringstream   outputJSONStream;

    outputJSONStream << jsonExporter(obj);
};


