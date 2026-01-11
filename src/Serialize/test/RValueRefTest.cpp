#include <gtest/gtest.h>
#include "PrinterConfig.h"
#include "Traits.h"
#include "JsonThor.h"

struct Simple
{
    std::string  data = "point";
};
ThorsAnvil_MakeTrait(Simple, data);

TEST(RValueRefTest, SerializeLValueRef)
{
    std::stringstream stream;

    Simple  data{"break"};
    stream << ThorsAnvil::Serialize::jsonExporter(data, ThorsAnvil::Serialize::PrinterConfig{ThorsAnvil::Serialize::OutputType::Stream});

    EXPECT_EQ(R"({"data":"break"})", stream.str());
}
TEST(RValueRefTest, SerializeRValueRef)
{
    std::stringstream stream;

    stream << ThorsAnvil::Serialize::jsonExporter(Simple{"break"}, ThorsAnvil::Serialize::PrinterConfig{ThorsAnvil::Serialize::OutputType::Stream});

    EXPECT_EQ(R"({"data":"break"})", stream.str());
}
