#include "gtest/gtest.h"
#include "Traits.h"
#include "JsonThor.h"
#include <optional>


struct OptionalTest
{
    int                 normal;
    std::optional<int>  optional;
};

ThorsAnvil_MakeTrait(OptionalTest,  normal, optional);

using  ThorsAnvil::Serialize::jsonExporter;
using  ThorsAnvil::Serialize::jsonImporter;
using  ThorsAnvil::Serialize::OutputType;
using  ThorsAnvil::Serialize::PrinterConfig;

TEST(OptionalTestString, NormalOnly)
{
    std::string     stream;

    OptionalTest    data;
    data.normal = 5;

    stream << jsonExporter(data, PrinterConfig{OutputType::Stream});
    EXPECT_EQ(R"({"normal":5})", stream);
}
TEST(OptionalTestString, NormalAndOptional)
{
    std::string     stream;

    OptionalTest    data;
    data.normal = 5;
    data.optional = 6;

    stream << jsonExporter(data, PrinterConfig{OutputType::Stream});
    EXPECT_EQ(R"({"normal":5,"optional":6})", stream);
}
TEST(OptionalTestString, ImportOptional)
{
    std::string stream{R"({"normal": 5, "optional": 6})"};

    OptionalTest    data;
    stream >> jsonImporter(data);

    EXPECT_EQ(5, data.normal);
    EXPECT_EQ(6, data.optional);
}
TEST(OptionalTestString, ImportWithNoOptional)
{
    std::string stream{R"({"normal": 5})"};

    OptionalTest    data;
    stream >> jsonImporter(data);

    EXPECT_EQ(5, data.normal);
    EXPECT_FALSE(data.optional.has_value());
}
