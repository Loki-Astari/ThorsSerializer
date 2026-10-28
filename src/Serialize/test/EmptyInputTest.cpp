#include <gtest/gtest.h>

#include "Traits.h"
#include "SerUtil.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include "YamlThor.h"

#include <string>
#include <sstream>


struct EmptyTestStruct
{
    std::string     data1;
    std::string     data2;
    std::string     data3;
    std::string     data4;
};

ThorsAnvil_MakeTrait(EmptyTestStruct,data1,data2,data3,data4);


// JSON

TEST(EmptyInputTest, JsonValString)
{
    std::stringstream   s;

    std::string         val;
    bool                succ = false;

    if (s >> ThorsAnvil::Serialize::jsonImporter(val)) {
        succ = true;
    }

    EXPECT_FALSE(succ);
}

TEST(EmptyInputTest, JsonValInt)
{
    std::stringstream   s;

    int                 val;
    bool                succ = false;

    if (s >> ThorsAnvil::Serialize::jsonImporter(val)) {
        succ = true;
    }

    EXPECT_FALSE(succ);
}

TEST(EmptyInputTest, JsonStruct)
{
    std::stringstream   s;

    EmptyTestStruct     val;
    bool                succ = false;

    if (s >> ThorsAnvil::Serialize::jsonImporter(val)) {
        succ = true;
    }

    EXPECT_FALSE(succ);
}

TEST(EmptyInputTest, JsonValStringFromString)
{
    std::string         s;

    std::string         val;
    bool                succ = false;

    if (s >> ThorsAnvil::Serialize::jsonImporter(val)) {
        succ = true;
    }

    EXPECT_FALSE(succ);
}

TEST(EmptyInputTest, JsonValIntFromString)
{
    std::string         s;

    int                 val;
    bool                succ = false;

    if (s >> ThorsAnvil::Serialize::jsonImporter(val)) {
        succ = true;
    }

    EXPECT_FALSE(succ);
}

TEST(EmptyInputTest, JsonStructFromString)
{
    std::string         s;

    EmptyTestStruct     val;
    bool                succ = false;

    if (s >> ThorsAnvil::Serialize::jsonImporter(val)) {
        succ = true;
    }

    EXPECT_FALSE(succ);
}

// BSON

TEST(EmptyInputTest, BsonValString)
{
    std::stringstream   s;

    std::string         val;
    bool                succ = false;

    if (s >> ThorsAnvil::Serialize::bsonImporter(val)) {
        succ = true;
    }

    EXPECT_FALSE(succ);
}

TEST(EmptyInputTest, BsonValInt)
{
    std::stringstream   s;

    int                 val;
    bool                succ = false;

    if (s >> ThorsAnvil::Serialize::bsonImporter(val)) {
        succ = true;
    }

    EXPECT_FALSE(succ);
}

TEST(EmptyInputTest, BsonStruct)
{
    std::stringstream   s;

    EmptyTestStruct     val;
    bool                succ = false;

    if (s >> ThorsAnvil::Serialize::bsonImporter(val)) {
        succ = true;
    }

    EXPECT_FALSE(succ);
}

TEST(EmptyInputTest, BsonValStringFromString)
{
    std::stringstream   s;

    std::string         val;
    bool                succ = false;

    if (s >> ThorsAnvil::Serialize::bsonImporter(val)) {
        succ = true;
    }

    EXPECT_FALSE(succ);
}

TEST(EmptyInputTest, BsonValIntFromString)
{
    std::stringstream   s;

    int                 val;
    bool                succ = false;

    if (s >> ThorsAnvil::Serialize::bsonImporter(val)) {
        succ = true;
    }

    EXPECT_FALSE(succ);
}

TEST(EmptyInputTest, BsonStructFromString)
{
    std::string         s;

    EmptyTestStruct     val;
    bool                succ = false;

    if (s >> ThorsAnvil::Serialize::bsonImporter(val)) {
        succ = true;
    }

    EXPECT_FALSE(succ);
}

// YAML

TEST(EmptyInputTest, YamlValString)
{
    std::stringstream   s;

    std::string         val;
    bool                succ = false;

    if (s >> ThorsAnvil::Serialize::yamlImporter(val)) {
        succ = true;
    }

    EXPECT_FALSE(succ);
}

TEST(EmptyInputTest, YamlValInt)
{
    std::stringstream   s;

    int                 val;
    bool                succ = false;

    if (s >> ThorsAnvil::Serialize::yamlImporter(val)) {
        succ = true;
    }

    EXPECT_FALSE(succ);
}

TEST(EmptyInputTest, YamlStruct)
{
    std::stringstream   s;

    EmptyTestStruct     val;
    bool                succ = false;

    if (s >> ThorsAnvil::Serialize::yamlImporter(val)) {
        succ = true;
    }

    EXPECT_FALSE(succ);
}

TEST(EmptyInputTest, YamlValStringFromString)
{
    std::string         s;

    std::string         val;
    bool                succ = false;

    if (s >> ThorsAnvil::Serialize::yamlImporter(val)) {
        succ = true;
    }

    EXPECT_FALSE(succ);
}

TEST(EmptyInputTest, YamlValIntFromString)
{
    std::string         s;

    int                 val;
    bool                succ = false;

    if (s >> ThorsAnvil::Serialize::yamlImporter(val)) {
        succ = true;
    }

    EXPECT_FALSE(succ);
}

TEST(EmptyInputTest, YamlStructFromString)
{
    std::string         s;

    EmptyTestStruct     val;
    bool                succ = false;

    if (s >> ThorsAnvil::Serialize::yamlImporter(val)) {
        succ = true;
    }

    EXPECT_FALSE(succ);
}

