#include "gtest/gtest.h"
#include "Traits.h"
#include "SerUtil.h"
#include "BsonThor.h"
#include "BsonPrinter.h"
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

ThorsAnvil_MakeTrait(Address, f1, f2);
ThorsAnvil_MakeTrait(Person, name, age, address);

using ThorsAnvil::Serialize::bsonExporter;
using ThorsAnvil::Serialize::PrinterInterface;
using ThorsAnvil::Serialize::BsonPrinterConfig;
using ThorsAnvil::Serialize::MongoUtility::ObjectID;

TEST(BsonAutoIdTest, JsonExportCustomField)
{
    using namespace std::string_literals;
 
    std::vector<Person>     people{{"Martin", 12, {"Road", "12"}}, {"Loki", 25, {"Street", "525"}}};
    std::stringstream       output;
    std::vector<ObjectID>   result;

    output << bsonExporter(people, BsonPrinterConfig{PrinterInterface::PrinterConfig{}, result});
    EXPECT_EQ(2, result.size());

#if 0
    \xD6\x00\x00\x00
        \x3     0\x00
            e\x00\x00\x00
                \x07    _id\x00     \x66\x98\x09\xED    \x00\x00\x00\x41\xA7    \x00\x08\x6E
                \x02    name\x00    \x07\x00\x00\x00    Martin\x00
                \x10    age\x00     \x0C\x00\x00\x00
                \x3     address\x00
                    \x19\x00\x00\x00
                        \x07_id\x00f\x98\x09\xED\x00`\xB7\xAC\xD9\x00\x08o\x2f1\x00\x5\x00\x00\x00Road\x00\x2f2\x00\x3\x00\x00\x0012\x00\x00\x00\x31\x00f\x00\x00\x00\x07_id\x00f\x98\x09\xED\x00:\xB5\x0C*\x00\x08p\x2name\x00\x5\x00\x00\x00Loki\x00\x10age\x00\x19\x00\x00\x00\x3address\x00\x1C\x00\x00\x00\x07_id\x00f\x98\x09\xED\x00D1\xB7\x82\x00\x08q\x2f1\x00\x07\x00\x00\x00Street\x00\x2f2\x00\x4\x00\x00\x00525\x00\x00\x00\x00
----
    \xAC\x00\x00\x00                                                                                4           4
        \x03    0\x00                                                                               3           7
            \x50\x00\x00\x00                                                                        4           11      4
                \x07    _id\x00     \x66\x98\xE\x16     \x00\x00\x00\x41\xA7    \x00\x08\x6e        17          28      21
                \x02    name\x00    \x07\x00\x00\x00    Martin\x00                                  17          45      38
                \x10    age\x00     \x0c\x00\x00\x00                                                9           54      47
                \x03    address\x00                                                                 9           63      56
                    \x19\x00\x00\x00                                                                4           67      60      4
                        \x02    f1\x00  \x05\x00\x00\x00    Road\x00                                13          80      73      17
                        \x02    f2\x00  \x03\x00\x00\x00    12\x00                                  11          91      84      28
                        \x00                                                                        1           92      85      29(25) => 4
                \x00                                                                                1           93      86(80) => 6
        \x03    1\x00                                                                               3           96
            \x51\x00\x00\x00                                                                        4           100     4
                \x07    _id\x00     \x66\x98\x0E\x16    \x00\x60\xB7\xAC\xD9    \x00\x08\x6f        17          117     21
                \x02    name\x00    \x5\x00\x00\x00     Loki\x00                                    15          132     36
                \x10    age\x00     \x19\x00\x00\x00                                                9           141     45
                \x03    address\x00                                                                 9           150     54
                    \x1C\x00\x00\x00                                                                4           154     58      4
                        \x02    f1\x00  \x07\x00\x00\x00    Street\x00                              15          169     73      19
                        \x02    f2\x00  \x04\x00\x00\x00    525\x00                                 12          181     85      31
                        \x00                                                                        1           182     86      32(28) => 4
                \x00                                                                                1           183     87(81) => 6
        \x00                                                                                        1           184(172) => 12
---
    \xB8\x00\x00\x00                                                                                184 => Correct
        \x03    0\x00
            \x56\x00\x00\x00                                                                        56 => 86 Correct
                \x07    _id\x00     \x66\x98\x16\x0a    \x00\x00\x00\x41\xA7    \x00\x08\x6e
                \x02    name\x00    \x07\x00\x00\x00    Martin\x00
                \x10    age\x00     \x0c\x00\x00\x00
                \x03    address\x00
                    \x1D\x00\x00\x00                                                                1D => 29 Correct
                        \x02    f1\x00  \x05\x00\x00\x00    Road\x00
                        \x02    f2\x00  \x03\x00\x00\x00    12\x00
                        \x00
                \x00
        \x03    1\x00
            \x57\x00\x00\x00                                                                        57 => 87 Correct
                x07     _id\x00     \x66\x98\x16\x0a    \x00\x60\xB7\xAC\xD9    \x00\x08\x6f
                \x02    name\x00    \x05\x00\x00\x00    Loki\x00
                \x10    age\x00     \x19\x00\x00\x00
                \x03    address\x00
                    \x20\x00\x00\x00                                                                20 => 32 Correct
                        \x02    f1\x00  \x07\x00\x00\x00    Street\x00
                        \x02    f2\x00  \x04\x00\x00\x00    525\x00
                        \x00
                \x00
        \x00
#endif

    std::string expected = "\xB8\x00\x00\x00"
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
        expected[16 + loop] = id0.str()[7 + loop];
        expected[105 + loop] = id1.str()[7 + loop];
    }

    EXPECT_EQ(
        expected,
        output.str()
    );
}

