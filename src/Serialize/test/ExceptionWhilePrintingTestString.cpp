#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonThor.h"
#include "BsonThor.h"
#include <sstream>
#include "test/ExceptionTest.h"


TEST(ExceptionWhilePrintingTestString, JsonNormalPrint)
{
    std::string         stream;
    ExceptionTest::ThrowablePrint      obj(false, 15);
    bool                thrown = false;
    bool                ok;

    try
    {
        ok = (stream << ThorsAnvil::Serialize::jsonExporter(obj, false));
    }
    catch(...)
    {
        thrown  = true;
    }

    EXPECT_EQ(thrown, false);
    EXPECT_TRUE(ok);
    EXPECT_EQ(stream, "15");
}


TEST(ExceptionWhilePrintingTestString, JsonNormalPrintCatchEnabled)
{
    using ThorsAnvil::Serialize::OutputType;
    std::string         stream;
    ExceptionTest::ThrowablePrint      obj(false, 16);
    bool                thrown = false;
    bool                ok;

    try
    {
        ok = (stream << ThorsAnvil::Serialize::jsonExporter(obj, OutputType::Default));
    }
    catch(...)
    {
        thrown  = true;
    }

    EXPECT_EQ(thrown, false);
    EXPECT_TRUE(ok);
    EXPECT_EQ(stream, "16");
}

TEST(ExceptionWhilePrintingTestString, JsonThrowPrint)
{
    std::string         stream;
    ExceptionTest::ThrowablePrint      obj(true, 17);
    bool                thrown = false;

    try
    {
        (stream << ThorsAnvil::Serialize::jsonExporter(obj, false));
    }
    catch(...)
    {
        thrown  = true;
    }

    EXPECT_EQ(thrown, true);
}


TEST(ExceptionWhilePrintingTestString, JsonThrowPrintCatchEnabled)
{
    using ThorsAnvil::Serialize::OutputType;
    std::string         stream;
    ExceptionTest::ThrowablePrint      obj(true, 18);
    bool                thrown = false;
    bool                ok;

    try
    {
        ok = (stream << ThorsAnvil::Serialize::jsonExporter(obj, OutputType::Default));
    }
    catch(...)
    {
        thrown  = true;
    }

    EXPECT_EQ(thrown, false);
    EXPECT_FALSE(ok);
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

    try
    {
        (stream >> ThorsAnvil::Serialize::jsonImporter(obj, false));
    }
    catch(...)
    {
        thrown  = true;
    }

    EXPECT_EQ(thrown, true);
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
    std::string         stream;
    ExceptionTest::ThrowablePrint      obj(false, 15);
    bool                thrown = false;
    bool                ok;

    try
    {
        ok = (stream << ThorsAnvil::Serialize::bsonExporter(obj, false));
    }
    catch(...)
    {
        thrown  = true;
    }

    EXPECT_EQ(thrown, false);
    EXPECT_TRUE(ok);

    static const char expectedRaw[]
                = "\x0F\x00\x00\x00"
                  "\x05"  "0\x00"  "\x02\x00\x00\x00" "\x80" "15"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(stream, expected);
}


TEST(ExceptionWhilePrintingTestString, BsonNormalPrintCatchEnabled)
{
    using ThorsAnvil::Serialize::OutputType;
    std::string         stream;
    ExceptionTest::ThrowablePrint      obj(false, 16);
    bool                thrown = false;
    bool                ok;

    try
    {
        ok = (stream << ThorsAnvil::Serialize::bsonExporter(obj, OutputType::Default));
    }
    catch(...)
    {
        thrown  = true;
    }

    EXPECT_EQ(thrown, false);
    EXPECT_TRUE(ok);
    static const char expectedRaw[]
                = "\x0F\x00\x00\x00"
                  "\x05"  "0\x00"  "\x02\x00\x00\x00" "\x80" "16"
                  "\x00";
    std::string expected(std::begin(expectedRaw), std::end(expectedRaw) - 1);
    EXPECT_EQ(stream, expected);
}

TEST(ExceptionWhilePrintingTestString, BsonThrowPrint)
{
    std::string         stream;
    ExceptionTest::ThrowablePrint      obj(true, 17);
    bool                thrown = false;

    try
    {
        (stream << ThorsAnvil::Serialize::bsonExporter(obj, false));
    }
    catch(...)
    {
        thrown  = true;
    }

    EXPECT_EQ(thrown, true);
}


TEST(ExceptionWhilePrintingTestString, BsonThrowPrintCatchEnabled)
{
    using ThorsAnvil::Serialize::OutputType;
    std::string         stream;
    ExceptionTest::ThrowablePrint      obj(true, 18);
    bool                thrown = false;
    bool                ok;

    try
    {
        ok = (stream << ThorsAnvil::Serialize::jsonExporter(obj, OutputType::Default));
    }
    catch(...)
    {
        thrown  = true;
    }

    EXPECT_EQ(thrown, false);
    EXPECT_FALSE(ok);
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

    try
    {
        (stream >> ThorsAnvil::Serialize::bsonImporter(obj, false));
    }
    catch(...)
    {
        thrown  = true;
    }

    EXPECT_EQ(thrown, true);
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

