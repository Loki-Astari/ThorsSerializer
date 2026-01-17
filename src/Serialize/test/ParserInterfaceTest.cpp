#include "gtest/gtest.h"
#include "JsonParser.h"
#include "BsonParser.h"
#include "BsonConfig.h"
#include "Serialize.h"

namespace TA=ThorsAnvil::Serialize;
using TA::JsonParser;
using TA::BsonParser;
using TA::ParserConfig;
using TA::ParserToken;
using TA::BsonParserConfig;

TEST(ParserInterfaceTest, JsonNormalNoPushBack)
{
    std::stringstream   stream("[10,11,12]");
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

TEST(ParserInterfaceTest, JsonPushBackValue)
{
    std::stringstream   stream("[10,11,12]");
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

TEST(ParserInterfaceTest, JsonPushBackTwoValue)
{
    std::stringstream   stream("[10,11,12]");
    JsonParser          parser(stream);

    EXPECT_EQ(ParserToken::DocStart, parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::Value, parser.getToken());

    parser.pushBackToken(ParserToken::Value);
#if defined(VALIDATE_EXTRA_PUSH_BACK_TOKEN)
    ASSERT_ANY_THROW(
        parser.pushBackToken(ParserToken::Value)
    );
#endif
}

TEST(ParserInterfaceTest, JsonPushBackTwoValueWithReads)
{
    std::stringstream   stream("[10,11,12]");
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

TEST(ParserInterfaceTest, BsonNormalNoPushBack)
{
    //NOTE INPUT ("[10,11,12]");
    static const char inputRaw[]
                = "\x1A\x00\x00\x00"
                  "\x10"  "0\x00"  "\x0A\x00\x00\x00"
                  "\x10"  "1\x00"  "\x0B\x00\x00\x00"
                  "\x10"  "2\x00"  "\x0C\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    BsonParser          parser(stream, BsonParserConfig{config, ThorsAnvil::Serialize::BsonContainer::Array});

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

TEST(ParserInterfaceTest, BsonPushBackValue)
{
    //NOTE INPUT ("[10,11,12]");
    static const char inputRaw[]
                = "\x1A\x00\x00\x00"
                  "\x10"  "0\x00"  "\x0A\x00\x00\x00"
                  "\x10"  "1\x00"  "\x0B\x00\x00\x00"
                  "\x10"  "2\x00"  "\x0C\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    BsonParser          parser(stream, BsonParserConfig{config, ThorsAnvil::Serialize::BsonContainer::Array});

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

TEST(ParserInterfaceTest, BsonPushBackTwoValue)
{
    //NOTE INPUT ("[10,11,12]");
    static const char inputRaw[]
                = "\x1A\x00\x00\x00"
                  "\x10"  "0\x00"  "\x0A\x00\x00\x00"
                  "\x10"  "1\x00"  "\x0B\x00\x00\x00"
                  "\x10"  "2\x00"  "\x0C\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    BsonParser          parser(stream, BsonParserConfig{config, ThorsAnvil::Serialize::BsonContainer::Array});

    EXPECT_EQ(ParserToken::DocStart, parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::Value, parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::Value, parser.getToken());

    parser.pushBackToken(ParserToken::Value);
#if defined(VALIDATE_EXTRA_PUSH_BACK_TOKEN)
    ASSERT_ANY_THROW(
        parser.pushBackToken(ParserToken::Value)
    );
#endif
}

TEST(ParserInterfaceTest, BsonPushBackTwoValueWithReads)
{
    //NOTE INPUT ("[10,11,12]");
    static const char inputRaw[]
                = "\x1A\x00\x00\x00"
                  "\x10"  "0\x00"  "\x0A\x00\x00\x00"
                  "\x10"  "1\x00"  "\x0B\x00\x00\x00"
                  "\x10"  "2\x00"  "\x0C\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    BsonParser          parser(stream, BsonParserConfig{config, ThorsAnvil::Serialize::BsonContainer::Array});

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


