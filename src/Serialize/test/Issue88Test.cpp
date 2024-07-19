#include "gtest/gtest.h"

#include "Traits.h"
#include "BsonThor.h"
#include "JsonThor.h"

#include <string>

using ThorsAnvil::Serialize::bsonExporter;
using ThorsAnvil::Serialize::jsonExporter;
using ThorsAnvil::Serialize::PrinterInterface;
using namespace std::string_literals;

struct ViewData
{
    std::string_view    house;
};

ThorsAnvil_MakeTrait(ViewData,              house);


TEST(Issue88Test, SerializeStringViewToJSON)
{
    std::string         house = "Madlabo";
    ViewData            view{{house}};
    std::stringstream   output;
    output << jsonExporter(view,{PrinterInterface::OutputType::Stream});

    EXPECT_EQ(  R"({"house":"Madlabo"})"s,
                output.str());
}
TEST(Issue88Test, SerializeStringViewToBSON)
{
    std::string         house = "Madlabo";
    ViewData            view{{house}};
    std::stringstream   output;
    output << bsonExporter(view);

    EXPECT_EQ(  "\x18\x00\x00\x00"
                "\x02" "house\x00" "\x08\x00\x00\x00" "Madlabo\x00"
                "\x00"s,
                output.str());
}

