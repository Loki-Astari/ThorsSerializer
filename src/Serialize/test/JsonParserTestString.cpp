#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonParser.h"

namespace TA=ThorsAnvil::Serialize;
using TA::ParserToken;

TEST(JsonParserTestString, ArrayEmpty)
{
    std::string         stream("[]");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserToken::DocEnd,     parser.getToken());
}
TEST(JsonParserTestString, ArrayOneValue)
{
    std::string         stream("[12]");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserToken::DocEnd,     parser.getToken());
}
TEST(JsonParserTestString, ArrayTwoValue)
{
    std::string         stream("[12,13]");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserToken::DocEnd,     parser.getToken());
}
TEST(JsonParserTestString, ArrayThreeValue)
{
    std::string         stream("[12,13,14]");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserToken::DocEnd,     parser.getToken());
}
TEST(JsonParserTestString, ArrayWithArray)
{
    std::string         stream("[[]]");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserToken::DocEnd,     parser.getToken());
}
TEST(JsonParserTestString, ArrayWithTwoArray)
{
    std::string         stream("[[],[]]");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserToken::DocEnd,     parser.getToken());
}
TEST(JsonParserTestString, ArrayWithMap)
{
    std::string         stream("[{}]");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserToken::DocEnd,     parser.getToken());
}
TEST(JsonParserTestString, ArrayWithTwoMap)
{
    std::string         stream("[{},{}]");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserToken::DocEnd,     parser.getToken());
}
TEST(JsonParserTestString, MapEmpty)
{
    std::string         stream("{}");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserToken::DocEnd,     parser.getToken());
}
TEST(JsonParserTestString, MapOneValue)
{
    std::string         stream(R"({"One": 12})");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserToken::DocEnd,     parser.getToken());
}
TEST(JsonParserTestString, MapTwoValue)
{
    std::string         stream(R"({"one": 12, "two": 13})");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserToken::DocEnd,     parser.getToken());
}
TEST(JsonParserTestString, MapThreeValue)
{
    std::string         stream(R"({"one":12, "two": 13, "three": 14})");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserToken::DocEnd,     parser.getToken());
}
TEST(JsonParserTestString, MapWithArray)
{
    std::string         stream(R"({"one": []})");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserToken::DocEnd,     parser.getToken());
}
TEST(JsonParserTestString, MapWithTwoArray)
{
    std::string         stream(R"({"one": [], "two": []}])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserToken::DocEnd,     parser.getToken());
}
TEST(JsonParserTestString, MapWithMap)
{
    std::string         stream(R"({"one": {}})");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserToken::DocEnd,     parser.getToken());
}
TEST(JsonParserTestString, MapWithTwoMap)
{
    std::string         stream(R"({"one": {}, "two": {}})");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserToken::DocEnd,     parser.getToken());
}
TEST(JsonParserTestString, GetKeyValue)
{
    std::string         stream(R"({"one": 15})");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserToken::Key,        parser.getToken());

    std::string_view key = parser.getKey();
    EXPECT_EQ("one", key);

    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    int value;
    parser.getValue(value);
    EXPECT_EQ(15, value);

    EXPECT_EQ(ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserToken::DocEnd,     parser.getToken());
}
TEST(JsonParserTestString, GetArrayValues)
{
    std::string         stream(R"([true, false, 123, 123.4, "A String"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    bool    test1   = false;
    parser.getValue(test1);
    EXPECT_EQ(true, test1);

    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    bool    test2   = true;
    parser.getValue(test2);
    EXPECT_EQ(false, test2);

    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    int    test3   = 0;
    parser.getValue(test3);
    EXPECT_EQ(123, test3);

    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    double test4   = 80;
    parser.getValue(test4);
    EXPECT_EQ(1234, (int)(test4*10));

    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    std::string    test5;
    parser.getValue(test5);
    EXPECT_EQ("A String", test5);


    EXPECT_EQ(ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserToken::DocEnd,     parser.getToken());
}
TEST(JsonParserTestString, CheckErrorDoesNotRead)
{
    std::string         stream("][");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());

    // First Character is an error.
    EXPECT_EQ(ParserToken::Error,      parser.getToken());

    // Subsequent read should also be an error.
    // But it should not read from the stream
    EXPECT_EQ(ParserToken::Error,      parser.getToken());
}

TEST(JsonParserTestString, getDataFromString_1)
{
    std::string         stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    std::string     value1;
    ASSERT_NO_THROW(
        parser.getValue(value1);
    );
    EXPECT_EQ("Test", value1);
}

TEST(JsonParserTestString, getDataFromString_2)
{
    std::string         stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    short             value2a;
    ASSERT_ANY_THROW(
        parser.getValue(value2a)
    );
}

TEST(JsonParserTestString, getDataFromString_3)
{
    std::string         stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    int             value2b;
    ASSERT_ANY_THROW(
        parser.getValue(value2b)
    );
}

TEST(JsonParserTestString, getDataFromString_4)
{
    std::string         stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    long             value2c;
    ASSERT_ANY_THROW(
        parser.getValue(value2c)
    );
}

TEST(JsonParserTestString, getDataFromString_5)
{
    std::string         stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    long long             value2d;
    ASSERT_ANY_THROW(
        parser.getValue(value2d)
    );
}

TEST(JsonParserTestString, getDataFromString_6)
{
    std::string         stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    unsigned short             value2e;
    ASSERT_ANY_THROW(
        parser.getValue(value2e)
    );
}

TEST(JsonParserTestString, getDataFromString_7)
{
    std::string         stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    unsigned int             value2f;
    ASSERT_ANY_THROW(
        parser.getValue(value2f)
    );
}

TEST(JsonParserTestString, getDataFromString_8)
{
    std::string         stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    unsigned long             value2g;
    ASSERT_ANY_THROW(
        parser.getValue(value2g)
    );
}

TEST(JsonParserTestString, getDataFromString_9)
{
    std::string         stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    unsigned long long             value2h;
    ASSERT_ANY_THROW(
        parser.getValue(value2h)
    );

}

TEST(JsonParserTestString, getDataFromString_a)
{
    std::string         stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    float          value3a;
    ASSERT_ANY_THROW(
        parser.getValue(value3a)
    );
}

TEST(JsonParserTestString, getDataFromString_b)
{
    std::string         stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    double          value3b;
    ASSERT_ANY_THROW(
        parser.getValue(value3b)
    );
}

TEST(JsonParserTestString, getDataFromString_c)
{
    std::string         stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
}

TEST(JsonParserTestString, getDataFromString_d)
{
    std::string         stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    long double          value3c;
    ASSERT_ANY_THROW(
        parser.getValue(value3c)
    );

}

TEST(JsonParserTestString, getDataFromString_e)
{
    std::string         stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    bool            value4;
    ASSERT_ANY_THROW(
        parser.getValue(value4)
    );
}

TEST(JsonParserTestString, getDataFromInt_1)
{
    std::string         stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    std::string     value1;
    ASSERT_ANY_THROW(
        parser.getValue(value1)
    );
}

TEST(JsonParserTestString, getDataFromInt_2)
{
    std::string         stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    short             value2a;
    ASSERT_NO_THROW(
        parser.getValue(value2a)
    );
    EXPECT_EQ(56, value2a);
}

TEST(JsonParserTestString, getDataFromInt_3)
{
    std::string         stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    int             value2b;
    ASSERT_NO_THROW(
        parser.getValue(value2b)
    );
    EXPECT_EQ(56, value2b);
}

TEST(JsonParserTestString, getDataFromInt_4)
{
    std::string         stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    long             value2c;
    ASSERT_NO_THROW(
        parser.getValue(value2c)
    );
    EXPECT_EQ(56, value2c);
}

TEST(JsonParserTestString, getDataFromInt_5)
{
    std::string         stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    long long             value2d;
    ASSERT_NO_THROW(
        parser.getValue(value2d)
    );
    EXPECT_EQ(56, value2d);
}

TEST(JsonParserTestString, getDataFromInt_6)
{
    std::string         stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    short             value2e;
    ASSERT_NO_THROW(
        parser.getValue(value2e)
    );
    EXPECT_EQ(56, value2e);
}

TEST(JsonParserTestString, getDataFromInt_7)
{
    std::string         stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    int             value2f;
    ASSERT_NO_THROW(
        parser.getValue(value2f)
    );
    EXPECT_EQ(56, value2f);
}

TEST(JsonParserTestString, getDataFromInt_8)
{
    std::string         stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    long             value2g;
    ASSERT_NO_THROW(
        parser.getValue(value2g)
    );
    EXPECT_EQ(56, value2g);
}

TEST(JsonParserTestString, getDataFromInt_9)
{
    std::string         stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    long long             value2h;
    ASSERT_NO_THROW(
        parser.getValue(value2h)
    );
    EXPECT_EQ(56, value2h);
}

TEST(JsonParserTestString, getDataFromInt_a)
{
    std::string         stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    float          value3a;
    ASSERT_NO_THROW(
        parser.getValue(value3a)
    );
    EXPECT_EQ(56, value3a);
}

TEST(JsonParserTestString, getDataFromInt_b)
{
    std::string         stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    double          value3b;
    ASSERT_NO_THROW(
        parser.getValue(value3b)
    );
    EXPECT_EQ(56, value3b);
}

TEST(JsonParserTestString, getDataFromInt_c)
{
    std::string         stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    long double          value3c;
    ASSERT_NO_THROW(
        parser.getValue(value3c)
    );
    EXPECT_EQ(56, value3c);
}

TEST(JsonParserTestString, getDataFromInt_d)
{
    std::string         stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    bool            value4;
    ASSERT_ANY_THROW(
        parser.getValue(value4)
    );
}

TEST(JsonParserTestString, getDataFromFloat_1)
{
    std::string         stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    std::string     value1;
    ASSERT_ANY_THROW(
        parser.getValue(value1)
    );
}

TEST(JsonParserTestString, getDataFromFloat_2)
{
    std::string         stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    short             value2a;
    ASSERT_ANY_THROW(
        parser.getValue(value2a)
    );
}

TEST(JsonParserTestString, getDataFromFloat_3)
{
    std::string         stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    int             value2b;
    ASSERT_ANY_THROW(
        parser.getValue(value2b)
    );
}

TEST(JsonParserTestString, getDataFromFloat_4)
{
    std::string         stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    long             value2c;
    ASSERT_ANY_THROW(
        parser.getValue(value2c)
    );
}

TEST(JsonParserTestString, getDataFromFloat_5)
{
    std::string         stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    long long             value2d;
    ASSERT_ANY_THROW(
        parser.getValue(value2d)
    );
}

TEST(JsonParserTestString, getDataFromFloat_6)
{
    std::string         stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    unsigned short             value2e;
    ASSERT_ANY_THROW(
        parser.getValue(value2e)
    );
}

TEST(JsonParserTestString, getDataFromFloat_7)
{
    std::string         stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    unsigned int             value2f;
    ASSERT_ANY_THROW(
        parser.getValue(value2f)
    );
}

TEST(JsonParserTestString, getDataFromFloat_8)
{
    std::string         stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    unsigned long             value2g;
    ASSERT_ANY_THROW(
        parser.getValue(value2g)
    );
}

TEST(JsonParserTestString, getDataFromFloat_9)
{
    std::string         stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    unsigned long long             value2h;
    ASSERT_ANY_THROW(
        parser.getValue(value2h)
    );
}

TEST(JsonParserTestString, getDataFromFloat_a)
{
    std::string         stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    float          value3a = 0.0;
    ASSERT_NO_THROW(
        parser.getValue(value3a)
    );
    EXPECT_EQ(12356, static_cast<int>(value3a * 100 + .5));
}

TEST(JsonParserTestString, getDataFromFloat_b)
{
    std::string         stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    double          value3b = 0.0;
    ASSERT_NO_THROW(
        parser.getValue(value3b)
    );
    EXPECT_EQ(12356, static_cast<int>(value3b * 100 + .5));
}

TEST(JsonParserTestString, getDataFromFloat_c)
{
    std::string         stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    long double          value3c = 0.0;
    ASSERT_NO_THROW(
        parser.getValue(value3c)
    );
    EXPECT_EQ(12356, static_cast<int>(value3c * 100 + .5));

}

TEST(JsonParserTestString, getDataFromFloat_d)
{
    std::string         stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    bool            value4 = true;
    ASSERT_ANY_THROW(
        parser.getValue(value4)
    );
}
TEST(JsonParserTestString, getDataFromBool_1)
{
    std::string         stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    std::string     value1;
    ASSERT_ANY_THROW(
        parser.getValue(value1)
    );
}

TEST(JsonParserTestString, getDataFromBool_2)
{
    std::string         stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    std::string     value1;
    ASSERT_ANY_THROW(
        parser.getValue(value1)
    );
}

TEST(JsonParserTestString, getDataFromBool_3)
{
    std::string         stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    short             value2a = 0;
    ASSERT_ANY_THROW(
        parser.getValue(value2a)
    );
}

TEST(JsonParserTestString, getDataFromBool_4)
{
    std::string         stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    int             value2b = 0;
    ASSERT_ANY_THROW(
        parser.getValue(value2b)
    );
}

TEST(JsonParserTestString, getDataFromBool_5)
{
    std::string         stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    long             value2c = 0;
    ASSERT_ANY_THROW(
        parser.getValue(value2c)
    );
}

TEST(JsonParserTestString, getDataFromBool_6)
{
    std::string         stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    long long             value2d = 0;
    ASSERT_ANY_THROW(
        parser.getValue(value2d)
    );
}

TEST(JsonParserTestString, getDataFromBool_7)
{
    std::string         stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    unsigned short             value2e = 0;
    ASSERT_ANY_THROW(
        parser.getValue(value2e)
    );
}

TEST(JsonParserTestString, getDataFromBool_8)
{
    std::string         stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    unsigned int             value2f  = 0;
    ASSERT_ANY_THROW(
        parser.getValue(value2f)
    );
}

TEST(JsonParserTestString, getDataFromBool_9)
{
    std::string         stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    unsigned long             value2g = 0;
    ASSERT_ANY_THROW(
        parser.getValue(value2g)
    );
}

TEST(JsonParserTestString, getDataFromBool_a)
{
    std::string         stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    unsigned long long             value2h = 0;
    ASSERT_ANY_THROW(
        parser.getValue(value2h)
    );
}

TEST(JsonParserTestString, getDataFromBool_b)
{
    std::string         stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    float          value3a = 0.0;
    ASSERT_ANY_THROW(
        parser.getValue(value3a)
    );
}

TEST(JsonParserTestString, getDataFromBool_c)
{
    std::string         stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    double          value3b = 0.0;
    ASSERT_ANY_THROW(
        parser.getValue(value3b)
    );
}

TEST(JsonParserTestString, getDataFromBool_d)
{
    std::string         stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    long double          value3c = 0.0;
    ASSERT_ANY_THROW(
        parser.getValue(value3c)
    );
}

TEST(JsonParserTestString, getDataFromBool_e)
{
    std::string         stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    bool            value4 = false;
    ASSERT_NO_THROW(
        parser.getValue(value4)
    );
    EXPECT_EQ(true, value4);

    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    ASSERT_NO_THROW(
        parser.getValue(value4)
    );
    EXPECT_EQ(false, value4);
}
TEST(JsonParserTestString, getRawValue)
{
    std::string         stream(R"([true, false, 0, 15.4, "The Best"])");
    TA::JsonParser      parser(stream);
    std::string         value;

    EXPECT_EQ(ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserToken::Value,      parser.getToken());

    value = parser.getRawValue();
    EXPECT_EQ(std::string("true"), value);

    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    value = parser.getRawValue();
    EXPECT_EQ(std::string("false"), value);

    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    value = parser.getRawValue();
    EXPECT_EQ(std::string("0"), value);

    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    value = parser.getRawValue();
    EXPECT_EQ(std::string("15.4"), value);

    EXPECT_EQ(ParserToken::Value,      parser.getToken());
    value = parser.getRawValue();
    EXPECT_EQ(std::string("\"The Best\""), value);
}



