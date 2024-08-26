#include <gtest/gtest.h>
#include "Traits.h"
#include "JsonThor.h"

class AbstractTask
{
    public:
        virtual ~AbstractTask() = default;
        virtual int check() = 0;

        ThorsAnvil_PolyMorphicSerializer(AbstractTask);
};

ThorsAnvil_MakeTrait(AbstractTask);

// No actual tests.
// This fails to compiler in old versions.
//
//  This function:
//      static T*   alloc()         {return new T;}
//
//  Is not vlaid as the T (Abstract) is an abstract class and we can not call new on it.


class Sorting: public AbstractTask
{
    public:
        virtual int check() override {return 1;}
        ThorsAnvil_PolyMorphicSerializerWithOverride(Sorting);
};

ThorsAnvil_ExpandTrait(AbstractTask, Sorting);

TEST(Issue91Test, TestOfDerived)
{
    Sorting     sort;
    std::stringstream   str;
    str << ThorsAnvil::Serialize::jsonExporter(sort, ThorsAnvil::Serialize::PrinterConfig{}.setOutputType(ThorsAnvil::Serialize::OutputType::Stream));

    EXPECT_EQ("{}", str.str());
}
TEST(Issue91Test, TestOfDerivedPtr)
{
    std::unique_ptr<AbstractTask>     sort  = std::make_unique<Sorting>();
    std::stringstream   str;
    str << ThorsAnvil::Serialize::jsonExporter(sort, ThorsAnvil::Serialize::PrinterConfig{}.setOutputType(ThorsAnvil::Serialize::OutputType::Stream));

    EXPECT_EQ(R"({"__type":"Sorting"})", str.str());
}
