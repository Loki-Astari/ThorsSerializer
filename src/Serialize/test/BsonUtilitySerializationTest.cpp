#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "BsonThor.h"
#include "test/BsonUtilitySerializationTest.h"
#include <sstream>


using namespace ThorsAnvil::Serialize;

TEST(BsonUtilitySerializationTest, ObjectIDSerialize)
{
    std::stringstream stream;
    MarvinObject    object(1,2,3);

    stream << ThorsAnvil::Serialize::bsonExporter(object);
    std::string result = stream.str();

    static const char expectedRaw[]
                = "\x15\x00\x00\x00"
                  "\x07" "id\x00" "\x00\x00\x00\x01" "\x00\x00\x00\x00\x02" "\x00\x00\x03"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);

    EXPECT_EQ(expected, result);
}

TEST(BsonUtilitySerializationTest, ObjectIDRoundTrip)
{
    std::stringstream stream;
    MarvinObject    object(4,5,6);

    stream << ThorsAnvil::Serialize::bsonExporter(object);

    MarvinObject    result(8, 9, 10);
    stream >> ThorsAnvil::Serialize::bsonImporter(result);

    EXPECT_EQ(object.id, result.id);
}

