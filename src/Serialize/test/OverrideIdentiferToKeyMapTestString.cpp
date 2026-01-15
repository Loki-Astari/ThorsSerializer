#include "gtest/gtest.h"
#include "Traits.h"
#include "SerUtil.h"
#include "JsonThor.h"
#include "YamlThor.h"
#include "BsonThor.h"

#include <string>
#include <sstream>

using namespace std::string_literals;

struct OverrideTest
{
    int             percentKey;
    std::string     deleteKey;
};

template<typename Doc>
struct OverrideTemplate
{
    Doc             percentKey;
    std::string     deleteKey;
};

ThorsAnvil_MakeOverride(OverrideTest, {"percentKey", "%"}, {"deleteKey", "delete"});
ThorsAnvil_Template_MakeOverride(1, OverrideTemplate, {"percentKey", "%"}, {"deleteKey", "delete"});
ThorsAnvil_MakeTrait(OverrideTest, percentKey, deleteKey);
ThorsAnvil_Template_MakeTrait(1, OverrideTemplate, percentKey, deleteKey);

TEST(OverrideIdentiferToKeyMapTestString, JsonExportCheckNormalOverrideWorks)
{
    OverrideTest    object{34, "The Stuff to Delete"};

    std::string          stream;
    stream << ThorsAnvil::Serialize::jsonExporter(object);
    std::string output = stream;

    auto findPercent =output.find(R"("%")");
    EXPECT_NE(std::string::npos, findPercent);

    auto findDelete =output.find(R"("delete")");
    EXPECT_NE(std::string::npos, findDelete);
}

TEST(OverrideIdentiferToKeyMapTestString, JsonImportCheckNormalOverrideWorks)
{
    std::string     stream(R"({"%": 567, "delete": "A valid string"})");


    OverrideTest    object{34, "The Stuff to Delete"};
    stream >> ThorsAnvil::Serialize::jsonImporter(object);

    EXPECT_EQ(567, object.percentKey);
    EXPECT_EQ("A valid string", object.deleteKey);
}

TEST(OverrideIdentiferToKeyMapTestString, YamlExportCheckNormalOverrideWorks)
{
    OverrideTest    object{34, "The Stuff to Delete"};

    std::string          stream;
    stream << ThorsAnvil::Serialize::yamlExporter(object);
    std::string output = stream;

    auto findPercent =output.find("%");
    EXPECT_NE(std::string::npos, findPercent);

    auto findDelete =output.find("delete");
    EXPECT_NE(std::string::npos, findDelete);
}

TEST(OverrideIdentiferToKeyMapTestString, YamlImportCheckNormalOverrideWorks)
{
    std::string     stream(R"(
---
'%': 567
delete: 'A valid string'
...
)");


    OverrideTest    object{34, "The Stuff to Delete"};
    stream >> ThorsAnvil::Serialize::yamlImporter(object);

    EXPECT_EQ(567, object.percentKey);
    EXPECT_EQ("A valid string", object.deleteKey);
}

TEST(OverrideIdentiferToKeyMapTestString, BsonExportCheckNormalOverrideWorks)
{
    OverrideTest    object{34, "The Stuff to Delete"};

    std::string          stream;
    stream << ThorsAnvil::Serialize::bsonExporter(object);
    std::string output = stream;

    auto findPercent =output.find("\x10" "%\x00"s);
    EXPECT_NE(std::string::npos, findPercent);

    auto findDelete =output.find("\x02" "delete\x00"s);
    EXPECT_NE(std::string::npos, findDelete);
}

TEST(OverrideIdentiferToKeyMapTestString, BsonImportCheckNormalOverrideWorks)
{
    std::string     stream("\x27\x00\x00\x00"
                             "\x10"   "%\x00"       "\x37\x02\x00\x00"
                             "\x02"   "delete\x00"  "\x0F\x00\x00\x00"  "A valid string\x00"
                             "\x00"s);


    OverrideTest    object{34, "The Stuff to Delete"};
    stream >> ThorsAnvil::Serialize::bsonImporter(object);

    EXPECT_EQ(567, object.percentKey);
    EXPECT_EQ("A valid string", object.deleteKey);
}

TEST(OverrideIdentiferToKeyMapTestString, JsonExportCheckTemplateOverrideWorks)
{
    OverrideTemplate<double>    object{12.23, "The Stuff to Delete"};

    std::string          stream;
    stream << ThorsAnvil::Serialize::jsonExporter(object);
    std::string output = stream;

    auto findPercent =output.find(R"("%")");
    EXPECT_NE(std::string::npos, findPercent);

    auto findDelete =output.find(R"("delete")");
    EXPECT_NE(std::string::npos, findDelete);
}

TEST(OverrideIdentiferToKeyMapTestString, JsonImportCheckTemplateOverrideWorks)
{
    std::string     stream(R"({"%": 567.0, "delete": "A valid string"})");


    OverrideTemplate<double>    object{12.23, "The Stuff to Delete"};
    stream >> ThorsAnvil::Serialize::jsonImporter(object);

    EXPECT_EQ(567.0, object.percentKey);
    EXPECT_EQ("A valid string", object.deleteKey);
}

TEST(OverrideIdentiferToKeyMapTestString, YamlExportCheckTemplateOverrideWorks)
{
    OverrideTemplate<double>    object{12.23, "The Stuff to Delete"};

    std::string          stream;
    stream << ThorsAnvil::Serialize::yamlExporter(object);
    std::string output = stream;

    auto findPercent =output.find("%");
    EXPECT_NE(std::string::npos, findPercent);

    auto findDelete =output.find("delete");
    EXPECT_NE(std::string::npos, findDelete);
}

TEST(OverrideIdentiferToKeyMapTestString, YamlImportCheckTemplateOverrideWorks)
{
    std::string     stream(R"(
---
'%': 567.0
delete: 'A valid string'
...
)");


    OverrideTemplate<double>    object{12.23, "The Stuff to Delete"};
    stream >> ThorsAnvil::Serialize::yamlImporter(object);

    EXPECT_EQ(567.0, object.percentKey);
    EXPECT_EQ("A valid string", object.deleteKey);
}

TEST(OverrideIdentiferToKeyMapTestString, BsonExportCheckTemplateOverrideWorks)
{
    OverrideTemplate<double>    object{12.23, "The Stuff to Delete"};

    std::string          stream;
    stream << ThorsAnvil::Serialize::bsonExporter(object);
    std::string output = stream;

    auto findPercent =output.find("\x01" "%\x00"s);
    EXPECT_NE(std::string::npos, findPercent);

    auto findDelete =output.find("\x02" "delete\x00"s);
    EXPECT_NE(std::string::npos, findDelete);
}

TEST(OverrideIdentiferToKeyMapTestString, BsonImportCheckTemplateOverrideWorks)
{
    std::string     stream("\x2B\x00\x00\x00"
                             "\x01"   "%\x00"       "\x00\x00\x00\x00\x00\xB8\x81\x40"
                             "\x02"   "delete\x00"  "\x0F\x00\x00\x00"  "A valid string\x00"
                             "\x00"s);


    OverrideTemplate<double>    object{12.23, "The Stuff to Delete"};
    stream >> ThorsAnvil::Serialize::bsonImporter(object);

    EXPECT_EQ(567.0, object.percentKey);
    EXPECT_EQ("A valid string", object.deleteKey);
}


