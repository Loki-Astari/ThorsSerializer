#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonManualLexer.h"
#include "JsonLexemes.h"

using ThorsAnvil::Serialize::JsonManualLexer;

class FakeParser: public ThorsAnvil::Serialize::ParserInterface
{
    public:
        FakeParser(std::string const& input)
            : ParserInterface(input)
        {}
        virtual ThorsAnvil::Serialize::FormatType  formatType()    {return ThorsAnvil::Serialize::FormatType::Json;}
        virtual ThorsAnvil::Serialize::ParserToken getNextToken()  {return ThorsAnvil::Serialize::ParserToken::Value;}
        virtual std::string_view     getKey()            {return "";}

        virtual void    getValue(short int&)             {}
        virtual void    getValue(int&)                   {}
        virtual void    getValue(long int&)              {}
        virtual void    getValue(long long int&)         {}

        virtual void    getValue(unsigned short int&)    {}
        virtual void    getValue(unsigned int&)          {}
        virtual void    getValue(unsigned long int&)     {}
        virtual void    getValue(unsigned long long int&){}

        virtual void    getValue(float&)                 {}
        virtual void    getValue(double&)                {}
        virtual void    getValue(long double&)           {}

        virtual void    getValue(bool&)                  {}
        virtual void    getValue(std::string&)           {}

        virtual bool    isValueNull()                    {return false;}

        virtual std::string_view getRawValue()           {return "";}
};
TEST(LexerTestString, JsonArrayTokens)
{
    std::string         stream("[],");
    FakeParser          parser(stream);
    JsonManualLexer     lexer(parser);

    EXPECT_EQ('[',   lexer.yylex());
    EXPECT_EQ(']',   lexer.yylex());
    EXPECT_EQ(',',   lexer.yylex());
}
TEST(LexerTestString, JsonMapTokens)
{
    std::string         stream("{}:,");
    FakeParser          parser(stream);
    JsonManualLexer     lexer(parser);

    EXPECT_EQ('{',   lexer.yylex());
    EXPECT_EQ('}',   lexer.yylex());
    EXPECT_EQ(':',   lexer.yylex());
    EXPECT_EQ(',',   lexer.yylex());
}
TEST(LexerTestString, JsonValueTokens)
{
    std::string         stream(R"("Test" 456 789.123 true false null)");
    FakeParser          parser(stream);
    JsonManualLexer     lexer(parser);

    EXPECT_EQ(ThorsAnvil::Serialize::JSON_STRING,  lexer.yylex());
    lexer.getRawString();
    EXPECT_EQ(ThorsAnvil::Serialize::JSON_NUMBER,  lexer.yylex());
    lexer.getRawString();
    EXPECT_EQ(ThorsAnvil::Serialize::JSON_NUMBER,  lexer.yylex());
    lexer.getRawString();
    EXPECT_EQ(ThorsAnvil::Serialize::JSON_TRUE,    lexer.yylex());
    lexer.getRawString();
    EXPECT_EQ(ThorsAnvil::Serialize::JSON_FALSE,   lexer.yylex());
    lexer.getRawString();
    EXPECT_EQ(ThorsAnvil::Serialize::JSON_NULL,    lexer.yylex());
    lexer.getRawString();
}

