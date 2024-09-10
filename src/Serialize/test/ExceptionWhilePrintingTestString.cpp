#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include <sstream>
#include "test/ExceptionTest.h"


TEST(ExceptionWhilePrintingTestString, JsonNormalPrint)
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
    EXPECT_EQ(stream.str(), "15");
}


TEST(ExceptionWhilePrintingTestString, JsonNormalPrintCatchEnabled)
{
    using ThorsAnvil::Serialize::OutputType;
    std::stringstream   stream;
    ExceptionTest::ThrowablePrint      obj(false, 16);
    bool                thrown = false;

    try
    {
        stream << ThorsAnvil::Serialize::jsonExporter(obj, OutputType::Default);
    }
    catch(...)
    {
        thrown  = true;
    }

    std::ios_base::iostate state = stream.rdstate();
    EXPECT_EQ(thrown, false);
    EXPECT_EQ(state, std::ios::goodbit);
    EXPECT_EQ(stream.str(), "16");
}

TEST(ExceptionWhilePrintingTestString, JsonThrowPrint)
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


TEST(ExceptionWhilePrintingTestString, JsonThrowPrintCatchEnabled)
{
    using ThorsAnvil::Serialize::OutputType;
    std::stringstream   stream;
    ExceptionTest::ThrowablePrint      obj(true, 18);
    bool                thrown = false;

    try
    {
        stream << ThorsAnvil::Serialize::jsonExporter(obj, OutputType::Default);
    }
    catch(...)
    {
        thrown  = true;
    }

    std::ios_base::iostate state = stream.rdstate();
    EXPECT_EQ(thrown, false);
    EXPECT_EQ(state, std::ios::failbit);
}


TEST(ExceptionWhilePrintingTestString, JsonNormalStream)
{
    std::string         stream(R"(19 "Data")");
    ExceptionTest::ThrowablePrint      obj(false,1);
    bool                thrown = false;
    bool                ok;

    try
    {
        ok = (stream >> ThorsAnvil::Serialize::jsonImporter(obj, false));
    }
    catch(...)
    {
        thrown  = true;
    }

    EXPECT_EQ(thrown, false);
    EXPECT_TRUE(ok);
    EXPECT_EQ(obj.val, 19);
}


TEST(ExceptionWhilePrintingTestString, JsonNormalStreamCatchEnabled)
{
    using ThorsAnvil::Serialize::ParseType;
    std::string         stream(R"(20 "Data")");
    ExceptionTest::ThrowablePrint      obj(false, 2);
    bool                thrown = false;
    bool                ok;

    try
    {
        ok = (stream >> ThorsAnvil::Serialize::jsonImporter(obj, ParseType::Weak));
    }
    catch(...)
    {
        thrown  = true;
    }

    EXPECT_EQ(thrown, false);
    EXPECT_TRUE(ok);
    EXPECT_EQ(obj.val, 20);
}

TEST(ExceptionWhilePrintingTestString, JsonThrowStream)
{
    std::string         stream("21");
    ExceptionTest::ThrowablePrint      obj(true, 3);
    bool                thrown = false;
    bool                ok;

    try
    {
        ok = (stream >> ThorsAnvil::Serialize::jsonImporter(obj, false));
    }
    catch(...)
    {
        thrown  = true;
    }

    EXPECT_EQ(thrown, true);
    EXPECT_FALSE(ok);
}


TEST(ExceptionWhilePrintingTestString, JsonThrowStreamCatchEnabled)
{
    using ThorsAnvil::Serialize::ParseType;
    std::string         stream("22");
    ExceptionTest::ThrowablePrint      obj(true, 4);
    bool                thrown = false;
    bool                ok;

    try
    {
        ok = (stream >> ThorsAnvil::Serialize::jsonImporter(obj, ParseType::Weak));
    }
    catch(...)
    {
        thrown  = true;
    }

    EXPECT_EQ(thrown, false);
    EXPECT_FALSE(ok);
}


TEST(ExceptionWhilePrintingTestString, BsonNormalPrint)
{
    std::stringstream   stream;
    ExceptionTest::ThrowablePrint      obj(false, 15);
    bool                thrown = false;

    try
    {
        stream << ThorsAnvil::Serialize::bsonExporter(obj, false);
    }
    catch(...)
    {
        thrown  = true;
    }

    std::ios_base::iostate state = stream.rdstate();
    EXPECT_EQ(thrown, false);
    EXPECT_EQ(state, std::ios::goodbit);

    static const char expectedRaw[]
                = "\x0F\x00\x00\x00"
                  "\x05"  "0\x00"  "\x02\x00\x00\x00" "\x80" "15"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(stream.str(), expected);
}


TEST(ExceptionWhilePrintingTestString, BsonNormalPrintCatchEnabled)
{
    using ThorsAnvil::Serialize::OutputType;
    std::stringstream   stream;
    ExceptionTest::ThrowablePrint      obj(false, 16);
    bool                thrown = false;

    try
    {
        stream << ThorsAnvil::Serialize::bsonExporter(obj, OutputType::Default);
    }
    catch(...)
    {
        thrown  = true;
    }

    std::ios_base::iostate state = stream.rdstate();
    EXPECT_EQ(thrown, false);
    EXPECT_EQ(state, std::ios::goodbit);
    static const char expectedRaw[]
                = "\x0F\x00\x00\x00"
                  "\x05"  "0\x00"  "\x02\x00\x00\x00" "\x80" "16"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(stream.str(), expected);
}

TEST(ExceptionWhilePrintingTestString, BsonThrowPrint)
{
    std::stringstream   stream;
    ExceptionTest::ThrowablePrint      obj(true, 17);
    bool                thrown = false;

    try
    {
        stream << ThorsAnvil::Serialize::bsonExporter(obj, false);
    }
    catch(...)
    {
        thrown  = true;
    }

    std::ios_base::iostate state = stream.rdstate();
    EXPECT_EQ(thrown, true);
    EXPECT_EQ(state, std::ios::failbit);
}


TEST(ExceptionWhilePrintingTestString, BsonThrowPrintCatchEnabled)
{
    using ThorsAnvil::Serialize::OutputType;
    std::stringstream   stream;
    ExceptionTest::ThrowablePrint      obj(true, 18);
    bool                thrown = false;

    try
    {
        stream << ThorsAnvil::Serialize::bsonExporter(obj, OutputType::Default);
    }
    catch(...)
    {
        thrown  = true;
    }

    std::ios_base::iostate state = stream.rdstate();
    EXPECT_EQ(thrown, false);
    EXPECT_EQ(state, std::ios::failbit);
}


TEST(ExceptionWhilePrintingTestString, BsonNormalStream)
{
    static const char inputRaw[]
                = "\x16\x00\x00\x00"
                  "\x05"  "0\x00"  "\x09\x00\x00\x00" "\x80" "19 \"Data\""
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::string         stream(input);
    ExceptionTest::ThrowablePrint      obj(false,1);
    bool                thrown = false;
    bool                ok;

    try
    {
        ok = (stream >> ThorsAnvil::Serialize::bsonImporter(obj, false));
    }
    catch(...)
    {
        thrown  = true;
    }

    EXPECT_EQ(thrown, false);
    EXPECT_TRUE(ok);
    EXPECT_EQ(obj.val, 19);
}


TEST(ExceptionWhilePrintingTestString, BsonNormalStreamCatchEnabled)
{
    using ThorsAnvil::Serialize::ParseType;
    static const char inputRaw[]
                = "\x16\x00\x00\x00"
                  "\x05"  "0\x00"  "\x09\x00\x00\x00" "\x80" "20 \"Done\""
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::string         stream(input);
    ExceptionTest::ThrowablePrint      obj(false, 2);
    bool                thrown = false;
    bool                ok;

    try
    {
        ok = (stream >> ThorsAnvil::Serialize::bsonImporter(obj, ParseType::Weak));
    }
    catch(...)
    {
        thrown  = true;
    }

    EXPECT_EQ(thrown, false);
    EXPECT_TRUE(ok);
    EXPECT_EQ(obj.val, 20);
}

TEST(ExceptionWhilePrintingTestString, BsonThrowStream)
{
    static const char inputRaw[]
                = "\x0F\x00\x00\x00"
                  "\x05"  "0\x00"  "\x02\x00\x00\x00" "\x80" "21"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::string         stream(input);
    ExceptionTest::ThrowablePrint      obj(true, 3);
    bool                thrown = false;
    bool                ok;

    try
    {
        ok = (stream >> ThorsAnvil::Serialize::bsonImporter(obj, false));
    }
    catch(...)
    {
        thrown  = true;
    }

    EXPECT_EQ(thrown, true);
    EXPECT_FALSE(ok);
}


TEST(ExceptionWhilePrintingTestString, BsonThrowStreamCatchEnabled)
{
    using ThorsAnvil::Serialize::ParseType;
    static const char inputRaw[]
                = "\x0F\x00\x00\x00"
                  "\x05"  "0\x00"  "\x02\x00\x00\x00" "\x80" "22"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::string         stream(input);
    ExceptionTest::ThrowablePrint      obj(true, 4);
    bool                thrown = false;
    bool                ok;

    try
    {
        ok = (stream >> ThorsAnvil::Serialize::jsonImporter(obj, ParseType::Weak));
    }
    catch(...)
    {
        thrown  = true;
    }

    EXPECT_EQ(thrown, false);
    EXPECT_FALSE(ok);
}

