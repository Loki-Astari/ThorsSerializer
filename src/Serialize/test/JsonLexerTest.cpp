
#include "gtest/gtest.h"
#include "JsonLexer.h"
#include "JsonLexemes.h"

TEST(JsonLexerTest, ArrayTokens)
{
    std::stringstream   stream("[],");
    JsonLexerFlexLexer  lexer(&stream);

    EXPECT_EQ('[',   lexer.yylex());
    EXPECT_EQ(']',   lexer.yylex());
    EXPECT_EQ(',',   lexer.yylex());
}
TEST(JsonLexerTest, MapTokens)
{
    std::stringstream   stream("{}:,");
    JsonLexerFlexLexer  lexer(&stream);

    EXPECT_EQ('{',   lexer.yylex());
    EXPECT_EQ('}',   lexer.yylex());
    EXPECT_EQ(':',   lexer.yylex());
    EXPECT_EQ(',',   lexer.yylex());
}
TEST(JsonLexerTest, ValueTokens)
{
    std::stringstream   stream(R"("Test" 456 789.123 true false null)");
    JsonLexerFlexLexer  lexer(&stream);

    EXPECT_EQ(ThorsAnvil::Serialize::JSON_STRING,  lexer.yylex());
    EXPECT_EQ(ThorsAnvil::Serialize::JSON_INTEGER, lexer.yylex());
    EXPECT_EQ(ThorsAnvil::Serialize::JSON_FLOAT,   lexer.yylex());
    EXPECT_EQ(ThorsAnvil::Serialize::JSON_TRUE,    lexer.yylex());
    EXPECT_EQ(ThorsAnvil::Serialize::JSON_FALSE,   lexer.yylex());
    EXPECT_EQ(ThorsAnvil::Serialize::JSON_NULL,    lexer.yylex());
}

