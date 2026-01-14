#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonManualLexer.h"
#include "JsonLexemes.h"

using ThorsAnvil::Serialize::JsonManualLexer;

class FakeParser: public ThorsAnvil::Serialize::ParserInterface
{
    public:
        FakeParser(std::istream& input)
            : ParserInterface(input, ThorsAnvil::Serialize::ParserConfig{})
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
std::map<char, int> convert1{{'{', 1}, {'}', 2}, {'[', 3}, {']', 4}, {',', 5}, {':', 6}};
std::map<int, int>  convert2{{ThorsAnvil::Serialize::JSON_NUMBER,  13},
                             {ThorsAnvil::Serialize::JSON_TRUE,    7},
                             {ThorsAnvil::Serialize::JSON_FALSE,   8},
                             {ThorsAnvil::Serialize::JSON_NULL,    9},
                             {ThorsAnvil::Serialize::JSON_STRING,  10}};
TEST(LexerTest, JsonArrayTokens)
{
    std::stringstream   stream("[],");
    FakeParser          parser(stream);
    JsonManualLexer     lexer(parser);

    EXPECT_EQ(convert1['['],   lexer.yylex());
    EXPECT_EQ(convert1[']'],   lexer.yylex());
    EXPECT_EQ(convert1[','],   lexer.yylex());
}
TEST(LexerTest, JsonMapTokens)
{
    std::stringstream   stream("{}:,");
    FakeParser          parser(stream);
    JsonManualLexer     lexer(parser);

    EXPECT_EQ(convert1['{'],   lexer.yylex());
    EXPECT_EQ(convert1['}'],   lexer.yylex());
    EXPECT_EQ(convert1[':'],   lexer.yylex());
    EXPECT_EQ(convert1[','],   lexer.yylex());
}
TEST(LexerTest, JsonValueTokens)
{
    std::stringstream   stream(R"("Test" 456 789.123 true false null)");
    FakeParser          parser(stream);
    JsonManualLexer     lexer(parser);

    EXPECT_EQ(convert2[ThorsAnvil::Serialize::JSON_STRING],  lexer.yylex());
    lexer.getRawString();
    EXPECT_EQ(convert2[ThorsAnvil::Serialize::JSON_NUMBER],  lexer.yylex());
    lexer.getRawString();
    EXPECT_EQ(convert2[ThorsAnvil::Serialize::JSON_NUMBER],  lexer.yylex());
    lexer.getRawString();
    EXPECT_EQ(convert2[ThorsAnvil::Serialize::JSON_TRUE],    lexer.yylex());
    lexer.getRawString();
    EXPECT_EQ(convert2[ThorsAnvil::Serialize::JSON_FALSE],   lexer.yylex());
    lexer.getRawString();
    EXPECT_EQ(convert2[ThorsAnvil::Serialize::JSON_NULL],    lexer.yylex());
    lexer.getRawString();
}

