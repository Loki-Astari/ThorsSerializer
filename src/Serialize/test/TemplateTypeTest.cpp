
#include "gtest/gtest.h"
#include "test/SerializeTest.h"
#include "Serialize.h"
#include "Serialize.tpp"
#include "SerUtil.h"
#include "Traits.h"
#include "JsonThor.h"
#include <string>
#include <sstream>

namespace TemplateTypeTest
{

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

}


ThorsAnvil_Template_MakeTrait(1, TemplateTypeTest::TemplateType, templateMember); 
ThorsAnvil_ExpandTrait(TemplateTypeTest::TemplateType<int>, TemplateTypeTest::NormalInheritFromTemplate, normalName);
ThorsAnvil_Template_ExpandTrait(1, TemplateTypeTest::TemplateType<T1>, TemplateTypeTest::TemplateInheritFromTemplate, alternative);

TEST(TemplateTypeTest, templateTest)
{
    std::string         inputStr(R"({"templateMember":[1,2,3,4]})");
    std::stringstream   input(inputStr);
    std::stringstream   output;
    TemplateTypeTest::TemplateType<int>   data;

    input  >> ThorsAnvil::Serialize::jsonImport(data);
    output << ThorsAnvil::Serialize::jsonExport(data, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream);

    EXPECT_EQ(output.str(), inputStr);
}

TEST(TemplateTypeTest, normalInheritingFromtemplateTest)
{
    std::string         inputStr(R"({"templateMember":[1,2,3,4],"normalName":"A name"})");
    std::stringstream   input(inputStr);
    std::stringstream   output;
    TemplateTypeTest::NormalInheritFromTemplate   data;

    input  >> ThorsAnvil::Serialize::jsonImport(data);
    output << ThorsAnvil::Serialize::jsonExport(data, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream);

    EXPECT_EQ(output.str(), inputStr);
}

TEST(TemplateTypeTest, templateInheritingFromtemplateTest)
{
    std::string         inputStr(R"({"templateMember":[1,2,3,4],"alternative":[5,6,7,8]})");
    std::stringstream   input(inputStr);
    std::stringstream   output;
    TemplateTypeTest::TemplateInheritFromTemplate<int>   data;

    input  >> ThorsAnvil::Serialize::jsonImport(data);
    output << ThorsAnvil::Serialize::jsonExport(data, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream);

    EXPECT_EQ(output.str(), inputStr);
}

