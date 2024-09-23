#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonParser.h"
#include "BsonParser.h"

namespace TA=ThorsAnvil::Serialize;
using TA::JsonParser;
using TA::BsonParser;
using TA::ParserConfig;
using TA::ParserToken;

TEST(ParserInterfaceTestString, JsonNormalNoPushBack)
{
    std::string         stream("[10,11,12]");
    JsonParser          parser(stream);

    EXPECT_EQ(ParserToken::DocStart, parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::ArrayEnd, parser.getToken());
    EXPECT_EQ(ParserToken::DocEnd, parser.getToken());
}

TEST(ParserInterfaceTestString, JsonPushBackValue)
{
    std::string         stream("[10,11,12]");
    JsonParser          parser(stream);

    EXPECT_EQ(ParserToken::DocStart, parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::Value, parser.getToken());

    parser.pushBackToken(ParserToken::Value);
    EXPECT_EQ(ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();

    EXPECT_EQ(ParserToken::ArrayEnd, parser.getToken());
    EXPECT_EQ(ParserToken::DocEnd, parser.getToken());
}

TEST(ParserInterfaceTestString, JsonPushBackTwoValue)
{
    std::string         stream("[10,11,12]");
    JsonParser          parser(stream);

    EXPECT_EQ(ParserToken::DocStart, parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::Value, parser.getToken());

    parser.pushBackToken(ParserToken::Value);
    ASSERT_ANY_THROW(
        parser.pushBackToken(ParserToken::Value)
    );
}

TEST(ParserInterfaceTestString, JsonPushBackTwoValueWithReads)
{
    std::string         stream("[10,11,12]");
    JsonParser          parser(stream);

    EXPECT_EQ(ParserToken::DocStart, parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::Value, parser.getToken());

    parser.pushBackToken(ParserToken::Value);
    EXPECT_EQ(ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();

    parser.pushBackToken(ParserToken::Value);
    EXPECT_EQ(ParserToken::Value, parser.getToken());

    EXPECT_EQ(ParserToken::ArrayEnd, parser.getToken());
    EXPECT_EQ(ParserToken::DocEnd, parser.getToken());
}

TEST(ParserInterfaceTestString, BsonNormalNoPushBack)
{
    //NOTE INPUT ("[10,11,12]");
    static const char inputRaw[]
                = "\x1A\x00\x00\x00"
                  "\x10"  "0\x00"  "\x0A\x00\x00\x00"
                  "\x10"  "1\x00"  "\x0B\x00\x00\x00"
                  "\x10"  "2\x00"  "\x0C\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::string         stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    BsonParser          parser(stream, config);

    EXPECT_EQ(ParserToken::DocStart, parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::ArrayEnd, parser.getToken());
    EXPECT_EQ(ParserToken::DocEnd, parser.getToken());
}

TEST(ParserInterfaceTestString, BsonPushBackValue)
{
    //NOTE INPUT ("[10,11,12]");
    static const char inputRaw[]
                = "\x1A\x00\x00\x00"
                  "\x10"  "0\x00"  "\x0A\x00\x00\x00"
                  "\x10"  "1\x00"  "\x0B\x00\x00\x00"
                  "\x10"  "2\x00"  "\x0C\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::string         stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    BsonParser          parser(stream, config);

    EXPECT_EQ(ParserToken::DocStart, parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::Value, parser.getToken());

    parser.pushBackToken(ParserToken::Value);
    EXPECT_EQ(ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();

    EXPECT_EQ(ParserToken::ArrayEnd, parser.getToken());
    EXPECT_EQ(ParserToken::DocEnd, parser.getToken());
}

TEST(ParserInterfaceTestString, BsonPushBackTwoValue)
{
    //NOTE INPUT ("[10,11,12]");
    static const char inputRaw[]
                = "\x1A\x00\x00\x00"
                  "\x10"  "0\x00"  "\x0A\x00\x00\x00"
                  "\x10"  "1\x00"  "\x0B\x00\x00\x00"
                  "\x10"  "2\x00"  "\x0C\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::string         stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    BsonParser          parser(stream, config);

    EXPECT_EQ(ParserToken::DocStart, parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::Value, parser.getToken());

    parser.pushBackToken(ParserToken::Value);
    ASSERT_ANY_THROW(
        parser.pushBackToken(ParserToken::Value)
    );
}

TEST(ParserInterfaceTestString, BsonPushBackTwoValueWithReads)
{
    //NOTE INPUT ("[10,11,12]");
    static const char inputRaw[]
                = "\x1A\x00\x00\x00"
                  "\x10"  "0\x00"  "\x0A\x00\x00\x00"
                  "\x10"  "1\x00"  "\x0B\x00\x00\x00"
                  "\x10"  "2\x00"  "\x0C\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::string         stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    BsonParser          parser(stream, config);

    EXPECT_EQ(ParserToken::DocStart, parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::Value, parser.getToken());

    parser.pushBackToken(ParserToken::Value);
    EXPECT_EQ(ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();

    parser.pushBackToken(ParserToken::Value);
    EXPECT_EQ(ParserToken::Value, parser.getToken());

    EXPECT_EQ(ParserToken::ArrayEnd, parser.getToken());
    EXPECT_EQ(ParserToken::DocEnd, parser.getToken());
}


