#include "gtest/gtest.h"

#include "Traits.h"
#include "BsonThor.h"

#include <optional>
#include <string>

using ThorsAnvil::Serialize::bsonExporter;
using namespace std::string_literals;

struct WriteConcern
{
    std::optional<int>  w;
    bool                j   = false;
};

ThorsAnvil_MakeTrait(WriteConcern,              w, j);


TEST(Issue87Test, FieldJOnly)
{
    WriteConcern        a;
    std::stringstream   output;
    output << bsonExporter(a);

    EXPECT_EQ(  "\x09\x00\x00\x00"
                "\x08" "j\x00" "\x00"
                "\x00"s,
                output.str());
}

TEST(Issue87Test, FieldJAndW)
{
    WriteConcern        a;
    a.w = 7;
    std::stringstream   output;
    output << bsonExporter(a);

    EXPECT_EQ(  "\x10\x00\x00\x00"
                "\x10" "w\x00" "\x07\x00\x00\x00"
                "\x08" "j\x00" "\x00"
                "\x00"s,
                output.str());
}

