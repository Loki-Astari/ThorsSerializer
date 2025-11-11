#include <string>
#include "JsonPrinter.h"
#include "JsonThor.h"
#include "PrinterConfig.h"
#include "gtest/gtest.h"


struct SizeBoolFalse
{
    bool    val1 = false;
};
struct SizeBoolTrue
{
    bool    val1 = true;
};
struct SizeNull
{
    bool*   val1 = nullptr;
};
struct SizeString
{
    std::string val1 = "12345";
};
struct SizeInt12
{
    int val1 = 12;
};
struct SizeInt0
{
    int val1 = 0;
};
struct SizeFloat12P567
{
    double val1 = 12.567;
};
struct SizeFloatZero
{
    double val1 = 0;
};
struct SizeArray
{
    std::vector<std::string>    val1 = {"123","456","789"};
};

ThorsAnvil_MakeTrait(SizeBoolFalse, val1);
ThorsAnvil_MakeTrait(SizeBoolTrue, val1);
ThorsAnvil_MakeTrait(SizeNull, val1);
ThorsAnvil_MakeTrait(SizeString, val1);
ThorsAnvil_MakeTrait(SizeInt12, val1);
ThorsAnvil_MakeTrait(SizeInt0, val1);
ThorsAnvil_MakeTrait(SizeFloat12P567, val1);
ThorsAnvil_MakeTrait(SizeFloatZero, val1);
ThorsAnvil_MakeTrait(SizeArray, val1);

TEST(SizeTest, getJsonSizeBoolFALSE)
{
    using TestType = SizeBoolFalse;

    ThorsAnvil::Serialize::JsonPrinter      printer(std::cout);
    TestType                                obj;
    std::size_t s = ThorsAnvil::Serialize::Traits<TestType>::getPrintSize(printer, obj, false);

    EXPECT_EQ(14, s);

    std::stringstream  output;
    output << ThorsAnvil::Serialize::jsonExporter(obj, ThorsAnvil::Serialize::PrinterConfig{ThorsAnvil::Serialize::OutputType::Stream});
    EXPECT_EQ(R"({"val1":false})", output.str());
}
TEST(SizeTest, getJsonSizeBoolTrue)
{
    using TestType = SizeBoolTrue;

    ThorsAnvil::Serialize::JsonPrinter      printer(std::cout);
    TestType                                obj;
    std::size_t s = ThorsAnvil::Serialize::Traits<TestType>::getPrintSize(printer, obj, false);

    // {"val1":true}
    EXPECT_EQ(13, s);

    std::stringstream  output;
    output << ThorsAnvil::Serialize::jsonExporter(obj, ThorsAnvil::Serialize::PrinterConfig{ThorsAnvil::Serialize::OutputType::Stream});
    EXPECT_EQ(R"({"val1":true})", output.str());
}
TEST(SizeTest, getJsonSizeNull)
{
    using TestType = SizeNull;

    ThorsAnvil::Serialize::JsonPrinter      printer(std::cout);
    TestType                                obj;
    std::size_t s = ThorsAnvil::Serialize::Traits<TestType>::getPrintSize(printer, obj, false);

    // {"val1":null}
    EXPECT_EQ(13, s);

    std::stringstream  output;
    output << ThorsAnvil::Serialize::jsonExporter(obj, ThorsAnvil::Serialize::PrinterConfig{ThorsAnvil::Serialize::OutputType::Stream});
    EXPECT_EQ(R"({"val1":null})", output.str());
}
TEST(SizeTest, getJsonSizeString)
{
    using TestType = SizeString;

    ThorsAnvil::Serialize::JsonPrinter      printer(std::cout);
    TestType                                obj;
    std::size_t s = ThorsAnvil::Serialize::Traits<TestType>::getPrintSize(printer, obj, false);

    // {"val1":"12345"}
    EXPECT_EQ(16, s);

    std::stringstream  output;
    output << ThorsAnvil::Serialize::jsonExporter(obj, ThorsAnvil::Serialize::PrinterConfig{ThorsAnvil::Serialize::OutputType::Stream});
    EXPECT_EQ(R"({"val1":"12345"})", output.str());
}
TEST(SizeTest, getJsonSizeInt12)
{
    using TestType = SizeInt12;

    ThorsAnvil::Serialize::JsonPrinter      printer(std::cout);
    TestType                                obj;
    std::size_t s = ThorsAnvil::Serialize::Traits<TestType>::getPrintSize(printer, obj, false);

    // {"val1":12}
    EXPECT_EQ(11, s);

    std::stringstream  output;
    output << ThorsAnvil::Serialize::jsonExporter(obj, ThorsAnvil::Serialize::PrinterConfig{ThorsAnvil::Serialize::OutputType::Stream});
    EXPECT_EQ(R"({"val1":12})", output.str());
}
TEST(SizeTest, getJsonSizeInt0)
{
    using TestType = SizeInt0;

    ThorsAnvil::Serialize::JsonPrinter      printer(std::cout);
    TestType                                obj;
    std::size_t s = ThorsAnvil::Serialize::Traits<TestType>::getPrintSize(printer, obj, false);

    // {"val1":0}
    EXPECT_EQ(10, s);

    std::stringstream  output;
    output << ThorsAnvil::Serialize::jsonExporter(obj, ThorsAnvil::Serialize::PrinterConfig{ThorsAnvil::Serialize::OutputType::Stream});
    EXPECT_EQ(R"({"val1":0})", output.str());
}
TEST(SizeTest, getJsonSizeFloat12P567)
{
    using TestType = SizeFloat12P567;

    ThorsAnvil::Serialize::JsonPrinter      printer(std::cout);
    TestType                                obj;
    std::size_t s = ThorsAnvil::Serialize::Traits<TestType>::getPrintSize(printer, obj, false);

    // {"val1":12.567}
    EXPECT_EQ(15, s);

    std::stringstream  output;
    output << ThorsAnvil::Serialize::jsonExporter(obj, ThorsAnvil::Serialize::PrinterConfig{ThorsAnvil::Serialize::OutputType::Stream});
    EXPECT_EQ(R"({"val1":12.567})", output.str());
}
TEST(SizeTest, getJsonSizeFloatZero)
{
    using TestType = SizeFloatZero;

    ThorsAnvil::Serialize::JsonPrinter      printer(std::cout);
    TestType                                obj;
    std::size_t s = ThorsAnvil::Serialize::Traits<TestType>::getPrintSize(printer, obj, false);

    // {"val1":0.0}
    EXPECT_EQ(12, s);

    std::stringstream  output;
    output << ThorsAnvil::Serialize::jsonExporter(obj, ThorsAnvil::Serialize::PrinterConfig{ThorsAnvil::Serialize::OutputType::Stream});
    EXPECT_EQ(R"({"val1":0.0})", output.str());
}
TEST(SizeTest, getJsonSizeArray)
{
    using TestType = SizeArray;

    ThorsAnvil::Serialize::JsonPrinter      printer(std::cout);
    TestType                                obj;
    std::size_t s = ThorsAnvil::Serialize::Traits<TestType>::getPrintSize(printer, obj, false);

    // {"val1":["123","345","678"]}
    EXPECT_EQ(28, s);

    std::stringstream  output;
    output << ThorsAnvil::Serialize::jsonExporter(obj, ThorsAnvil::Serialize::PrinterConfig{ThorsAnvil::Serialize::OutputType::Stream});
    EXPECT_EQ(R"({"val1":["123","456","789"]})", output.str());
}
