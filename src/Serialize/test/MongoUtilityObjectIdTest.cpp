#include "gtest/gtest.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include "MongoUtility.h"

using namespace ThorsAnvil::Serialize;
using ThorsAnvil::Serialize::MongoUtility::ObjectID;

TEST(MongoUtilityObjectIdTest, JsonSerialzieObjectID)
{
    ObjectID            objectId{1, 2, 3};
    std::stringstream   ss;

    ss << jsonExporter(objectId, PrinterConfig{OutputType::Stream});

    EXPECT_EQ(R"("00000001-0000000002-000003")", ss.str());
}

TEST(MongoUtilityObjectIdTest, JsonArray)
{
    std::vector<ObjectID>            vec;
    vec.emplace_back(1, 2, 3);
    vec.emplace_back(4, 5, 6);
    vec.emplace_back(7, 8, 9);
    std::stringstream   ss;

    ss << jsonExporter(vec, PrinterConfig{OutputType::Stream});

    EXPECT_EQ(R"(["00000001-0000000002-000003","00000004-0000000005-000006","00000007-0000000008-000009"])", ss.str());
}

struct ObjectIdInObject
{
    ObjectID    v1;
    int         v2;
    ObjectID    v3;
    std::string v4;
    ObjectID    v5;
};
ThorsAnvil_MakeTrait(ObjectIdInObject, v1,v2,v3,v4,v5);


TEST(MongoUtilityObjectIdTest, JsonObject)
{
    ObjectIdInObject                data{{1,2,3}, 8, {10,12,13}, "Hi There", {32,48,64}};
    std::stringstream   ss;

    ss << jsonExporter(data, PrinterConfig{OutputType::Stream});

    EXPECT_EQ(R"({"v1":"00000001-0000000002-000003","v2":8,"v3":"0000000a-000000000c-00000d","v4":"Hi There","v5":"00000020-0000000030-000040"})", ss.str());
}


TEST(MongoUtilityObjectIdTest, BsonSerialzieObjectID)
{
    ObjectID            objectId{1, 2, 3};
    std::stringstream   ss;

    ss << bsonExporter(objectId, PrinterConfig{OutputType::Stream});

    using std::string_literals::operator""s;
    char x = ss.str()[4];
    std::cerr << "X(" << ((int) x) << "\n";
    EXPECT_EQ("\x14\x00\x00\x00"
              "\x07" "0\x00" "\x00\x00\x00\x01" "\x00\x00\x00\x00\x02" "\x00\x00\x03"
              "\x00"s,
              ss.str()
             );
}

TEST(MongoUtilityObjectIdTest, BsonArray)
{
    std::vector<ObjectID>            vec;
    vec.emplace_back(1, 2, 3);
    vec.emplace_back(4, 5, 6);
    vec.emplace_back(7, 8, 9);
    std::stringstream   ss;

    ss << bsonExporter(vec, PrinterConfig{OutputType::Stream});

    using std::string_literals::operator""s;
    EXPECT_EQ("\x32\x00\x00\x00"
                    "\x07" "0\x00" "\x00\x00\x00\x01" "\x00\x00\x00\x00\x02" "\x00\x00\x03"
                    "\x07" "1\x00" "\x00\x00\x00\x04" "\x00\x00\x00\x00\x05" "\x00\x00\x06"
                    "\x07" "2\x00" "\x00\x00\x00\x07" "\x00\x00\x00\x00\x08" "\x00\x00\x09"
              "\x00"s,
              ss.str()
             );
}

TEST(MongoUtilityObjectIdTest, BsonObject)
{
    ObjectIdInObject                data{{1,2,3}, 8, {10,12,13}, "Hi There", {32,48,64}};
    std::stringstream   ss;

    ss << bsonExporter(data, PrinterConfig{OutputType::Stream});

    using std::string_literals::operator""s;
    EXPECT_EQ(
              "\x4E\x00\x00\x00"
                    "\x07" "v1\x00" "\x00\x00\x00\x01" "\x00\x00\x00\x00\x02" "\x00\x00\x03"
                    "\x10" "v2\x00" "\x08\x00\x00\x00"
                    "\x07" "v3\x00" "\x00\x00\x00\x0a" "\x00\x00\x00\x00\x0c" "\x00\x00\x0d"
                    "\x02" "v4\x00" "\x09\x00\x00\x00" "Hi There\x00"
                    "\x07" "v5\x00" "\x00\x00\x00\x20" "\x00\x00\x00\x00\x30" "\x00\x00\x40"
              "\x00"s,
              ss.str()
             );
}


