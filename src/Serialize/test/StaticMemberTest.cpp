#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "test/SerializeTest.h"
#include "Serialize.h"
#include "Serialize.tpp"
#include "Traits.h"
#include "JsonThor.h"
#include <string>
#include <sstream>

namespace StaticMemberTest
{

struct StaticMember
{
    static int staticMember;
           int normalMember;
};

int StaticMember::staticMember = 8;
}

ThorsAnvil_MakeTrait(StaticMemberTest::StaticMember, normalMember, staticMember); 

TEST(StaticMemberTest, serializeStaticMember)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    std::string         inputStr(R"({"normalMember":7,"staticMember":14})");
    std::stringstream   input(inputStr);
    std::stringstream   output;
    StaticMemberTest::StaticMember        data;

    input  >> ThorsAnvil::Serialize::jsonImporter(data, false);
    output << ThorsAnvil::Serialize::jsonExporter(data, PrinterInterface::OutputType::Stream);

    EXPECT_EQ(output.str(), inputStr);
}

