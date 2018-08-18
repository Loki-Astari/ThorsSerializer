#include "gtest/gtest.h"
#include "JsonThor.h"
#include <sstream>
#include <string>


TEST(JsonEscapeControl, NormalInput)
{
    std::stringstream   input("\"String With no special characters\"");
    std::string         value;
    bool                importDone = false;

    if (input >> ThorsAnvil::Serialize::jsonImport(value, ThorsAnvil::Serialize::ParserInterface::ParseType::Weak, true)) {
        importDone = true;
    }
    EXPECT_EQ(importDone, true);
}
TEST(JsonEscapeControl, InputContainsTab)
{
    std::stringstream   input("\"\t A string with A tab\"");
    std::string         value;
    bool                importDone = false;

    if (input >> ThorsAnvil::Serialize::jsonImport(value, ThorsAnvil::Serialize::ParserInterface::ParseType::Weak, true)) {
        importDone = true;
    }
    EXPECT_EQ(importDone, false);
}
TEST(JsonEscapeControl, InputContainsBS)
{
    std::stringstream   input("\"\b A string with A Back Space\"");
    std::string         value;
    bool                importDone = false;

    if (input >> ThorsAnvil::Serialize::jsonImport(value, ThorsAnvil::Serialize::ParserInterface::ParseType::Weak, true)) {
        importDone = true;
    }
    EXPECT_EQ(importDone, false);
}
TEST(JsonEscapeControl, InputContainsNL)
{
    std::stringstream   input("\"\n A string with A New Line\"");
    std::string         value;
    bool                importDone = false;

    if (input >> ThorsAnvil::Serialize::jsonImport(value, ThorsAnvil::Serialize::ParserInterface::ParseType::Weak, true)) {
        importDone = true;
    }
    EXPECT_EQ(importDone, false);
}
TEST(JsonEscapeControl, InputContainsFF)
{
    std::stringstream   input("\"\f A string with A Form Feed\"");
    std::string         value;
    bool                importDone = false;

    if (input >> ThorsAnvil::Serialize::jsonImport(value, ThorsAnvil::Serialize::ParserInterface::ParseType::Weak, true)) {
        importDone = true;
    }
    EXPECT_EQ(importDone, false);
}
TEST(JsonEscapeControl, InputContainsCR)
{
    std::stringstream   input("\"\r A string with A Carridge Return\"");
    std::string         value;
    bool                importDone = false;

    if (input >> ThorsAnvil::Serialize::jsonImport(value, ThorsAnvil::Serialize::ParserInterface::ParseType::Weak, true)) {
        importDone = true;
    }
    EXPECT_EQ(importDone, false);
}
TEST(JsonEscapeControl, OutputContainsTab)
{
    std::string         value("\t A string with A tab");
    std::stringstream   output;
    bool                exportDone = false;

    if (output << ThorsAnvil::Serialize::jsonExport(value, ThorsAnvil::Serialize::PrinterInterface::OutputType::Default, true)) {
        exportDone = true;
    }
    EXPECT_EQ(exportDone, true);
    EXPECT_EQ(output.str().find('\t'), std::string::npos);
    auto find = output.str().find('\\');
    ASSERT_NE(find, std::string::npos);
    EXPECT_EQ(output.str()[find+1], 't');
}
TEST(JsonEscapeControl, OutputContainsBS)
{
    std::string         value("\b A string with A Back Space");
    std::stringstream   output;
    bool                exportDone = false;

    if (output << ThorsAnvil::Serialize::jsonExport(value, ThorsAnvil::Serialize::PrinterInterface::OutputType::Default, true)) {
        exportDone = true;
    }
    EXPECT_EQ(exportDone, true);
    EXPECT_EQ(output.str().find('\t'), std::string::npos);
    auto find = output.str().find('\\');
    ASSERT_NE(find, std::string::npos);
    EXPECT_EQ(output.str()[find+1], 'b');
}
TEST(JsonEscapeControl, OutputContainsNL)
{
    std::string         value("\n A string with A New Line");
    std::stringstream   output;
    bool                exportDone = false;

    if (output << ThorsAnvil::Serialize::jsonExport(value, ThorsAnvil::Serialize::PrinterInterface::OutputType::Default, true)) {
        exportDone = true;
    }
    EXPECT_EQ(exportDone, true);
    EXPECT_EQ(output.str().find('\t'), std::string::npos);
    auto find = output.str().find('\\');
    ASSERT_NE(find, std::string::npos);
    EXPECT_EQ(output.str()[find+1], 'n');
}
TEST(JsonEscapeControl, OutputContainsFF)
{
    std::string         value("\f A string with A Form Feed");
    std::stringstream   output;
    bool                exportDone = false;

    if (output << ThorsAnvil::Serialize::jsonExport(value, ThorsAnvil::Serialize::PrinterInterface::OutputType::Default, true)) {
        exportDone = true;
    }
    EXPECT_EQ(exportDone, true);
    EXPECT_EQ(output.str().find('\t'), std::string::npos);
    auto find = output.str().find('\\');
    ASSERT_NE(find, std::string::npos);
    EXPECT_EQ(output.str()[find+1], 'f');
}
TEST(JsonEscapeControl, OutputContainsCR)
{
    std::string         value("\r A string with A Carridge Return");
    std::stringstream   output;
    bool                exportDone = false;

    if (output << ThorsAnvil::Serialize::jsonExport(value, ThorsAnvil::Serialize::PrinterInterface::OutputType::Default, true)) {
        exportDone = true;
    }
    EXPECT_EQ(exportDone, true);
    EXPECT_EQ(output.str().find('\t'), std::string::npos);
    auto find = output.str().find('\\');
    ASSERT_NE(find, std::string::npos);
    EXPECT_EQ(output.str()[find+1], 'r');
}

