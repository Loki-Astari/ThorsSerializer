#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include <sstream>
#include <string>
#include <string_view>


TEST(EscapeControlTestString, JsonNormalInput)
{
    using ThorsAnvil::Serialize::ParseType;
    std::string         input("\"String With no special characters\"");
    std::string         value;
    bool                importDone = false;

    if (input >> ThorsAnvil::Serialize::jsonImporter(value, ParseType::Weak)) {
        importDone = true;
    }
    EXPECT_EQ(importDone, true);
}
TEST(EscapeControlTestString, JsonInputContainsTab)
{
    using ThorsAnvil::Serialize::ParseType;
    std::string         input("\"\t A string with A tab\"");
    std::string         value;
    bool                importDone = false;

    if (input >> ThorsAnvil::Serialize::jsonImporter(value, ParseType::Weak)) {
        importDone = true;
    }
    EXPECT_EQ(importDone, false);
}
TEST(EscapeControlTestString, JsonInputContainsBS)
{
    using ThorsAnvil::Serialize::ParseType;
    std::string         input("\"\b A string with A Back Space\"");
    std::string         value;
    bool                importDone = false;

    if (input >> ThorsAnvil::Serialize::jsonImporter(value, ParseType::Weak)) {
        importDone = true;
    }
    EXPECT_EQ(importDone, false);
}
TEST(EscapeControlTestString, JsonInputContainsNL)
{
    using ThorsAnvil::Serialize::ParseType;
    std::string         input("\"\n A string with A New Line\"");
    std::string         value;
    bool                importDone = false;

    if (input >> ThorsAnvil::Serialize::jsonImporter(value, ParseType::Weak)) {
        importDone = true;
    }
    EXPECT_EQ(importDone, false);
}
TEST(EscapeControlTestString, JsonInputContainsFF)
{
    using ThorsAnvil::Serialize::ParseType;
    std::string         input("\"\f A string with A Form Feed\"");
    std::string         value;
    bool                importDone = false;

    if (input >> ThorsAnvil::Serialize::jsonImporter(value, ParseType::Weak)) {
        importDone = true;
    }
    EXPECT_EQ(importDone, false);
}
TEST(EscapeControlTestString, JsonInputContainsCR)
{
    using ThorsAnvil::Serialize::ParseType;
    std::string         input("\"\r A string with A Carridge Return\"");
    std::string         value;
    bool                importDone = false;

    if (input >> ThorsAnvil::Serialize::jsonImporter(value, ParseType::Weak)) {
        importDone = true;
    }
    EXPECT_EQ(importDone, false);
}
TEST(EscapeControlTestString, JsonOutputContainsTab)
{
    using ThorsAnvil::Serialize::OutputType;
    std::string         value("\t A string with A tab");
    std::string         output;
    bool                exportDone = false;

    if (output << ThorsAnvil::Serialize::jsonExporter(value, OutputType::Default)) {
        exportDone = true;
    }
    EXPECT_EQ(exportDone, true);
    EXPECT_EQ(output.find('\t'), std::string::npos);
    auto find = output.find('\\');
    ASSERT_NE(find, std::string::npos);
    EXPECT_EQ(output[find+1], 't');
}
TEST(EscapeControlTestString, JsonOutputContainsBS)
{
    using ThorsAnvil::Serialize::OutputType;
    std::string         value("\b A string with A Back Space");
    std::string         output;
    bool                exportDone = false;

    if (output << ThorsAnvil::Serialize::jsonExporter(value, OutputType::Default)) {
        exportDone = true;
    }
    EXPECT_EQ(exportDone, true);
    EXPECT_EQ(output.find('\t'), std::string::npos);
    auto find = output.find('\\');
    ASSERT_NE(find, std::string::npos);
    EXPECT_EQ(output[find+1], 'b');
}
TEST(EscapeControlTestString, JsonOutputContainsNL)
{
    using ThorsAnvil::Serialize::OutputType;
    std::string         value("\n A string with A New Line");
    std::string         output;
    bool                exportDone = false;

    if (output << ThorsAnvil::Serialize::jsonExporter(value, OutputType::Default)) {
        exportDone = true;
    }
    EXPECT_EQ(exportDone, true);
    EXPECT_EQ(output.find('\t'), std::string::npos);
    auto find = output.find('\\');
    ASSERT_NE(find, std::string::npos);
    EXPECT_EQ(output[find+1], 'n');
}
TEST(EscapeControlTestString, JsonOutputContainsFF)
{
    using ThorsAnvil::Serialize::OutputType;
    std::string         value("\f A string with A Form Feed");
    std::string         output;
    bool                exportDone = false;

    if (output << ThorsAnvil::Serialize::jsonExporter(value, OutputType::Default)) {
        exportDone = true;
    }
    EXPECT_EQ(exportDone, true);
    EXPECT_EQ(output.find('\t'), std::string::npos);
    auto find = output.find('\\');
    ASSERT_NE(find, std::string::npos);
    EXPECT_EQ(output[find+1], 'f');
}
TEST(EscapeControlTestString, JsonOutputContainsCR)
{
    using ThorsAnvil::Serialize::OutputType;
    std::string         value("\r A string with A Carridge Return");
    std::string         output;
    bool                exportDone = false;

    if (output << ThorsAnvil::Serialize::jsonExporter(value, OutputType::Default)) {
        exportDone = true;
    }
    EXPECT_EQ(exportDone, true);
    EXPECT_EQ(output.find('\t'), std::string::npos);
    auto find = output.find('\\');
    ASSERT_NE(find, std::string::npos);
    EXPECT_EQ(output[find+1], 'r');
}

TEST(EscapeControlTestString, BsonNormalInput)
{
    using ThorsAnvil::Serialize::ParseType;
    //NOTE INPUT ("\"String With no special characters\"");
    static const char inputRaw[]
                = "\x2E\x00\x00\x00"
                  "\x02" "0\x00" "\x22\x00\x00\x00" "String With no special characters\x00"
                  "\x00";
    std::string inputString(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::string         input(inputString);
    std::string         value;
    bool                importDone = false;

    if (input >> ThorsAnvil::Serialize::bsonImporter(value, ParseType::Weak)) {
        importDone = true;
    }
    EXPECT_EQ(importDone, true);
}
TEST(EscapeControlTestString, BsonOutputContainsTab)
{
    using ThorsAnvil::Serialize::OutputType;
    std::string         value("\t A string with A tab");
    std::string         output;
    bool                exportDone = false;

    if (output << ThorsAnvil::Serialize::bsonExporter(value, OutputType::Default)) {
        exportDone = true;
    }
    EXPECT_EQ(exportDone, true);

    std::string outputString(output);
    std::string_view outputView((&*outputString.begin()) + 11 , std::size(value));
    EXPECT_EQ(outputView.find('\t'), std::string::npos);
    auto find = outputView.find('\\');
    ASSERT_NE(find, std::string::npos);
    EXPECT_EQ(outputView[find+1], 't');
}
TEST(EscapeControlTestString, BsonOutputContainsBS)
{
    using ThorsAnvil::Serialize::OutputType;
    std::string         value("\b A string with A Back Space");
    std::string         output;
    bool                exportDone = false;

    if (output << ThorsAnvil::Serialize::bsonExporter(value, OutputType::Default)) {
        exportDone = true;
    }
    EXPECT_EQ(exportDone, true);

    std::string outputString(output);
    std::string_view outputView((&*outputString.begin()) + 11 , std::size(value));
    EXPECT_EQ(outputView.find('\t'), std::string::npos);
    auto find = outputView.find('\\');
    ASSERT_NE(find, std::string::npos);
    EXPECT_EQ(outputView[find+1], 'b');
}
TEST(EscapeControlTestString, BsonOutputContainsNL)
{
    using ThorsAnvil::Serialize::OutputType;
    std::string         value("\n A string with A New Line");
    std::string         output;
    bool                exportDone = false;

    if (output << ThorsAnvil::Serialize::bsonExporter(value, OutputType::Default)) {
        exportDone = true;
    }
    EXPECT_EQ(exportDone, true);

    std::string outputString(output);
    std::string_view outputView((&*outputString.begin()) + 11 , std::size(value));
    EXPECT_EQ(outputView.find('\t'), std::string::npos);
    auto find = outputView.find('\\');
    ASSERT_NE(find, std::string::npos);
    EXPECT_EQ(outputView[find+1], 'n');
}
TEST(EscapeControlTestString, BsonOutputContainsFF)
{
    using ThorsAnvil::Serialize::OutputType;
    std::string         value("\f A string with A Form Feed");
    std::string         output;
    bool                exportDone = false;

    if (output << ThorsAnvil::Serialize::bsonExporter(value, OutputType::Default)) {
        exportDone = true;
    }
    EXPECT_EQ(exportDone, true);

    std::string outputString(output);
    std::string_view outputView((&*outputString.begin()) + 11 , std::size(value));
    EXPECT_EQ(outputView.find('\t'), std::string::npos);
    auto find = outputView.find('\\');
    ASSERT_NE(find, std::string::npos);
    EXPECT_EQ(outputView[find+1], 'f');
}
TEST(EscapeControlTestString, BsonOutputContainsCR)
{
    using ThorsAnvil::Serialize::OutputType;
    std::string         value("\r A string with A Carridge Return");
    std::string         output;
    bool                exportDone = false;

    if (output << ThorsAnvil::Serialize::bsonExporter(value, OutputType::Default)) {
        exportDone = true;
    }
    EXPECT_EQ(exportDone, true);

    std::string outputString(output);
    std::string_view outputView((&*outputString.begin()) + 11 , std::size(value));
    EXPECT_EQ(outputView.find('\t'), std::string::npos);
    auto find = outputView.find('\\');
    ASSERT_NE(find, std::string::npos);
    EXPECT_EQ(outputView[find+1], 'r');
}


