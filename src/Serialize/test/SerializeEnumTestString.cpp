#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include "Serialize.h"
#include "test/SerializeTest.h"
#include <algorithm>

extern std::string stripspace(std::string const& value);

TEST(SerializeEnumTestString, JsonRedGreenBlueAtRed)
{
    SerializeTest::RGB      enumHolder {SerializeTest::Red};
    std::string   str;
    str << ThorsAnvil::Serialize::jsonExporter(enumHolder, false);

    EXPECT_EQ(R"("Red")", stripspace(str));
}
TEST(SerializeEnumTestString, JsonRedGreenBlueAtGreen)
{
    SerializeTest::RGB      enumHolder {SerializeTest::Green};
    std::string   str;
    str << ThorsAnvil::Serialize::jsonExporter(enumHolder, false);

    EXPECT_EQ(R"("Green")", stripspace(str));
}
TEST(SerializeEnumTestString, JsonRedGreenBlueAtBlue)
{
    SerializeTest::RGB      enumHolder {SerializeTest::Blue};
    std::string   str;
    str << ThorsAnvil::Serialize::jsonExporter(enumHolder, false);

    EXPECT_EQ(R"("Blue")", stripspace(str));
}
TEST(SerializeEnumTestString, JsonRefGreenBlueFromRed)
{
    std::string            str(R"("Red")");
    SerializeTest::RGB     enumHolder {SerializeTest::Green};

    str >> ThorsAnvil::Serialize::jsonImporter(enumHolder, false);
    EXPECT_EQ(SerializeTest::Red, enumHolder);
}
TEST(SerializeEnumTestString, JsonRefGreenBlueFromGreen)
{
    std::string            str(R"("Green")");
    SerializeTest::RGB     enumHolder {SerializeTest::Red};

    str >> ThorsAnvil::Serialize::jsonImporter(enumHolder, false);
    EXPECT_EQ(SerializeTest::Green, enumHolder);
}
TEST(SerializeEnumTestString, JsonRefGreenBlueFromBlue)
{
    std::string            str(R"("Blue")");
    SerializeTest::RGB     enumHolder {SerializeTest::Green};

    str >> ThorsAnvil::Serialize::jsonImporter(enumHolder, false);
    EXPECT_EQ(SerializeTest::Blue, enumHolder);
}
TEST(SerializeEnumTestString, JsonSerEnumInContainer)
{
    SerializeTest::EumHolder  holder { SerializeTest::Red };

    std::string   str;

    str << ThorsAnvil::Serialize::jsonExporter(holder, false);
    EXPECT_EQ(R"({"value":"Red"})", stripspace(str));
}
TEST(SerializeEnumTestString, JsonDeSerEnumInContainer)
{
    SerializeTest::EumHolder  holder { SerializeTest::Red };
    std::string            str(R"({"value": "Green"})");

    str >> ThorsAnvil::Serialize::jsonImporter(holder, false);
    EXPECT_EQ(SerializeTest::Green, holder.value);
}


TEST(SerializeEnumTestString, BsonRedGreenBlueAtRed)
{
    SerializeTest::RGB      enumHolder {SerializeTest::Red};
    std::string   str;
    str << ThorsAnvil::Serialize::bsonExporter(enumHolder, false);

    static const char expectedRaw[]
                = "\x10\x00\x00\x00"
                  "\x02" "0\x00" "\x04\x00\x00\x00"  "Red\x00"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(expected, str);
    //NOTE OUTPUT (R"("Red")", stripspace(str));
}
TEST(SerializeEnumTestString, BsonRedGreenBlueAtGreen)
{
    SerializeTest::RGB      enumHolder {SerializeTest::Green};
    std::string   str;
    str << ThorsAnvil::Serialize::bsonExporter(enumHolder, false);

    static const char expectedRaw[]
                = "\x12\x00\x00\x00"
                  "\x02" "0\x00" "\x06\x00\x00\x00"  "Green\x00"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(expected, str);
    //NOTE OUTPUT (R"("Green")", stripspace(str));
}
TEST(SerializeEnumTestString, BsonRedGreenBlueAtBlue)
{
    SerializeTest::RGB      enumHolder {SerializeTest::Blue};
    std::string   str;
    str << ThorsAnvil::Serialize::bsonExporter(enumHolder, false);

    static const char expectedRaw[]
                = "\x11\x00\x00\x00"
                  "\x02" "0\x00" "\x05\x00\x00\x00"  "Blue\x00"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(expected, str);
    //NOTE OUTPUT  (R"("Blue")", stripspace(str));
}
TEST(SerializeEnumTestString, BsonRefGreenBlueFromRed)
{
    //NOTE INPUT (R"("Red")");
    static const char inputRaw[]
                = "\x10\x00\x00\x00"
                  "\x02" "0\x00" "\x04\x00\x00\x00"  "Red\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::string            str(input);
    SerializeTest::RGB     enumHolder {SerializeTest::Green};

    str >> ThorsAnvil::Serialize::bsonImporter(enumHolder, false);
    EXPECT_EQ(SerializeTest::Red, enumHolder);
}
TEST(SerializeEnumTestString, BsonRefGreenBlueFromGreen)
{
    //NOTE INPUT (R"("Green")");
    static const char inputRaw[]
                = "\x12\x00\x00\x00"
                  "\x02" "0\x00" "\x06\x00\x00\x00"  "Green\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::string            str(input);
    SerializeTest::RGB     enumHolder {SerializeTest::Red};

    str >> ThorsAnvil::Serialize::bsonImporter(enumHolder, false);
    EXPECT_EQ(SerializeTest::Green, enumHolder);
}
TEST(SerializeEnumTestString, BsonRefGreenBlueFromBlue)
{
    //NOTE INPUT (R"("Blue")");
    static const char inputRaw[]
                = "\x11\x00\x00\x00"
                  "\x02" "0\x00" "\x05\x00\x00\x00"  "Blue\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::string            str(input);
    SerializeTest::RGB     enumHolder {SerializeTest::Green};

    str >> ThorsAnvil::Serialize::bsonImporter(enumHolder, false);
    EXPECT_EQ(SerializeTest::Blue, enumHolder);
}
TEST(SerializeEnumTestString, BsonSerEnumInContainer)
{
    SerializeTest::EumHolder  holder { SerializeTest::Red };

    std::string   str;

    str << ThorsAnvil::Serialize::bsonExporter(holder, false);
    static const char expectedRaw[]
                = "\x14\x00\x00\x00"
                  "\x02" "value\x00" "\x04\x00\x00\x00"  "Red\x00"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(expected, str);
    //NOTE OUTPUT  (R"({"value":"Red"})", stripspace(str));
}
TEST(SerializeEnumTestString, BsonDeSerEnumInContainer)
{
    SerializeTest::EumHolder  holder { SerializeTest::Red };
    //NOTE INPUT (R"({"value": "Green"})");
    static const char inputRaw[]
                = "\x16\x00\x00\x00"
                  "\x02" "value\x00" "\x06\x00\x00\x00"  "Green\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::string            str(input);

    str >> ThorsAnvil::Serialize::bsonImporter(holder, false);
    EXPECT_EQ(SerializeTest::Green, holder.value);
}

