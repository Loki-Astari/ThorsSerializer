#include "SerializeConfig.h"
#include "gtest/gtest.h"
#include "JsonParser.h"
#include "BsonParser.h"

// enum class ParserToken {Error, DocStart, DocEnd, MapStart, MapEnd, ArrayStart, ArrayEnd, Key, Value};

namespace TA=ThorsAnvil::Serialize;
using TA::ParserInterface;

TEST(ParserTest, JsonArrayEmpty)
{
    std::stringstream   stream("[]");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(ParserTest, JsonArrayOneValue)
{
    std::stringstream   stream("[12]");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(ParserTest, JsonArrayTwoValue)
{
    std::stringstream   stream("[12,13]");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(ParserTest, JsonArrayThreeValue)
{
    std::stringstream   stream("[12,13,14]");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(ParserTest, JsonArrayWithArray)
{
    std::stringstream   stream("[[]]");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(ParserTest, JsonArrayWithTwoArray)
{
    std::stringstream   stream("[[],[]]");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(ParserTest, JsonArrayWithMap)
{
    std::stringstream   stream("[{}]");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(ParserTest, JsonArrayWithTwoMap)
{
    std::stringstream   stream("[{},{}]");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(ParserTest, JsonMapEmpty)
{
    std::stringstream   stream("{}");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(ParserTest, JsonMapOneValue)
{
    std::stringstream   stream(R"({"One": 12})");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(ParserTest, JsonMapTwoValue)
{
    std::stringstream   stream(R"({"one": 12, "two": 13})");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(ParserTest, JsonMapThreeValue)
{
    std::stringstream   stream(R"({"one":12, "two": 13, "three": 14})");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(ParserTest, JsonMapWithArray)
{
    std::stringstream   stream(R"({"one": []})");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(ParserTest, JsonMapWithTwoArray)
{
    std::stringstream   stream(R"({"one": [], "two": []}])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(ParserTest, JsonMapWithMap)
{
    std::stringstream   stream(R"({"one": {}})");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(ParserTest, JsonMapWithTwoMap)
{
    std::stringstream   stream(R"({"one": {}, "two": {}})");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(ParserTest, JsonGetKeyValue)
{
    std::stringstream   stream(R"({"one": 15})");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());

    std::string key     = parser.getKey();
    EXPECT_EQ("one", key);

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    int value;
    parser.getValue(value);
    EXPECT_EQ(15, value);

    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(ParserTest, JsonGetArrayValues)
{
    std::stringstream   stream(R"([true, false, 123, 123.4, "A String"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    bool    test1   = false;
    parser.getValue(test1);
    EXPECT_EQ(true, test1);

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    bool    test2   = true;
    parser.getValue(test2);
    EXPECT_EQ(false, test2);

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    int    test3   = 0;
    parser.getValue(test3);
    EXPECT_EQ(123, test3);

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    double test4   = 80;
    parser.getValue(test4);
    EXPECT_EQ(1234, (int)(test4*10));

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    std::string    test5;
    parser.getValue(test5);
    EXPECT_EQ("A String", test5);


    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(ParserTest, JsonCheckErrorDoesNotRead)
{
    std::stringstream   stream("][");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());

    // First Character is an error.
    EXPECT_EQ(ParserInterface::ParserToken::Error,      parser.getToken());

    // Subsequent read should also be an error.
    // But it should not read from the stream
    EXPECT_EQ(ParserInterface::ParserToken::Error,      parser.getToken());

    char  next;
    stream >> next;
    EXPECT_EQ('[', next);
}

TEST(ParserTest, JsongetDataFromString_1)
{
    std::stringstream   stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    std::string     value1;
    ASSERT_NO_THROW(
        parser.getValue(value1);
    );
    EXPECT_EQ("Test", value1);
}

TEST(ParserTest, JsongetDataFromString_2)
{
    std::stringstream   stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    short             value2a;
    ASSERT_ANY_THROW(
        parser.getValue(value2a)
    );
}

TEST(ParserTest, JsongetDataFromString_3)
{
    std::stringstream   stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    int             value2b;
    ASSERT_ANY_THROW(
        parser.getValue(value2b)
    );
}

TEST(ParserTest, JsongetDataFromString_4)
{
    std::stringstream   stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    long             value2c;
    ASSERT_ANY_THROW(
        parser.getValue(value2c)
    );
}

TEST(ParserTest, JsongetDataFromString_5)
{
    std::stringstream   stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    long long             value2d;
    ASSERT_ANY_THROW(
        parser.getValue(value2d)
    );
}

TEST(ParserTest, JsongetDataFromString_6)
{
    std::stringstream   stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    unsigned short             value2e;
    ASSERT_ANY_THROW(
        parser.getValue(value2e)
    );
}

TEST(ParserTest, JsongetDataFromString_7)
{
    std::stringstream   stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    unsigned int             value2f;
    ASSERT_ANY_THROW(
        parser.getValue(value2f)
    );
}

TEST(ParserTest, JsongetDataFromString_8)
{
    std::stringstream   stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    unsigned long             value2g;
    ASSERT_ANY_THROW(
        parser.getValue(value2g)
    );
}

TEST(ParserTest, JsongetDataFromString_9)
{
    std::stringstream   stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    unsigned long long             value2h;
    ASSERT_ANY_THROW(
        parser.getValue(value2h)
    );

}

TEST(ParserTest, JsongetDataFromString_a)
{
    std::stringstream   stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    float          value3a;
    ASSERT_ANY_THROW(
        parser.getValue(value3a)
    );
}

TEST(ParserTest, JsongetDataFromString_b)
{
    std::stringstream   stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    double          value3b;
    ASSERT_ANY_THROW(
        parser.getValue(value3b)
    );
}

TEST(ParserTest, JsongetDataFromString_c)
{
    std::stringstream   stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
}

TEST(ParserTest, JsongetDataFromString_d)
{
    std::stringstream   stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    long double          value3c;
    ASSERT_ANY_THROW(
        parser.getValue(value3c)
    );

}

TEST(ParserTest, JsongetDataFromString_e)
{
    std::stringstream   stream(R"(["Test"])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    bool            value4;
    ASSERT_ANY_THROW(
        parser.getValue(value4)
    );
}

TEST(ParserTest, JsongetDataFromInt_1)
{
    std::stringstream   stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    std::string     value1;
    ASSERT_ANY_THROW(
        parser.getValue(value1)
    );
}

TEST(ParserTest, JsongetDataFromInt_2)
{
    std::stringstream   stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    short             value2a;
    ASSERT_NO_THROW(
        parser.getValue(value2a)
    );
    EXPECT_EQ(56, value2a);
}

TEST(ParserTest, JsongetDataFromInt_3)
{
    std::stringstream   stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    int             value2b;
    ASSERT_NO_THROW(
        parser.getValue(value2b)
    );
    EXPECT_EQ(56, value2b);
}

TEST(ParserTest, JsongetDataFromInt_4)
{
    std::stringstream   stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    long             value2c;
    ASSERT_NO_THROW(
        parser.getValue(value2c)
    );
    EXPECT_EQ(56, value2c);
}

TEST(ParserTest, JsongetDataFromInt_5)
{
    std::stringstream   stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    long long             value2d;
    ASSERT_NO_THROW(
        parser.getValue(value2d)
    );
    EXPECT_EQ(56, value2d);
}

TEST(ParserTest, JsongetDataFromInt_6)
{
    std::stringstream   stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    short             value2e;
    ASSERT_NO_THROW(
        parser.getValue(value2e)
    );
    EXPECT_EQ(56, value2e);
}

TEST(ParserTest, JsongetDataFromInt_7)
{
    std::stringstream   stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    int             value2f;
    ASSERT_NO_THROW(
        parser.getValue(value2f)
    );
    EXPECT_EQ(56, value2f);
}

TEST(ParserTest, JsongetDataFromInt_8)
{
    std::stringstream   stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    long             value2g;
    ASSERT_NO_THROW(
        parser.getValue(value2g)
    );
    EXPECT_EQ(56, value2g);
}

TEST(ParserTest, JsongetDataFromInt_9)
{
    std::stringstream   stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    long long             value2h;
    ASSERT_NO_THROW(
        parser.getValue(value2h)
    );
    EXPECT_EQ(56, value2h);
}

TEST(ParserTest, JsongetDataFromInt_a)
{
    std::stringstream   stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    float          value3a;
    ASSERT_NO_THROW(
        parser.getValue(value3a)
    );
    EXPECT_EQ(56, value3a);
}

TEST(ParserTest, JsongetDataFromInt_b)
{
    std::stringstream   stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    double          value3b;
    ASSERT_NO_THROW(
        parser.getValue(value3b)
    );
    EXPECT_EQ(56, value3b);
}

TEST(ParserTest, JsongetDataFromInt_c)
{
    std::stringstream   stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    long double          value3c;
    ASSERT_NO_THROW(
        parser.getValue(value3c)
    );
    EXPECT_EQ(56, value3c);
}

TEST(ParserTest, JsongetDataFromInt_d)
{
    std::stringstream   stream(R"([56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    bool            value4;
    ASSERT_ANY_THROW(
        parser.getValue(value4)
    );
}

TEST(ParserTest, JsongetDataFromFloat_1)
{
    std::stringstream   stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    std::string     value1;
    ASSERT_ANY_THROW(
        parser.getValue(value1)
    );
}

TEST(ParserTest, JsongetDataFromFloat_2)
{
    std::stringstream   stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    short             value2a;
    ASSERT_ANY_THROW(
        parser.getValue(value2a)
    );
}

TEST(ParserTest, JsongetDataFromFloat_3)
{
    std::stringstream   stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    int             value2b;
    ASSERT_ANY_THROW(
        parser.getValue(value2b)
    );
}

TEST(ParserTest, JsongetDataFromFloat_4)
{
    std::stringstream   stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    long             value2c;
    ASSERT_ANY_THROW(
        parser.getValue(value2c)
    );
}

TEST(ParserTest, JsongetDataFromFloat_5)
{
    std::stringstream   stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    long long             value2d;
    ASSERT_ANY_THROW(
        parser.getValue(value2d)
    );
}

TEST(ParserTest, JsongetDataFromFloat_6)
{
    std::stringstream   stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    unsigned short             value2e;
    ASSERT_ANY_THROW(
        parser.getValue(value2e)
    );
}

TEST(ParserTest, JsongetDataFromFloat_7)
{
    std::stringstream   stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    unsigned int             value2f;
    ASSERT_ANY_THROW(
        parser.getValue(value2f)
    );
}

TEST(ParserTest, JsongetDataFromFloat_8)
{
    std::stringstream   stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    unsigned long             value2g;
    ASSERT_ANY_THROW(
        parser.getValue(value2g)
    );
}

TEST(JsonParserTest, getDataFromFloat_9)
{
    std::stringstream   stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    unsigned long long             value2h;
    ASSERT_ANY_THROW(
        parser.getValue(value2h)
    );
}

TEST(JsonParserTest, getDataFromFloat_a)
{
    std::stringstream   stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    float          value3a;
    ASSERT_NO_THROW(
        parser.getValue(value3a)
    );
    EXPECT_EQ(12356, static_cast<int>(value3a * 100 + .5));
}

TEST(ParserTest, JsongetDataFromFloat_b)
{
    std::stringstream   stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    double          value3b;
    ASSERT_NO_THROW(
        parser.getValue(value3b)
    );
    EXPECT_EQ(12356, static_cast<int>(value3b * 100 + .5));
}

TEST(ParserTest, JsongetDataFromFloat_c)
{
    std::stringstream   stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    long double          value3c;
    ASSERT_NO_THROW(
        parser.getValue(value3c)
    );
    EXPECT_EQ(12356, static_cast<int>(value3c * 100 + .5));

}

TEST(ParserTest, JsongetDataFromFloat_d)
{
    std::stringstream   stream(R"([123.56])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    bool            value4;
    ASSERT_ANY_THROW(
        parser.getValue(value4)
    );
}
TEST(ParserTest, JsongetDataFromBool_1)
{
    std::stringstream   stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    std::string     value1;
    ASSERT_ANY_THROW(
        parser.getValue(value1)
    );
}

TEST(ParserTest, JsongetDataFromBool_2)
{
    std::stringstream   stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    std::string     value1;
    ASSERT_ANY_THROW(
        parser.getValue(value1)
    );
}

TEST(ParserTest, JsongetDataFromBool_3)
{
    std::stringstream   stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    short             value2a;
    ASSERT_ANY_THROW(
        parser.getValue(value2a)
    );
}

TEST(ParserTest, JsongetDataFromBool_4)
{
    std::stringstream   stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    int             value2b;
    ASSERT_ANY_THROW(
        parser.getValue(value2b)
    );
}

TEST(ParserTest, JsongetDataFromBool_5)
{
    std::stringstream   stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    long             value2c;
    ASSERT_ANY_THROW(
        parser.getValue(value2c)
    );
}

TEST(ParserTest, JsongetDataFromBool_6)
{
    std::stringstream   stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    long long             value2d;
    ASSERT_ANY_THROW(
        parser.getValue(value2d)
    );
}

TEST(ParserTest, JsongetDataFromBool_7)
{
    std::stringstream   stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    unsigned short             value2e;
    ASSERT_ANY_THROW(
        parser.getValue(value2e)
    );
}

TEST(ParserTest, JsongetDataFromBool_8)
{
    std::stringstream   stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    unsigned int             value2f;
    ASSERT_ANY_THROW(
        parser.getValue(value2f)
    );
}

TEST(ParserTest, JsongetDataFromBool_9)
{
    std::stringstream   stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    unsigned long             value2g;
    ASSERT_ANY_THROW(
        parser.getValue(value2g)
    );
}

TEST(ParserTest, JsongetDataFromBool_a)
{
    std::stringstream   stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    unsigned long long             value2h;
    ASSERT_ANY_THROW(
        parser.getValue(value2h)
    );
}

TEST(ParserTest, JsongetDataFromBool_b)
{
    std::stringstream   stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    float          value3a;
    ASSERT_ANY_THROW(
        parser.getValue(value3a)
    );
}

TEST(ParserTest, JsongetDataFromBool_c)
{
    std::stringstream   stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    double          value3b;
    ASSERT_ANY_THROW(
        parser.getValue(value3b)
    );
}

TEST(ParserTest, JsongetDataFromBool_d)
{
    std::stringstream   stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    long double          value3c;
    ASSERT_ANY_THROW(
        parser.getValue(value3c)
    );
}

TEST(ParserTest, JsongetDataFromBool_e)
{
    std::stringstream   stream(R"([true, false])");
    TA::JsonParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    bool            value4 = false;
    ASSERT_NO_THROW(
        parser.getValue(value4)
    );
    EXPECT_EQ(true, value4);

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    ASSERT_NO_THROW(
        parser.getValue(value4)
    );
    EXPECT_EQ(false, value4);
}
TEST(ParserTest, JsongetRawValue)
{
    std::stringstream   stream(R"([true, false, 0, 15.4, "The Best"])");
    TA::JsonParser      parser(stream);
    std::string         value;

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    value = parser.getRawValue();
    EXPECT_EQ(std::string("true"), value);

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    value = parser.getRawValue();
    EXPECT_EQ(std::string("false"), value);

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    value = parser.getRawValue();
    EXPECT_EQ(std::string("0"), value);

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    value = parser.getRawValue();
    EXPECT_EQ(std::string("15.4"), value);

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    value = parser.getRawValue();
    EXPECT_EQ(std::string("\"The Best\""), value);
}



TEST(ParserTest, BsonArrayEmpty)
{
    //std::stringstream   stream("[]");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x05\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser          parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(ParserTest, BsonArrayOneValue)
{
    //std::stringstream   stream("[12]");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x10"  "0\x00"  "\x0C\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(ParserTest, BsonArrayTwoValue)
{
    //std::stringstream   stream("[12,13]");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x13\x00\x00\x00"
                  "\x10"  "0\x00"  "\x0C\x00\x00\x00"
                  "\x10"  "1\x00"  "\x0D\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(ParserTest, BsonArrayThreeValue)
{
    //std::stringstream   stream("[12,13,14]");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x1A\x00\x00\x00"
                  "\x10"  "0\x00"  "\x0C\x00\x00\x00"
                  "\x10"  "1\x00"  "\x0D\x00\x00\x00"
                  "\x10"  "2\x00"  "\x0E\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(ParserTest, BsonArrayWithArray)
{
    //std::stringstream   stream("[[]]");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0D\x00\x00\x00"
                  "\x04"  "0\x00"
                        "\x05\x00\x00\x00"
                        "\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(ParserTest, BsonArrayWithTwoArray)
{
    //std::stringstream   stream("[[],[]]");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x15\x00\x00\x00"
                  "\x04"  "0\x00"
                        "\x05\x00\x00\x00"
                        "\x00"
                  "\x04"  "1\x00"
                        "\x05\x00\x00\x00"
                        "\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(ParserTest, BsonArrayWithMap)
{
    //std::stringstream   stream("[{}]");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0D\x00\x00\x00"
                  "\x03"  "0\x00"
                        "\x05\x00\x00\x00"
                        "\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(ParserTest, BsonArrayWithTwoMap)
{
    //std::stringstream   stream("[{},{}]");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x15\x00\x00\x00"
                  "\x03"  "0\x00"
                        "\x05\x00\x00\x00"
                        "\x00"
                  "\x03"  "1\x00"
                        "\x05\x00\x00\x00"
                        "\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(ParserTest, BsonMapEmpty)
{
    //std::stringstream   stream("{}");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x05\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(ParserTest, BsonMapOneValue)
{
    //std::stringstream   stream(R"({"One": 12})");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0E\x00\x00\x00"
                  "\x10" "One\x00" "\x0C\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(ParserTest, BsonMapTwoValue)
{
    //std::stringstream   stream(R"({"one": 12, "two": 13})");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x17\x00\x00\x00"
                  "\x10" "One\x00" "\x0C\x00\x00\x00"
                  "\x10" "Two\x00" "\x0D\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(ParserTest, BsonMapThreeValue)
{
    //std::stringstream   stream(R"({"one":12, "two": 13, "three": 14})");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x22\x00\x00\x00"
                  "\x10" "One\x00" "\x0C\x00\x00\x00"
                  "\x10" "Two\x00" "\x0D\x00\x00\x00"
                  "\x10" "Three\x00" "\x0E\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(ParserTest, BsonMapWithArray)
{
    //std::stringstream   stream(R"({"one": []})");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0F\x00\x00\x00"
                  "\x04" "one\x00"
                        "\x05\x00\x00\x00"
                        "\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(ParserTest, BsonMapWithTwoArray)
{
    //std::stringstream   stream(R"({"one": [], "two": []}])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x19\x00\x00\x00"
                  "\x04" "one\x00"
                        "\x05\x00\x00\x00"
                        "\x00"
                  "\x04" "two\x00"
                        "\x05\x00\x00\x00"
                        "\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(ParserTest, BsonMapWithMap)
{
    //std::stringstream   stream(R"({"one": {}})");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0F\x00\x00\x00"
                  "\x03" "one\x00"
                        "\x05\x00\x00\x00"
                        "\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(ParserTest, BsonMapWithTwoMap)
{
    //std::stringstream   stream(R"({"one": {}, "two": {}})");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x19\x00\x00\x00"
                  "\x03" "one\x00"
                        "\x05\x00\x00\x00"
                        "\x00"
                  "\x03" "two\x00"
                        "\x05\x00\x00\x00"
                        "\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    parser.ignoreDataValue();
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(ParserTest, BsonGetKeyValue)
{
    //std::stringstream   stream(R"({"one": 15})");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0E\x00\x00\x00"
                  "\x10" "one\x00" "\x0F\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());

    std::string key     = parser.getKey();
    EXPECT_EQ("one", key);

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    int value;
    parser.getValue(value);
    EXPECT_EQ(15, value);

    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(ParserTest, BsonGetArrayValues)
{
    //std::stringstream   stream(R"([true, false, 123, 123.4, "A String"])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x2F\x00\x00\x00"
                  "\x08" "0\x00" "\x01"
                  "\x08" "1\x00" "\x00"
                  "\x10" "2\x00" "\x7B\x00\x00\x00"
                  "\x01" "3\x00" "\x9A\x99\x99\x99\x99\xD9\x5E\x40"
                  "\x02" "4\x00" "\x09\x00\x00\x00" "A String\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    bool    test1   = false;
    parser.getValue(test1);
    EXPECT_EQ(true, test1);

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    bool    test2   = true;
    parser.getValue(test2);
    EXPECT_EQ(false, test2);

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    int    test3   = 0;
    parser.getValue(test3);
    EXPECT_EQ(123, test3);

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    double test4   = 80;
    parser.getValue(test4);
    EXPECT_EQ(1234, (int)(test4*10));

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    std::string    test5;
    parser.getValue(test5);
    EXPECT_EQ("A String", test5);


    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}

TEST(ParserTest, BsongetDataFromString_1)
{
    //std::stringstream   stream(R"(["Test"])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x11\x00\x00\x00"
                  "\x02" "0\x00" "\x05\x00\x00\x00" "Test\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    std::string     value1;
    ASSERT_NO_THROW(
        parser.getValue(value1);
    );
    EXPECT_EQ("Test", value1);
}

TEST(ParserTest, BsongetDataFromString_2)
{
    //std::stringstream   stream(R"(["Test"])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x13\x00\x00\x00"
                  "\x02" "0\x00" "\x05\x00\x00\x00" "Test\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    short             value2a;
    ASSERT_ANY_THROW(
        parser.getValue(value2a)
    );
}

TEST(ParserTest, BsongetDataFromString_3)
{
    //std::stringstream   stream(R"(["Test"])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x11\x00\x00\x00"
                  "\x02" "0\x00" "\x05\x00\x00\x00" "Test\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    int             value2b;
    ASSERT_ANY_THROW(
        parser.getValue(value2b)
    );
}

TEST(ParserTest, BsongetDataFromString_4)
{
    //std::stringstream   stream(R"(["Test"])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x11\x00\x00\x00"
                  "\x02" "0\x00" "\x05\x00\x00\x00" "Test\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    long             value2c;
    ASSERT_ANY_THROW(
        parser.getValue(value2c)
    );
}

TEST(ParserTest, BsongetDataFromString_5)
{
    //std::stringstream   stream(R"(["Test"])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x11\x00\x00\x00"
                  "\x02" "0\x00" "\x05\x00\x00\x00" "Test\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    long long             value2d;
    ASSERT_ANY_THROW(
        parser.getValue(value2d)
    );
}

TEST(ParserTest, BsongetDataFromString_6)
{
    //std::stringstream   stream(R"(["Test"])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x11\x00\x00\x00"
                  "\x02" "0\x00" "\x05\x00\x00\x00" "Test\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    unsigned short             value2e;
    ASSERT_ANY_THROW(
        parser.getValue(value2e)
    );
}

TEST(ParserTest, BsongetDataFromString_7)
{
    //std::stringstream   stream(R"(["Test"])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x11\x00\x00\x00"
                  "\x02" "0\x00" "\x05\x00\x00\x00" "Test\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    unsigned int             value2f;
    ASSERT_ANY_THROW(
        parser.getValue(value2f)
    );
}

TEST(ParserTest, BsongetDataFromString_8)
{
    //std::stringstream   stream(R"(["Test"])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x11\x00\x00\x00"
                  "\x02" "0\x00" "\x05\x00\x00\x00" "Test\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    unsigned long             value2g;
    ASSERT_ANY_THROW(
        parser.getValue(value2g)
    );
}

TEST(ParserTest, BsongetDataFromString_9)
{
    //std::stringstream   stream(R"(["Test"])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x11\x00\x00\x00"
                  "\x02" "0\x00" "\x05\x00\x00\x00" "Test\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    unsigned long long             value2h;
    ASSERT_ANY_THROW(
        parser.getValue(value2h)
    );

}

TEST(ParserTest, BsongetDataFromString_a)
{
    //std::stringstream   stream(R"(["Test"])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x11\x00\x00\x00"
                  "\x02" "0\x00" "\x05\x00\x00\x00" "Test\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    float          value3a;
    ASSERT_ANY_THROW(
        parser.getValue(value3a)
    );
}

TEST(ParserTest, BsongetDataFromString_b)
{
    //std::stringstream   stream(R"(["Test"])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x11\x00\x00\x00"
                  "\x02" "0\x00" "\x05\x00\x00\x00" "Test\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    double          value3b;
    ASSERT_ANY_THROW(
        parser.getValue(value3b)
    );
}

TEST(ParserTest, BsongetDataFromString_c)
{
    //std::stringstream   stream(R"(["Test"])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x11\x00\x00\x00"
                  "\x02" "0\x00" "\x05\x00\x00\x00" "Test\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
}

TEST(ParserTest, BsongetDataFromString_d)
{
    //std::stringstream   stream(R"(["Test"])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x11\x00\x00\x00"
                  "\x02" "0\x00" "\x05\x00\x00\x00" "Test\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    long double          value3c;
    ASSERT_ANY_THROW(
        parser.getValue(value3c)
    );

}

TEST(ParserTest, BsongetDataFromString_e)
{
    //std::stringstream   stream(R"(["Test"])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x11\x00\x00\x00"
                  "\x02" "0\x00" "\x05\x00\x00\x00" "Test\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    bool            value4;
    ASSERT_ANY_THROW(
        parser.getValue(value4)
    );
}

TEST(ParserTest, BsongetDataFromInt_1)
{
    //std::stringstream   stream(R"([56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x10" "0\x00" "\x38\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    std::string     value1;
    ASSERT_ANY_THROW(
        parser.getValue(value1)
    );
}

TEST(ParserTest, BsongetDataFromInt_2)
{
    //std::stringstream   stream(R"([56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x10" "0\x00" "\x38\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    short             value2a;
    ASSERT_NO_THROW(
        parser.getValue(value2a)
    );
    EXPECT_EQ(56, value2a);
}

TEST(ParserTest, BsongetDataFromInt_3)
{
    //std::stringstream   stream(R"([56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x10" "0\x00" "\x38\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    int             value2b;
    ASSERT_NO_THROW(
        parser.getValue(value2b)
    );
    EXPECT_EQ(56, value2b);
}

TEST(ParserTest, BsongetDataFromInt_4)
{
    //std::stringstream   stream(R"([56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x10" "0\x00" "\x38\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    long             value2c;
    ASSERT_NO_THROW(
        parser.getValue(value2c)
    );
    EXPECT_EQ(56, value2c);
}

TEST(ParserTest, BsongetDataFromInt_5)
{
    //std::stringstream   stream(R"([56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x10" "0\x00" "\x38\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    long long             value2d;
    ASSERT_NO_THROW(
        parser.getValue(value2d)
    );
    EXPECT_EQ(56, value2d);
}

TEST(ParserTest, BsongetDataFromInt_6)
{
    //std::stringstream   stream(R"([56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x10" "0\x00" "\x38\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    short             value2e;
    ASSERT_NO_THROW(
        parser.getValue(value2e)
    );
    EXPECT_EQ(56, value2e);
}

TEST(ParserTest, BsongetDataFromInt_7)
{
    //std::stringstream   stream(R"([56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x10" "0\x00" "\x38\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    int             value2f;
    ASSERT_NO_THROW(
        parser.getValue(value2f)
    );
    EXPECT_EQ(56, value2f);
}

TEST(ParserTest, BsongetDataFromInt_8)
{
    //std::stringstream   stream(R"([56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x10" "0\x00" "\x38\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    long             value2g;
    ASSERT_NO_THROW(
        parser.getValue(value2g)
    );
    EXPECT_EQ(56, value2g);
}

TEST(ParserTest, BsongetDataFromInt_9)
{
    //std::stringstream   stream(R"([56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x10" "0\x00" "\x38\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    long long             value2h;
    ASSERT_NO_THROW(
        parser.getValue(value2h)
    );
    EXPECT_EQ(56, value2h);
}

TEST(ParserTest, BsongetDataFromInt_a)
{
    //std::stringstream   stream(R"([56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x10" "0\x00" "\x38\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    float          value3a;
    ASSERT_NO_THROW(
        parser.getValue(value3a)
    );
    EXPECT_EQ(56, value3a);
}

TEST(ParserTest, BsongetDataFromInt_b)
{
    //std::stringstream   stream(R"([56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x10" "0\x00" "\x38\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    double          value3b;
    ASSERT_NO_THROW(
        parser.getValue(value3b)
    );
    EXPECT_EQ(56, value3b);
}

TEST(ParserTest, BsongetDataFromInt_c)
{
    //std::stringstream   stream(R"([56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x10" "0\x00" "\x38\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    long double          value3c;
    ASSERT_NO_THROW(
        parser.getValue(value3c)
    );
    EXPECT_EQ(56, value3c);
}

TEST(ParserTest, BsongetDataFromInt_d)
{
    //std::stringstream   stream(R"([56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x10" "0\x00" "\x38\x00\x00\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    bool            value4;
    ASSERT_ANY_THROW(
        parser.getValue(value4)
    );
}

TEST(ParserTest, BsongetDataFromFloat_1)
{
    //std::stringstream   stream(R"([123.56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x01" "0\x00" "\xA4\x70\x3D\x0A\xD7\xE3\x5E\x40"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    std::string     value1;
    ASSERT_ANY_THROW(
        parser.getValue(value1)
    );
}

TEST(ParserTest, BsongetDataFromFloat_2)
{
    //std::stringstream   stream(R"([123.56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x01" "0\x00" "\xA4\x70\x3D\x0A\xD7\xE3\x5E\x40"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    short             value2a;
    ASSERT_ANY_THROW(
        parser.getValue(value2a)
    );
}

TEST(ParserTest, BsongetDataFromFloat_3)
{
    //std::stringstream   stream(R"([123.56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x01" "0\x00" "\xA4\x70\x3D\x0A\xD7\xE3\x5E\x40"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    int             value2b;
    ASSERT_ANY_THROW(
        parser.getValue(value2b)
    );
}

TEST(ParserTest, BsongetDataFromFloat_4)
{
    //std::stringstream   stream(R"([123.56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x01" "0\x00" "\xA4\x70\x3D\x0A\xD7\xE3\x5E\x40"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    long             value2c;
    ASSERT_ANY_THROW(
        parser.getValue(value2c)
    );
}

TEST(ParserTest, BsongetDataFromFloat_5)
{
    //std::stringstream   stream(R"([123.56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x01" "0\x00" "\xA4\x70\x3D\x0A\xD7\xE3\x5E\x40"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    long long             value2d;
    ASSERT_ANY_THROW(
        parser.getValue(value2d)
    );
}

TEST(ParserTest, BsongetDataFromFloat_6)
{
    //std::stringstream   stream(R"([123.56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x01" "0\x00" "\xA4\x70\x3D\x0A\xD7\xE3\x5E\x40"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    unsigned short             value2e;
    ASSERT_ANY_THROW(
        parser.getValue(value2e)
    );
}

TEST(ParserTest, BsongetDataFromFloat_7)
{
    //std::stringstream   stream(R"([123.56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x01" "0\x00" "\xA4\x70\x3D\x0A\xD7\xE3\x5E\x40"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    unsigned int             value2f;
    ASSERT_ANY_THROW(
        parser.getValue(value2f)
    );
}

TEST(ParserTest, BsongetDataFromFloat_8)
{
    //std::stringstream   stream(R"([123.56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x01" "0\x00" "\xA4\x70\x3D\x0A\xD7\xE3\x5E\x40"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    unsigned long             value2g;
    ASSERT_ANY_THROW(
        parser.getValue(value2g)
    );
}

TEST(ParserTest, BsongetDataFromFloat_9)
{
    //std::stringstream   stream(R"([123.56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x01" "0\x00" "\xA4\x70\x3D\x0A\xD7\xE3\x5E\x40"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    unsigned long long             value2h;
    ASSERT_ANY_THROW(
        parser.getValue(value2h)
    );
}

TEST(ParserTest, BsongetDataFromFloat_a)
{
    //std::stringstream   stream(R"([123.56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x01" "0\x00" "\xA4\x70\x3D\x0A\xD7\xE3\x5E\x40"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    float          value3a;
    ASSERT_NO_THROW(
        parser.getValue(value3a)
    );
    EXPECT_EQ(12356, static_cast<int>(value3a * 100 + .5));
}

TEST(ParserTest, BsongetDataFromFloat_b)
{
    //std::stringstream   stream(R"([123.56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x01" "0\x00" "\xA4\x70\x3D\x0A\xD7\xE3\x5E\x40"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    double          value3b;
    ASSERT_NO_THROW(
        parser.getValue(value3b)
    );
    EXPECT_EQ(12356, static_cast<int>(value3b * 100 + .5));
}

TEST(ParserTest, BsongetDataFromFloat_c)
{
    //std::stringstream   stream(R"([123.56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x01" "0\x00" "\xA4\x70\x3D\x0A\xD7\xE3\x5E\x40"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    long double          value3c;
    ASSERT_NO_THROW(
        parser.getValue(value3c)
    );
    EXPECT_EQ(12356, static_cast<int>(value3c * 100 + .5));

}

TEST(ParserTest, BsongetDataFromFloat_d)
{
    //std::stringstream   stream(R"([123.56])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0C\x00\x00\x00"
                  "\x01" "0\x00" "\xA4\x70\x3D\x0A\xD7\xE3\x5E\x40"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    bool            value4;
    ASSERT_ANY_THROW(
        parser.getValue(value4)
    );
}
TEST(ParserTest, BsongetDataFromBool_1)
{
    //std::stringstream   stream(R"([true, false])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0D\x00\x00\x00"
                  "\x08" "0\x00" "\x01"
                  "\x08" "1\x00" "\x02"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    std::string     value1;
    ASSERT_ANY_THROW(
        parser.getValue(value1)
    );
}

TEST(ParserTest, BsongetDataFromBool_2)
{
    //std::stringstream   stream(R"([true, false])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0D\x00\x00\x00"
                  "\x08" "0\x00" "\x01"
                  "\x08" "1\x00" "\x02"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    std::string     value1;
    ASSERT_ANY_THROW(
        parser.getValue(value1)
    );
}

TEST(ParserTest, BsongetDataFromBool_3)
{
    //std::stringstream   stream(R"([true, false])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0D\x00\x00\x00"
                  "\x08" "0\x00" "\x01"
                  "\x08" "1\x00" "\x02"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    short             value2a;
    ASSERT_ANY_THROW(
        parser.getValue(value2a)
    );
}

TEST(ParserTest, BsongetDataFromBool_4)
{
    //std::stringstream   stream(R"([true, false])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0D\x00\x00\x00"
                  "\x08" "0\x00" "\x01"
                  "\x08" "1\x00" "\x02"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    int             value2b;
    ASSERT_ANY_THROW(
        parser.getValue(value2b)
    );
}

TEST(ParserTest, BsongetDataFromBool_5)
{
    //std::stringstream   stream(R"([true, false])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0D\x00\x00\x00"
                  "\x08" "0\x00" "\x01"
                  "\x08" "1\x00" "\x02"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    long             value2c;
    ASSERT_ANY_THROW(
        parser.getValue(value2c)
    );
}

TEST(ParserTest, BsongetDataFromBool_6)
{
    //std::stringstream   stream(R"([true, false])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0D\x00\x00\x00"
                  "\x08" "0\x00" "\x01"
                  "\x08" "1\x00" "\x02"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    long long             value2d;
    ASSERT_ANY_THROW(
        parser.getValue(value2d)
    );
}

TEST(ParserTest, BsongetDataFromBool_7)
{
    //std::stringstream   stream(R"([true, false])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0D\x00\x00\x00"
                  "\x08" "0\x00" "\x01"
                  "\x08" "1\x00" "\x02"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    unsigned short             value2e;
    ASSERT_ANY_THROW(
        parser.getValue(value2e)
    );
}

TEST(ParserTest, BsongetDataFromBool_8)
{
    //std::stringstream   stream(R"([true, false])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0D\x00\x00\x00"
                  "\x08" "0\x00" "\x01"
                  "\x08" "1\x00" "\x02"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    unsigned int             value2f;
    ASSERT_ANY_THROW(
        parser.getValue(value2f)
    );
}

TEST(ParserTest, BsongetDataFromBool_9)
{
    //std::stringstream   stream(R"([true, false])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0D\x00\x00\x00"
                  "\x08" "0\x00" "\x01"
                  "\x08" "1\x00" "\x02"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    unsigned long             value2g;
    ASSERT_ANY_THROW(
        parser.getValue(value2g)
    );
}

TEST(ParserTest, BsongetDataFromBool_a)
{
    //std::stringstream   stream(R"([true, false])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0D\x00\x00\x00"
                  "\x08" "0\x00" "\x01"
                  "\x08" "1\x00" "\x02"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    unsigned long long             value2h;
    ASSERT_ANY_THROW(
        parser.getValue(value2h)
    );
}

TEST(ParserTest, BsongetDataFromBool_b)
{
    //std::stringstream   stream(R"([true, false])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0D\x00\x00\x00"
                  "\x08" "0\x00" "\x01"
                  "\x08" "1\x00" "\x02"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    float          value3a;
    ASSERT_ANY_THROW(
        parser.getValue(value3a)
    );
}

TEST(ParserTest, BsongetDataFromBool_c)
{
    //std::stringstream   stream(R"([true, false])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0D\x00\x00\x00"
                  "\x08" "0\x00" "\x01"
                  "\x08" "1\x00" "\x02"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    double          value3b;
    ASSERT_ANY_THROW(
        parser.getValue(value3b)
    );
}

TEST(ParserTest, BsongetDataFromBool_d)
{
    //std::stringstream   stream(R"([true, false])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0D\x00\x00\x00"
                  "\x08" "0\x00" "\x01"
                  "\x08" "1\x00" "\x02"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    long double          value3c;
    ASSERT_ANY_THROW(
        parser.getValue(value3c)
    );
}

TEST(ParserTest, BsongetDataFromBool_e)
{
    //std::stringstream   stream(R"([true, false])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x0D\x00\x00\x00"
                  "\x08" "0\x00" "\x01"
                  "\x08" "1\x00" "\x02"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    bool            value4 = false;
    ASSERT_NO_THROW(
        parser.getValue(value4)
    );
    EXPECT_EQ(true, value4);

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    ASSERT_NO_THROW(
        parser.getValue(value4)
    );
    EXPECT_EQ(false, value4);
}
TEST(ParserTest, BsongetRawValue)
{
    //std::stringstream   stream(R"([true, false, 0, 15.4, "The Best"])");
    using ParserConfig = ParserInterface::ParserConfig;
    static const char inputRaw[]
                = "\x2F\x00\x00\x00"
                  "\x08" "0\x00" "\x01"
                  "\x08" "1\x00" "\x02"
                  "\x10" "2\x00" "\x00\x00\x00\x00"
                  "\x01" "3\x00" "\xCD\xCC\xCC\xCC\xCC\xCC\x2E\x40"
                  "\x02" "4\x00" "\x09\x00\x00\x00" "The Best\x00"
                  "\x00";
    std::string input(std::begin(inputRaw), std::end(inputRaw) - 1);
    std::stringstream   stream(input);
    ParserConfig        config;
    config.parserInfo   = static_cast<long>(ThorsAnvil::Serialize::BsonContainer::Array);
    TA::BsonParser      parser(stream, config);
    std::string         value;

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    value = parser.getRawValue();
    EXPECT_EQ(std::string("true"), value);

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    value = parser.getRawValue();
    EXPECT_EQ(std::string("false"), value);

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    value = parser.getRawValue();
    EXPECT_EQ(std::string("0"), value);

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    value = parser.getRawValue();
    EXPECT_EQ(std::string("15.4"), value.substr(0,4));

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    value = parser.getRawValue();
    EXPECT_EQ(std::string("\"The Best\""), value);
}


