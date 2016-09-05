
#include "gtest/gtest.h"
#include "test/SerializeTest.h"
#include "Serialize.h"
#include "Serialize.tpp"
#include "SerUtil.h"
#include "Traits.h"
#include "JsonThor.h"
#include <string>
#include <sstream>

template<typename T>
struct TemplateType
{
    std::vector<T>   templateMember;
};

ThorsAnvil_Template_MakeTrait(1, TemplateType, templateMember); 

TEST(TemplateTypeTest, serializeTypeTest)
{
    std::string         inputStr(R"({"templateMember":[1,2,3,4]})");
    std::stringstream   input(inputStr);
    std::stringstream   output;
    TemplateType<int>   data;

    input  >> ThorsAnvil::Serialize::jsonImport(data);
    output << ThorsAnvil::Serialize::jsonExport(data, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream);

    EXPECT_EQ(output.str(), inputStr);
}

