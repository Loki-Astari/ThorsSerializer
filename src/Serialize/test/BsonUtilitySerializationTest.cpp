#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "BsonThor.h"
#include "test/BsonUtilitySerializationTest.h"
#include <sstream>


using namespace ThorsAnvil::Serialize;

TEST(BsonUtilitySerializationTest, ObjectIDSerialize)
{
    std::stringstream stream;
    MongoObjectID  object(0x12345678,0x9ABCDEF053LL,0x1A2B3C);

    stream << ThorsAnvil::Serialize::bsonExporter(object);
    std::string result = stream.str();

    static const char expectedRaw[]
                = "\x15\x00\x00\x00"
                  "\x07" "id\x00" "\x12\x34\x56\x78" "\x9A\xBC\xDE\xF0\x53" "\x1A\x2B\x3C"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);

    EXPECT_EQ(expected, result);
}

TEST(BsonUtilitySerializationTest, ObjectIDRoundTrip)
{
    std::stringstream stream;
    MongoObjectID  object(0x12345678,0x9ABCDEF053LL,0x1A2B3C);

    stream << ThorsAnvil::Serialize::bsonExporter(object);

    MongoObjectID  result(8, 9, 10);
    stream >> ThorsAnvil::Serialize::bsonImporter(result);

    EXPECT_EQ(object.id, result.id);
}
TEST(BsonUtilitySerializationTest, UTCDateTimeSerialize)
{
    std::stringstream stream;
    MongoUTCDateTime   object(0x123456789ABCDEF0LL);


    stream << ThorsAnvil::Serialize::bsonExporter(object);
    std::string result = stream.str();

    static const char expectedRaw[]
                = "\x11\x00\x00\x00"
                  "\x09" "dt\x00" "\x12\x34\x56\x78" "\x9A\xBC\xDE\xF0"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);

    EXPECT_EQ(expected, result);
}

TEST(BsonUtilitySerializationTest, UTCDateTimeRoundTrip)
{
    std::stringstream stream;
    MongoUTCDateTime    object(0x123456789ABCDEF0LL);

    stream << ThorsAnvil::Serialize::bsonExporter(object);

    MongoUTCDateTime    result(8);
    stream >> ThorsAnvil::Serialize::bsonImporter(result);

    EXPECT_EQ(object.dt, result.dt);
}
TEST(BsonUtilitySerializationTest, BsonTimeStampSerialize)
{
    std::stringstream stream;
    MongoBsonTimeStamp    object(0x12345678, 0x9ABCDEF0);


    stream << ThorsAnvil::Serialize::bsonExporter(object);
    std::string result = stream.str();

    static const char expectedRaw[]
                = "\x11\x00\x00\x00"
                  "\x11" "ts\x00" "\x9A\xBC\xDE\xF0" "\x12\x34\x56\x78"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);

    EXPECT_EQ(expected, result);
}

TEST(BsonUtilitySerializationTest, BsonTimeStampRoundTrip)
{
    std::stringstream stream;
    MongoBsonTimeStamp    object(0x12345678, 0x9ABCDEF0);

    stream << ThorsAnvil::Serialize::bsonExporter(object);

    MongoBsonTimeStamp    result(8,9);
    stream >> ThorsAnvil::Serialize::bsonImporter(result);

    EXPECT_EQ(object.ts, result.ts);
}

