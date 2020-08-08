#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonParser.h"
#include "BsonParser.h"

namespace TA=ThorsAnvil::Serialize;
using TA::JsonParser;
using TA::BsonParser;
using TA::ParserInterface;

TEST(ParserInterfaceTest, JsonNormalNoPushBack)
{
    std::stringstream   stream("[10,11,12]");
    JsonParser          parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd, parser.getToken());
}

TEST(ParserInterfaceTest, JsonPushBackValue)
{
    std::stringstream   stream("[10,11,12]");
    JsonParser          parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());

    parser.pushBackToken(ParserInterface::ParserToken::Value);
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());

    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd, parser.getToken());
}

TEST(ParserInterfaceTest, JsonPushBackTwoValue)
{
    std::stringstream   stream("[10,11,12]");
    JsonParser          parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());

    parser.pushBackToken(ParserInterface::ParserToken::Value);
    ASSERT_ANY_THROW(
        parser.pushBackToken(ParserInterface::ParserToken::Value)
    );
}

TEST(ParserInterfaceTest, JsonPushBackTwoValueWithReads)
{
    std::stringstream   stream("[10,11,12]");
    JsonParser          parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());

    parser.pushBackToken(ParserInterface::ParserToken::Value);
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());

    parser.pushBackToken(ParserInterface::ParserToken::Value);
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());

    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd, parser.getToken());
}

TEST(ParserInterfaceTest, BsonNormalNoPushBack)
{
    std::stringstream   stream("[10,11,12]");
    BsonParser          parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd, parser.getToken());
}

TEST(ParserInterfaceTest, BsonPushBackValue)
{
    std::stringstream   stream("[10,11,12]");
    BsonParser          parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());

    parser.pushBackToken(ParserInterface::ParserToken::Value);
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());

    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd, parser.getToken());
}

TEST(ParserInterfaceTest, BsonPushBackTwoValue)
{
    std::stringstream   stream("[10,11,12]");
    BsonParser          parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());

    parser.pushBackToken(ParserInterface::ParserToken::Value);
    ASSERT_ANY_THROW(
        parser.pushBackToken(ParserInterface::ParserToken::Value)
    );
}

TEST(ParserInterfaceTest, BsonPushBackTwoValueWithReads)
{
    std::stringstream   stream("[10,11,12]");
    BsonParser          parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());

    parser.pushBackToken(ParserInterface::ParserToken::Value);
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());

    parser.pushBackToken(ParserInterface::ParserToken::Value);
    EXPECT_EQ(ParserInterface::ParserToken::Value, parser.getToken());

    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd, parser.getToken());
}


