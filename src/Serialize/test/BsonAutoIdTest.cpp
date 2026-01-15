#include "gtest/gtest.h"
#include "Traits.h"
#include "SerUtil.h"
#include "BsonThor.h"
#include "MongoUtility.h"


struct Address
{
    std::string     f1;
    std::string     f2;
};
struct Person
{
    std::string     name;
    int             age;
    Address         address;
};

struct Insert
{
    // Emulate the Mongo Insert Object.
    std::vector<Person> data;
};

ThorsAnvil_MakeTrait(Address, f1, f2);
ThorsAnvil_MakeTrait(Person, name, age, address);
ThorsAnvil_MakeTrait(Insert, data);

using ThorsAnvil::Serialize::bsonExporter;
using ThorsAnvil::Serialize::PrinterConfig;
using ThorsAnvil::Serialize::MongoUtility::ObjectID;

TEST(BsonAutoIdTest, JsonExportCustomField)
{
    using namespace std::string_literals;
 
    Insert                  people{{{"Martin", 12, {"Road", "12"}}, {"Loki", 25, {"Street", "525"}}}};
    std::stringstream       output;
    std::vector<ObjectID>   result;

    output << bsonExporter(people, PrinterConfig{}, result);
    EXPECT_EQ(2, result.size());

    std::string expected =
    "\xC3\x00\x00\x00"
        "\x04" "data\x00" "\xB8\x00\x00\x00"
            "\x03" "0\x00"
                "\x56\x00\x00\x00"
                "\x07" "_id\x00"  "\x00\x00\x00\x00" "\x00\x00\x00\x00\x00" "\x00\x00\x00"
                "\x02" "name\x00" "\x07\x00\x00\x00" "Martin\x00"
                "\x10" "age\x00"  "\x0c\x00\x00\x00"
                "\x03" "address\x00"
                    "\x1d\x00\x00\x00"
                        "\x02" "f1\x00" "\x05\x00\x00\x00" "Road\x00"
                        "\x02" "f2\x00" "\x03\x00\x00\x00" "12\x00"
                        "\x00"
                "\x00"
            "\x03" "1\x00"
                "\x57\x00\x00\x00"
                "\x07" "_id\x00"  "\x00\x00\x00\x00" "\x00\x00\x00\x00\x00" "\x00\x00\x00"
                "\x02" "name\x00" "\x05\x00\x00\x00" "Loki\x00"
                "\x10" "age\x00"  "\x19\x00\x00\x00"
                "\x03" "address\x00"
                    "\x20\x00\x00\x00"
                        "\x02" "f1\x00" "\x07\x00\x00\x00" "Street\x00"
                        "\x02" "f2\x00" "\x04\x00\x00\x00" "525\x00"
                        "\x00"
                "\x00"
            "\x00"
        "\x00"s;

    // Get the created ObjectID values.
    // Convert them into BSON.
    std::stringstream id0;
    id0 << bsonExporter(result[0]); // Note: Creates an Array with one value. So ObjectID starts at 7th character.
    std::stringstream id1;
    id1 << bsonExporter(result[1]);

    EXPECT_EQ(20, id0.str().size());    // Array with one element ObjectID
    EXPECT_EQ(20, id1.str().size());


    // Copy generated ID into the expected string.
    for (int loop = 0; loop < 12; ++loop) {
        expected[26 + loop] = id0.str()[7 + loop];
        expected[115 + loop] = id1.str()[7 + loop];
    }

    EXPECT_EQ(
        expected,
        output.str()
    );
}

