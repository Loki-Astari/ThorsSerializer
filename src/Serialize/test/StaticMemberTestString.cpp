#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "test/SerializeTest.h"
#include "Serialize.h"
#include "Serialize.tpp"
#include "Traits.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include <string>
#include <sstream>

using namespace std::string_literals;

namespace StaticMemberTest
{

struct StaticMember
{
    static int staticMember;
           int normalMember;
};

}

ThorsAnvil_MakeTrait(StaticMemberTest::StaticMember, normalMember, staticMember); 

TEST(StaticMemberTestString, JsonserializeStaticMember)
{
    using ThorsAnvil::Serialize::OutputType;
    std::string         input(R"({"normalMember":7,"staticMember":14})");
    std::stringstream   output;
    StaticMemberTest::StaticMember        data;

    input  >> ThorsAnvil::Serialize::jsonImporter(data, false);
    output << ThorsAnvil::Serialize::jsonExporter(data, OutputType::Stream);

    EXPECT_EQ(output.str(), input);
}

TEST(StaticMemberTestString, BsonserializeStaticMember)
{
    using ThorsAnvil::Serialize::OutputType;
    //NOTE INPUT (R"({"normalMember":7,"staticMember":14})");
    std::string           input("\x29\x00\x00\x00"
                              "\x10" "normalMember\x00" "\x07\x00\x00\x00"
                              "\x10" "staticMember\x00" "\x0E\x00\x00\x00"
                              "\x00"s);
    std::stringstream   output;
    StaticMemberTest::StaticMember        data;

    input  >> ThorsAnvil::Serialize::bsonImporter(data, false);
    output << ThorsAnvil::Serialize::bsonExporter(data, OutputType::Stream);

    EXPECT_EQ(output.str(), input);
}

