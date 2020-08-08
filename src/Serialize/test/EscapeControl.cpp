#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonThor.h"
#include <sstream>
#include <string>


TEST(JsonEscapeControl, NormalInput)
{
    using ThorsAnvil::Serialize::ParserInterface;
    std::stringstream   input("\"String With no special characters\"");
    std::string         value;
    bool                importDone = false;

    if (input >> ThorsAnvil::Serialize::jsonImporter(value, ParserInterface::ParseType::Weak)) {
        importDone = true;
    }
    EXPECT_EQ(importDone, true);
}
TEST(JsonEscapeControl, InputContainsTab)
{
    using ThorsAnvil::Serialize::ParserInterface;
    std::stringstream   input("\"\t A string with A tab\"");
    std::string         value;
    bool                importDone = false;

    if (input >> ThorsAnvil::Serialize::jsonImporter(value, ParserInterface::ParseType::Weak)) {
        importDone = true;
    }
    EXPECT_EQ(importDone, false);
}
TEST(JsonEscapeControl, InputContainsBS)
{
    using ThorsAnvil::Serialize::ParserInterface;
    std::stringstream   input("\"\b A string with A Back Space\"");
    std::string         value;
    bool                importDone = false;

    if (input >> ThorsAnvil::Serialize::jsonImporter(value, ParserInterface::ParseType::Weak)) {
        importDone = true;
    }
    EXPECT_EQ(importDone, false);
}
TEST(JsonEscapeControl, InputContainsNL)
{
    using ThorsAnvil::Serialize::ParserInterface;
    std::stringstream   input("\"\n A string with A New Line\"");
    std::string         value;
    bool                importDone = false;

    if (input >> ThorsAnvil::Serialize::jsonImporter(value, ParserInterface::ParseType::Weak)) {
        importDone = true;
    }
    EXPECT_EQ(importDone, false);
}
TEST(JsonEscapeControl, InputContainsFF)
{
    using ThorsAnvil::Serialize::ParserInterface;
    std::stringstream   input("\"\f A string with A Form Feed\"");
    std::string         value;
    bool                importDone = false;

    if (input >> ThorsAnvil::Serialize::jsonImporter(value, ParserInterface::ParseType::Weak)) {
        importDone = true;
    }
    EXPECT_EQ(importDone, false);
}
TEST(JsonEscapeControl, InputContainsCR)
{
    using ThorsAnvil::Serialize::ParserInterface;
    std::stringstream   input("\"\r A string with A Carridge Return\"");
    std::string         value;
    bool                importDone = false;

    if (input >> ThorsAnvil::Serialize::jsonImporter(value, ParserInterface::ParseType::Weak)) {
        importDone = true;
    }
    EXPECT_EQ(importDone, false);
}
TEST(JsonEscapeControl, OutputContainsTab)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    std::string         value("\t A string with A tab");
    std::stringstream   output;
    bool                exportDone = false;

    if (output << ThorsAnvil::Serialize::jsonExporter(value, PrinterInterface::OutputType::Default)) {
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
    using ThorsAnvil::Serialize::PrinterInterface;
    std::string         value("\b A string with A Back Space");
    std::stringstream   output;
    bool                exportDone = false;

    if (output << ThorsAnvil::Serialize::jsonExporter(value, PrinterInterface::OutputType::Default)) {
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
    using ThorsAnvil::Serialize::PrinterInterface;
    std::string         value("\n A string with A New Line");
    std::stringstream   output;
    bool                exportDone = false;

    if (output << ThorsAnvil::Serialize::jsonExporter(value, PrinterInterface::OutputType::Default)) {
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
    using ThorsAnvil::Serialize::PrinterInterface;
    std::string         value("\f A string with A Form Feed");
    std::stringstream   output;
    bool                exportDone = false;

    if (output << ThorsAnvil::Serialize::jsonExporter(value, PrinterInterface::OutputType::Default)) {
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
    using ThorsAnvil::Serialize::PrinterInterface;
    std::string         value("\r A string with A Carridge Return");
    std::stringstream   output;
    bool                exportDone = false;

    if (output << ThorsAnvil::Serialize::jsonExporter(value, PrinterInterface::OutputType::Default)) {
        exportDone = true;
    }
    EXPECT_EQ(exportDone, true);
    EXPECT_EQ(output.str().find('\t'), std::string::npos);
    auto find = output.str().find('\\');
    ASSERT_NE(find, std::string::npos);
    EXPECT_EQ(output.str()[find+1], 'r');
}

