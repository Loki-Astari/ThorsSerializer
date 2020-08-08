#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonManualLexer.h"
#include "BsonManualLexer.h"
#include "JsonLexemes.h"

using ThorsAnvil::Serialize::JsonManualLexer;
using ThorsAnvil::Serialize::BsonManualLexer;

TEST(LexerTest, JsonArrayTokens)
{
    std::stringstream   stream("[],");
    JsonManualLexer     lexer(stream);

    EXPECT_EQ('[',   lexer.yylex());
    EXPECT_EQ(']',   lexer.yylex());
    EXPECT_EQ(',',   lexer.yylex());
}
TEST(LexerTest, JsonMapTokens)
{
    std::stringstream   stream("{}:,");
    JsonManualLexer     lexer(stream);

    EXPECT_EQ('{',   lexer.yylex());
    EXPECT_EQ('}',   lexer.yylex());
    EXPECT_EQ(':',   lexer.yylex());
    EXPECT_EQ(',',   lexer.yylex());
}
TEST(LexerTest, JsonValueTokens)
{
    std::stringstream   stream(R"("Test" 456 789.123 true false null)");
    JsonManualLexer     lexer(stream);

    EXPECT_EQ(ThorsAnvil::Serialize::JSON_STRING,  lexer.yylex());
    lexer.getRawString();
    EXPECT_EQ(ThorsAnvil::Serialize::JSON_INTEGER, lexer.yylex());
    lexer.getRawString();
    EXPECT_EQ(ThorsAnvil::Serialize::JSON_FLOAT,   lexer.yylex());
    lexer.getRawString();
    EXPECT_EQ(ThorsAnvil::Serialize::JSON_TRUE,    lexer.yylex());
    lexer.getRawString();
    EXPECT_EQ(ThorsAnvil::Serialize::JSON_FALSE,   lexer.yylex());
    lexer.getRawString();
    EXPECT_EQ(ThorsAnvil::Serialize::JSON_NULL,    lexer.yylex());
    lexer.getRawString();
}
TEST(LexerTest, BsonArrayTokens)
{
    std::stringstream   stream("[],");
    BsonManualLexer     lexer(stream);

    EXPECT_EQ('[',   lexer.yylex());
    EXPECT_EQ(']',   lexer.yylex());
    EXPECT_EQ(',',   lexer.yylex());
}
TEST(LexerTest, BsonMapTokens)
{
    std::stringstream   stream("{}:,");
    BsonManualLexer     lexer(stream);

    EXPECT_EQ('{',   lexer.yylex());
    EXPECT_EQ('}',   lexer.yylex());
    EXPECT_EQ(':',   lexer.yylex());
    EXPECT_EQ(',',   lexer.yylex());
}
TEST(LexerTest, BsonValueTokens)
{
    std::stringstream   stream(R"("Test" 456 789.123 true false null)");
    BsonManualLexer     lexer(stream);

    EXPECT_EQ(ThorsAnvil::Serialize::JSON_STRING,  lexer.yylex());
    lexer.getRawString();
    EXPECT_EQ(ThorsAnvil::Serialize::JSON_INTEGER, lexer.yylex());
    lexer.getRawString();
    EXPECT_EQ(ThorsAnvil::Serialize::JSON_FLOAT,   lexer.yylex());
    lexer.getRawString();
    EXPECT_EQ(ThorsAnvil::Serialize::JSON_TRUE,    lexer.yylex());
    lexer.getRawString();
    EXPECT_EQ(ThorsAnvil::Serialize::JSON_FALSE,   lexer.yylex());
    lexer.getRawString();
    EXPECT_EQ(ThorsAnvil::Serialize::JSON_NULL,    lexer.yylex());
    lexer.getRawString();
}

