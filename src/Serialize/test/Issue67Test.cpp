#include "gtest/gtest.h"
#include "test/SerializeTest.h"
#include "Traits.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include "SerUtil.h"
#include <memory>
#include <iostream>
#include <sstream>

struct Type1
{
    int a;
};
struct Type2
{
    static int b;
    static Type1 c;
};

int Type2::b = 12;
Type1 Type2::c;

ThorsAnvil_MakeTrait(Type1, a);
ThorsAnvil_MakeTrait(Type2, b, c);

TEST(Issue67Test, StaticMemberSerialization)
{
    using ThorsAnvil::Serialize::jsonExporter;
    using ThorsAnvil::Serialize::jsonImporter;

    std::stringstream    fileStream;
    Type2 entity;
    fileStream >> jsonImporter(entity);
    fileStream << jsonExporter(entity);

}

