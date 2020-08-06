#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonThor.h"
#include <sstream>
#include "test/ExceptionTest.h"


TEST(ExceptionWhilePrintingTest, NormalPrint)
{
    std::stringstream   stream;
    ExceptionTest::ThrowablePrint      obj(false, 15);
    bool                thrown = false;

    try
    {
        stream << ThorsAnvil::Serialize::jsonExporter(obj, false);
    }
    catch(...)
    {
        thrown  = true;
    }

    std::ios_base::iostate state = stream.rdstate();
    EXPECT_EQ(thrown, false);
    EXPECT_EQ(state, std::ios::goodbit);
    EXPECT_EQ(stream.str(), " 15");
}


TEST(ExceptionWhilePrintingTest, NormalPrintCatchEnabled)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    std::stringstream   stream;
    ExceptionTest::ThrowablePrint      obj(false, 16);
    bool                thrown = false;

    try
    {
        stream << ThorsAnvil::Serialize::jsonExporter(obj, PrinterInterface::OutputType::Default);
    }
    catch(...)
    {
        thrown  = true;
    }

    std::ios_base::iostate state = stream.rdstate();
    EXPECT_EQ(thrown, false);
    EXPECT_EQ(state, std::ios::goodbit);
    EXPECT_EQ(stream.str(), " 16");
}

TEST(ExceptionWhilePrintingTest, ThrowPrint)
{
    std::stringstream   stream;
    ExceptionTest::ThrowablePrint      obj(true, 17);
    bool                thrown = false;

    try
    {
        stream << ThorsAnvil::Serialize::jsonExporter(obj, false);
    }
    catch(...)
    {
        thrown  = true;
    }

    std::ios_base::iostate state = stream.rdstate();
    EXPECT_EQ(thrown, true);
    EXPECT_EQ(state, std::ios::failbit);
}


TEST(ExceptionWhilePrintingTest, ThrowPrintCatchEnabled)
{
    using ThorsAnvil::Serialize::PrinterInterface;
    std::stringstream   stream;
    ExceptionTest::ThrowablePrint      obj(true, 18);
    bool                thrown = false;

    try
    {
        stream << ThorsAnvil::Serialize::jsonExporter(obj, PrinterInterface::OutputType::Default);
    }
    catch(...)
    {
        thrown  = true;
    }

    std::ios_base::iostate state = stream.rdstate();
    EXPECT_EQ(thrown, false);
    EXPECT_EQ(state, std::ios::failbit);
}


TEST(ExceptionWhilePrintingTest, NormalStream)
{
    std::stringstream   stream(R"(19 "Data")");
    ExceptionTest::ThrowablePrint      obj(false,1);
    bool                thrown = false;

    try
    {
        stream >> ThorsAnvil::Serialize::jsonImporter(obj, false);
    }
    catch(...)
    {
        thrown  = true;
    }

    std::ios_base::iostate state = stream.rdstate();
    EXPECT_EQ(thrown, false);
    EXPECT_EQ(state, std::ios::goodbit);
    EXPECT_EQ(obj.val, 19);
}


TEST(ExceptionWhilePrintingTest, NormalStreamCatchEnabled)
{
    using ThorsAnvil::Serialize::ParserInterface;
    std::stringstream   stream(R"(20 "Data")");
    ExceptionTest::ThrowablePrint      obj(false, 2);
    bool                thrown = false;

    try
    {
        stream >> ThorsAnvil::Serialize::jsonImporter(obj, ParserInterface::ParseType::Weak);
    }
    catch(...)
    {
        thrown  = true;
    }

    std::ios_base::iostate state = stream.rdstate();
    EXPECT_EQ(thrown, false);
    EXPECT_EQ(state, std::ios::goodbit);
    EXPECT_EQ(obj.val, 20);
}

TEST(ExceptionWhilePrintingTest, ThrowStream)
{
    std::stringstream   stream("21");
    ExceptionTest::ThrowablePrint      obj(true, 3);
    bool                thrown = false;

    try
    {
        stream >> ThorsAnvil::Serialize::jsonImporter(obj, false);
    }
    catch(...)
    {
        thrown  = true;
    }

    std::ios_base::iostate state = stream.rdstate();
    EXPECT_EQ(thrown, true);
    EXPECT_EQ(state, std::ios::eofbit | std::ios::failbit);
}


TEST(ExceptionWhilePrintingTest, ThrowStreamCatchEnabled)
{
    using ThorsAnvil::Serialize::ParserInterface;
    std::stringstream   stream("22");
    ExceptionTest::ThrowablePrint      obj(true, 4);
    bool                thrown = false;

    try
    {
        stream >> ThorsAnvil::Serialize::jsonImporter(obj, ParserInterface::ParseType::Weak);
    }
    catch(...)
    {
        thrown  = true;
    }

    std::ios_base::iostate state = stream.rdstate();
    EXPECT_EQ(thrown, false);
    EXPECT_EQ(state, std::ios::eofbit | std::ios::failbit);
}

