#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "BsonThor.h"
#include "test/BsonUtilitySerializationTest.h"
#include <sstream>


using namespace ThorsAnvil::Serialize;

TEST(BsonUtilitySerializationTestString, ObjectIDSerialize)
{
    std::string    stream;
    MongoObjectID  object(0x12345678,0x9ABCDEF053LL,0x1A2B3C);

    stream << ThorsAnvil::Serialize::bsonExporter(object);
    std::string result = stream;

    static const char expectedRaw[]
                = "\x15\x00\x00\x00"
                  "\x07" "id\x00" "\x12\x34\x56\x78" "\x9A\xBC\xDE\xF0\x53" "\x1A\x2B\x3C"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);

    EXPECT_EQ(expected, result);
}
TEST(BsonUtilitySerializationTestString, ObjectIDGetSize)
{
    std::string        stream;
    MongoObjectID  object(0x12345678,0x9ABCDEF053LL,0x1A2B3C);

    std::size_t size = ThorsAnvil::Serialize::bsonGetPrintSize(object);
    EXPECT_EQ(0x15, size);
}

TEST(BsonUtilitySerializationTestString, ObjectIDRoundTrip)
{
    std::string        stream;
    MongoObjectID  object(0x12345678,0x9ABCDEF053LL,0x1A2B3C);

    stream << ThorsAnvil::Serialize::bsonExporter(object);

    MongoObjectID  result(8, 9, 10);
    stream >> ThorsAnvil::Serialize::bsonImporter(result);

    EXPECT_EQ(object, result);
}
TEST(BsonUtilitySerializationTestString, UTCDateTimeSerialize)
{
    std::string        stream;
    MongoUTCDateTime   object(0x123456789ABCDEF0LL);


    stream << ThorsAnvil::Serialize::bsonExporter(object);
    std::string result = stream;

    static const char expectedRaw[]
                = "\x11\x00\x00\x00"
                  "\x09" "dt\x00" "\xf0\xde\xbc\x9a" "\x78\x56\x34\x12" // "\x12\x34\x56\x78" "\x9A\xBC\xDE\xF0"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);

    EXPECT_EQ(expected, result);
}

TEST(BsonUtilitySerializationTestString, UTCDateTimeRoundTrip)
{
    std::string        stream;
    MongoUTCDateTime    object(0x123456789ABCDEF0LL);

    stream << ThorsAnvil::Serialize::bsonExporter(object);

    MongoUTCDateTime    result(8);
    stream >> ThorsAnvil::Serialize::bsonImporter(result);

    EXPECT_EQ(object, result);
}
TEST(BsonUtilitySerializationTestString, BsonTimeStampSerialize)
{
    std::string        stream;
    MongoBsonTimeStamp    object(0x12345678, 0x9ABCDEF0);


    stream << ThorsAnvil::Serialize::bsonExporter(object);
    std::string result = stream;

    static const char expectedRaw[]
                = "\x11\x00\x00\x00"
                  "\x11" "ts\x00" "\x9A\xBC\xDE\xF0" "\x12\x34\x56\x78"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);

    EXPECT_EQ(expected, result);
}

TEST(BsonUtilitySerializationTestString, BsonTimeStampRoundTrip)
{
    std::string        stream;
    MongoBsonTimeStamp    object(0x12345678, 0x9ABCDEF0);

    stream << ThorsAnvil::Serialize::bsonExporter(object);

    MongoBsonTimeStamp    result(8,9);
    stream >> ThorsAnvil::Serialize::bsonImporter(result);

    EXPECT_EQ(object, result);
}

TEST(BsonUtilitySerializationTestString, BsonBinarySerializer)
{
    MongoBsonBinary  data("This is a binary test");
    std::string        stream;

    stream << ThorsAnvil::Serialize::bsonExporter(data);

    static const char expectedRaw[]
                = "\x27\x00\x00\x00"
                  "\x05" "binary\x00"
                            "\x15\x00\x00\x00" "\x08"
                            "This is a binary test"
                  "\x00";

    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(expected, stream);
}

TEST(BsonUtilitySerializationTestString, BsonBinarySerializerRoundTrip)
{
    MongoBsonBinary  data("This is a binary test");
    std::string        stream;

    stream << ThorsAnvil::Serialize::bsonExporter(data);
    MongoBsonBinary  result("XXXXX");
    stream >> ThorsAnvil::Serialize::bsonImporter(result);

    EXPECT_EQ(data, result);
}

TEST(BsonUtilitySerializationTestString, BsonJavascriptSerializer)
{
    MongoBsonJsavScript data("function myrand() {return 4;}");
    std::string        stream;

    stream << ThorsAnvil::Serialize::bsonExporter(data);

    static const char expectedRaw[]
                = "\x33\x00\x00\x00"
                  "\x0D" "javascript\x00"
                            "\x1E\x00\x00\x00" "function myrand() {return 4;}\x00"
                  "\x00";

    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(expected, stream);
}

TEST(BsonUtilitySerializationTestString, BsonJavascriptSerializerRoundtrip)
{
    MongoBsonJsavScript data("function myrand() {return 4;}");
    std::string        stream;

    stream << ThorsAnvil::Serialize::bsonExporter(data);
    MongoBsonJsavScript result("XXXX");

    stream >> ThorsAnvil::Serialize::bsonImporter(result);

    EXPECT_EQ(data, result);
}

TEST(BsonUtilitySerializationTestString, BsonRegExSerializer)
{
    MongoBsonRegExp    data("^[ \\t]*", "g");
    std::string        stream;

    stream << ThorsAnvil::Serialize::bsonExporter(data);

    static const char expectedRaw[]
                = "\x16\x00\x00\x00"
                  "\x0B" "regex\x00"
                            "^[ \\t]*\x00"
                            "g\x00"
                  "\x00";

    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(expected, stream);
}
TEST(BsonUtilitySerializationTestString, BsonRegExSerializerRoundtrip)
{
    MongoBsonRegExp    data("^[ \\t]*", "g");
    std::string        stream;

    stream << ThorsAnvil::Serialize::bsonExporter(data);
    MongoBsonRegExp     result("X", "Y");

    stream >> ThorsAnvil::Serialize::bsonImporter(result);

    EXPECT_EQ(data, result);
}

