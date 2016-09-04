
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

#undef  THOR_TEMPLATE_PARAM
#define THOR_TEMPLATE_PARAM T,
ThorsAnvil_MakeTrait(TemplateType, templateMember); 
#undef  THOR_TEMPLATE_PARAM
#if 0
//#define ThorsAnvil_MakeTrait(...)
//ThorsAnvil_MakeTrait_Base( , Map, TemplateType, templateMember, 1)
//#define ThorsAnvil_MakeTrait_Base(Parent, TType, DataType, ...)
namespace ThorsAnvil { namespace Serialize {
template<typename T>
class Traits<TemplateType<T>>
{
    public:
        static constexpr TraitType type = TraitType::Map;

        using Members = std::tuple<
                        std::pair<char const*, decltype(&TemplateType<T>::templateMember)>
                                    >;

        static Members const& getMembers()
        {
            static constexpr Members members{
                        { "templateMember", &TemplateType<T>::templateMember }
                                            };
            return members;
        }
};
}}
#endif


#if 0
#define THOR_TEMPLATE_PARAM int,
Test 1 (int)
BuildTemplateTypeParamExp
BuildTemplateTypeValueExp
#undef  THOR_TEMPLATE_PARAM
#define  THOR_TEMPLATE_PARAM int, float,
Test 2 (int, float)
BuildTemplateTypeParamExp
BuildTemplateTypeValueExp
#undef  THOR_TEMPLATE_PARAM
#define  THOR_TEMPLATE_PARAM
Test 3 ()
BuildTemplateTypeParamExp
BuildTemplateTypeValueExp
#undef  THOR_TEMPLATE_PARAM
#endif

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

