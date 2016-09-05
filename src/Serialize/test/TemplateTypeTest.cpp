
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

struct NormalInheritFromTemplate: public TemplateType<int>
{
    std::string      normalName;
};

template<typename T>
struct TemplateInheritFromTemplate: public TemplateType<T>
{
    std::vector<T>   alternative;
};


ThorsAnvil_Template_MakeTrait(1, TemplateType, templateMember); 
ThorsAnvil_ExpandTrait(TemplateType<int>, NormalInheritFromTemplate, normalName);
ThorsAnvil_Template_ExpandTrait(1, TemplateType<T1>, TemplateInheritFromTemplate, alternative);

TEST(TemplateTypeTest, templateTest)
{
    std::string         inputStr(R"({"templateMember":[1,2,3,4]})");
    std::stringstream   input(inputStr);
    std::stringstream   output;
    TemplateType<int>   data;

    input  >> ThorsAnvil::Serialize::jsonImport(data);
    output << ThorsAnvil::Serialize::jsonExport(data, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream);

    EXPECT_EQ(output.str(), inputStr);
}

TEST(TemplateTypeTest, normalInheritingFromtemplateTest)
{
    std::string         inputStr(R"({"templateMember":[1,2,3,4],"normalName":"A name"})");
    std::stringstream   input(inputStr);
    std::stringstream   output;
    NormalInheritFromTemplate   data;

    input  >> ThorsAnvil::Serialize::jsonImport(data);
    output << ThorsAnvil::Serialize::jsonExport(data, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream);

    EXPECT_EQ(output.str(), inputStr);
}

TEST(TemplateTypeTest, templateInheritingFromtemplateTest)
{
    std::string         inputStr(R"({"templateMember":[1,2,3,4],"alternative":[5,6,7,8]})");
    std::stringstream   input(inputStr);
    std::stringstream   output;
    TemplateInheritFromTemplate<int>   data;

    input  >> ThorsAnvil::Serialize::jsonImport(data);
    output << ThorsAnvil::Serialize::jsonExport(data, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream);

    EXPECT_EQ(output.str(), inputStr);
}

