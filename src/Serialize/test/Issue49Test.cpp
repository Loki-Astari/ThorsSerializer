#include "gtest/gtest.h"
#include "test/SerializeTest.h"
#include "Serialize.h"
#include "Traits.h"
#include "JsonThor.h"
#include "SerUtil.h"
#include <memory>
#include <iostream>



using namespace ThorsAnvil::Serialize;
using namespace std;

namespace Issue49
{
    enum class FloatFormat {scientific = 1,fixed = 2,hex = 4,general = fixed | scientific};
}
ThorsAnvil_MakeEnum(Issue49::FloatFormat, scientific, fixed, hex, general);

TEST(Issue49Test, StreamScientific)
{
    std::stringstream stream;

    Issue49::FloatFormat    testData = Issue49::FloatFormat::scientific;
    stream << ThorsAnvil::Serialize::jsonExport(testData);

    std::string result = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ("\"scientific\"", result);
}
TEST(Issue49Test, StreamFixed)
{
    std::stringstream stream;

    Issue49::FloatFormat    testData = Issue49::FloatFormat::fixed;
    stream << ThorsAnvil::Serialize::jsonExport(testData);

    std::string result = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ("\"fixed\"", result);
}
TEST(Issue49Test, StreamHex)
{
    std::stringstream stream;

    Issue49::FloatFormat    testData = Issue49::FloatFormat::hex;
    stream << ThorsAnvil::Serialize::jsonExport(testData);

    std::string result = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ("\"hex\"", result);
}
TEST(Issue49Test, StreamGeneral)
{
    std::stringstream stream;

    Issue49::FloatFormat    testData = Issue49::FloatFormat::general;
    stream << ThorsAnvil::Serialize::jsonExport(testData);

    std::string result = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ("\"general\"", result);
}
TEST(Issue49Test, ImportScientific)
{
    std::string input = R"("scientific")";
    std::stringstream stream(input);

    Issue49::FloatFormat    testData = Issue49::FloatFormat::general;
    stream >> ThorsAnvil::Serialize::jsonImport(testData);

    EXPECT_EQ(Issue49::FloatFormat::scientific, testData);
}
TEST(Issue49Test, ImportFixed)
{
    std::string input = R"("fixed")";
    std::stringstream stream(input);

    Issue49::FloatFormat    testData = Issue49::FloatFormat::general;
    stream >> ThorsAnvil::Serialize::jsonImport(testData);

    EXPECT_EQ(Issue49::FloatFormat::fixed, testData);
}
TEST(Issue49Test, ImportHex)
{
    std::string input = R"("hex")";
    std::stringstream stream(input);

    Issue49::FloatFormat    testData = Issue49::FloatFormat::general;
    stream >> ThorsAnvil::Serialize::jsonImport(testData);

    EXPECT_EQ(Issue49::FloatFormat::hex, testData);
}
TEST(Issue49Test, ImportGeneral)
{
    std::string input = R"("general")";
    std::stringstream stream(input);

    Issue49::FloatFormat    testData = Issue49::FloatFormat::scientific;
    stream >> ThorsAnvil::Serialize::jsonImport(testData);

    EXPECT_EQ(Issue49::FloatFormat::general, testData);
}




