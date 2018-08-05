
#include "gtest/gtest.h"
#include "JsonParser.h"
#include "test/SerializeTest.h"

namespace TA=ThorsAnvil::Serialize;
using TA::JsonParser;
using TA::ParserInterface;
using TA::DeSerializer;

class ParserMock: public ParserInterface
{
    std::vector<ParserToken> const& tokens;
    std::vector<std::string> const& keys;
    std::vector<std::string> const& values;
    int nextToken;
    int nextKey;
    int nextValue;
    public:
        ParserMock(std::istream& input, std::vector<ParserToken> const& tokens,  std::vector<std::string> const& keys, std::vector<std::string> const& values)
            : ParserInterface(input, ParseType::Weak)
            , tokens(tokens)
            , keys(keys)
            , values(values)
            , nextToken(0)
            , nextKey(0)
            , nextValue(0)
        {}
        virtual ParserToken     getNextToken()           override{return tokens[nextToken++];}
        virtual std::string     getKey()                 override{return keys[nextKey++];}

        virtual void    getValue(short int&)             override{}
        virtual void    getValue(int&)                   override{}
        virtual void    getValue(long int&)              override{}
        virtual void    getValue(long long int&)         override{}

        virtual void    getValue(unsigned short int&)    override{}
        virtual void    getValue(unsigned int&)          override{}
        virtual void    getValue(unsigned long int&)     override{}
        virtual void    getValue(unsigned long long int&)override{}

        virtual void    getValue(float&)                 override{}
        virtual void    getValue(double&)                override{}
        virtual void    getValue(long double&)           override{}

        virtual void    getValue(bool&)                  override{}

        virtual void    getValue(std::string& value)     override{value = values[nextValue++];}

        virtual bool    isValueNull()                    override{return false;}

        virtual std::string getRawValue()                override{return "";}
};
TEST(CornerCaseTest, IgnoreTheArrayUnexpectedKey)
{
    std::stringstream           stream;
    std::vector<std::string>    keys    {"Ignore"};
    std::vector<std::string>    values;
    std::vector<ParserInterface::ParserToken>    tokens
    {   ParserInterface::ParserToken::DocStart,
            ParserInterface::ParserToken::MapStart,
                ParserInterface::ParserToken::Key,  // Key
                    ParserInterface::ParserToken::ArrayStart,
                        ParserInterface::ParserToken::Key,   /* Don't expect a Key in Array */
                    ParserInterface::ParserToken::ArrayEnd,
            ParserInterface::ParserToken::MapEnd,
        ParserInterface::ParserToken::DocEnd
    };
    ParserMock      parser(stream, tokens, keys, values);
    DeSerializer    deSerializer(parser);


    CornerCaseClass     value;
    EXPECT_THROW(
        deSerializer.parse(value),
        std::runtime_error
    );
}
TEST(CornerCaseTest, IgnoreTheArrayUnexpectedMapEnd)
{
    std::stringstream           stream;
    std::vector<std::string>    keys    {"Ignore"};
    std::vector<std::string>    values;
    std::vector<ParserInterface::ParserToken>    tokens
    {   ParserInterface::ParserToken::DocStart,
            ParserInterface::ParserToken::MapStart,
                ParserInterface::ParserToken::Key,  // Key
                    ParserInterface::ParserToken::ArrayStart,
                        ParserInterface::ParserToken::MapEnd,   /* Don't expect a MapEnd in Array */
                    ParserInterface::ParserToken::ArrayEnd,
            ParserInterface::ParserToken::MapEnd,
        ParserInterface::ParserToken::DocEnd
    };
    ParserMock      parser(stream, tokens, keys, values);
    DeSerializer    deSerializer(parser);


    CornerCaseClass     value;
    EXPECT_THROW(
        deSerializer.parse(value),
        std::runtime_error
    );
}
TEST(CornerCaseTest, IgnoreTheArrayUnexpectedInvalidValue)
{
    std::stringstream           stream;
    std::vector<std::string>    keys    {"Ignore"};
    std::vector<std::string>    values;
    std::vector<ParserInterface::ParserToken>    tokens
    {   ParserInterface::ParserToken::DocStart,
            ParserInterface::ParserToken::MapStart,
                ParserInterface::ParserToken::Key,  // Key
                    ParserInterface::ParserToken::ArrayStart,
                        ((ParserInterface::ParserToken)32762),   /* Don't expect a Invalid in Array */
                    ParserInterface::ParserToken::ArrayEnd,
            ParserInterface::ParserToken::MapEnd,
        ParserInterface::ParserToken::DocEnd
    };
    ParserMock      parser(stream, tokens, keys, values);
    DeSerializer    deSerializer(parser);


    CornerCaseClass     value;
    EXPECT_THROW(
        deSerializer.parse(value),
        std::runtime_error
    );
}
TEST(CornerCaseTest, IgnoreTheValueUnexpectedKey)
{
    std::stringstream           stream;
    std::vector<std::string>    keys    {"Ignore"};
    std::vector<std::string>    values;
    std::vector<ParserInterface::ParserToken>    tokens
    {   ParserInterface::ParserToken::DocStart,
            ParserInterface::ParserToken::MapStart,
                ParserInterface::ParserToken::Key,  // Key
                ParserInterface::ParserToken::Key,  /* Don't expect a key after a key */
            ParserInterface::ParserToken::MapEnd,
        ParserInterface::ParserToken::DocEnd
    };
    ParserMock      parser(stream, tokens, keys, values);
    DeSerializer    deSerializer(parser);


    CornerCaseClass     value;
    EXPECT_THROW(
        deSerializer.parse(value),
        std::runtime_error
    );
}
TEST(CornerCaseTest, IgnoreTheValueUnexpectedMapEnd)
{
    std::stringstream           stream;
    std::vector<std::string>    keys    {"Ignore"};
    std::vector<std::string>    values;
    std::vector<ParserInterface::ParserToken>    tokens
    {   ParserInterface::ParserToken::DocStart,
            ParserInterface::ParserToken::MapStart,
                ParserInterface::ParserToken::Key,  // Key
                ParserInterface::ParserToken::MapEnd,  /* Don't expect a MapEnd after a key */
            ParserInterface::ParserToken::MapEnd,
        ParserInterface::ParserToken::DocEnd
    };
    ParserMock      parser(stream, tokens, keys, values);
    DeSerializer    deSerializer(parser);


    CornerCaseClass     value;
    EXPECT_THROW(
        deSerializer.parse(value),
        std::runtime_error
    );
}
TEST(CornerCaseTest, IgnoreTheValueUnexpectedArrayEnd)
{
    std::stringstream           stream;
    std::vector<std::string>    keys    {"Ignore"};
    std::vector<std::string>    values;
    std::vector<ParserInterface::ParserToken>    tokens
    {   ParserInterface::ParserToken::DocStart,
            ParserInterface::ParserToken::MapStart,
                ParserInterface::ParserToken::Key,  // Key
                ParserInterface::ParserToken::ArrayEnd,  /* Don't expect an ArrayEnd after a key */
            ParserInterface::ParserToken::MapEnd,
        ParserInterface::ParserToken::DocEnd
    };
    ParserMock      parser(stream, tokens, keys, values);
    DeSerializer    deSerializer(parser);


    CornerCaseClass     value;
    EXPECT_THROW(
        deSerializer.parse(value),
        std::runtime_error
    );
}
TEST(CornerCaseTest, IgnoreTheValueUnexpectedInvalidValue)
{
    std::stringstream           stream;
    std::vector<std::string>    keys    {"Ignore"};
    std::vector<std::string>    values;
    std::vector<ParserInterface::ParserToken>    tokens
    {   ParserInterface::ParserToken::DocStart,
            ParserInterface::ParserToken::MapStart,
                ParserInterface::ParserToken::Key,  // Key
                ((ParserInterface::ParserToken)32762),   /* Don't expect a Invalid after a Key */
            ParserInterface::ParserToken::MapEnd,
        ParserInterface::ParserToken::DocEnd
    };
    ParserMock      parser(stream, tokens, keys, values);
    DeSerializer    deSerializer(parser);


    CornerCaseClass     value;
    EXPECT_THROW(
        deSerializer.parse(value),
        std::runtime_error
    );
}
TEST(CornerCaseTest, DeSerializerNoDocStart)
{
    auto test = []()
    {
        std::stringstream           stream;
        std::vector<std::string>    keys;
        std::vector<std::string>    values;
        std::vector<ParserInterface::ParserToken>    tokens
        {
            // Missing DocStart
            ParserInterface::ParserToken::MapStart,
            ParserInterface::ParserToken::MapEnd,
            ParserInterface::ParserToken::DocEnd
        };
        ParserMock      parser(stream, tokens, keys, values);
        DeSerializer    deSerializer(parser);

        CornerCaseClass     value;
        deSerializer.parse(value);
    };

    EXPECT_THROW(
        test(),
        std::runtime_error
    );
}
TEST(CornerCaseTest, DeSerializerNoDocEnd)
{
    auto test = [](){
        std::stringstream           stream;
        std::vector<std::string>    keys;
        std::vector<std::string>    values;
        std::vector<ParserInterface::ParserToken>    tokens
        {
            ParserInterface::ParserToken::DocStart,
            ParserInterface::ParserToken::MapStart,
            ParserInterface::ParserToken::MapEnd,
            // Missing Doc End
        };
        ParserMock      parser(stream, tokens, keys, values);
        DeSerializer    deSerializer(parser);

        CornerCaseClass     value;
        deSerializer.parse(value);
    };
    EXPECT_THROW(
        test(),
        std::runtime_error
    );
}

