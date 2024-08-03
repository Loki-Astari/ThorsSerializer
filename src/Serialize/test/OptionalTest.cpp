#include "gtest/gtest.h"
#include <optional>
#include "Traits.h"
#include "JsonThor.h"


struct OptionalTest
{
    int                 normal;
    std::optional<int>  optional;
};

ThorsAnvil_MakeTrait(OptionalTest,  normal, optional);

using  ThorsAnvil::Serialize::jsonExporter;
using  ThorsAnvil::Serialize::jsonImporter;
using  ThorsAnvil::Serialize::PrinterInterface;

TEST(OptionalTest, NormalOnly)
{
    std::stringstream stream;

    OptionalTest    data;
    data.normal = 5;

    stream << jsonExporter(data, PrinterInterface::PrinterConfig{PrinterInterface::OutputType::Stream});
    EXPECT_EQ(R"({"normal":5})", stream.str());
}
TEST(OptionalTest, NormalAndOptional)
{
    std::stringstream stream;

    OptionalTest    data;
    data.normal = 5;
    data.optional = 6;

    stream << jsonExporter(data, PrinterInterface::PrinterConfig{PrinterInterface::OutputType::Stream});
    EXPECT_EQ(R"({"normal":5,"optional":6})", stream.str());
}
TEST(OptionalTest, ImportOptional)
{
    std::stringstream stream;
    stream << R"({"normal": 5, "optional": 6})";

    OptionalTest    data;
    stream >> jsonImporter(data);

    EXPECT_EQ(5, data.normal);
    EXPECT_EQ(6, data.optional);
}
TEST(OptionalTest, ImportWithNoOptional)
{
    std::stringstream stream;
    stream << R"({"normal": 5})";

    OptionalTest    data;
    stream >> jsonImporter(data);

    EXPECT_EQ(5, data.normal);
    EXPECT_FALSE(data.optional.has_value());
}
