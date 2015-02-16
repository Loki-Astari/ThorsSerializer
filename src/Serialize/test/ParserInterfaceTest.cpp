
#include "gtest/gtest.h"
#include "JsonParser.h"

namespace TA=ThorsAnvil::Serialize;
using TA::JsonParser;
using TA::ParserInterface;

TEST(ParserInterfaceTest, NormalNoPushBack)
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

TEST(ParserInterfaceTest, PushBackValue)
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

TEST(ParserInterfaceTest, PushBackTwoValue)
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

TEST(ParserInterfaceTest, PushBackTwoValueWithReads)
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

