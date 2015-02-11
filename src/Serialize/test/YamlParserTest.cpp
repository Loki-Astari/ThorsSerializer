
#include "../../../config.h"
#ifdef  HAVE_YAML
#include "gtest/gtest.h"
#include "YamlParser.h"

namespace TA=ThorsAnvil::Serialize;
using TA::ParserInterface;

TEST(YamlParserTest, ArrayEmpty)
{
    std::stringstream   stream("[]");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());

    // Read past the end gets an error
    EXPECT_EQ(ParserInterface::ParserToken::Error,      parser.getToken());
}
TEST(YamlParserTest, ArrayOneValue)
{
    std::stringstream   stream("[12]");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(YamlParserTest, ArrayTwoValue)
{
    std::stringstream   stream("[12,13]");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(YamlParserTest, ArrayThreeValue)
{
    std::stringstream   stream("[12,13,14]");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(YamlParserTest, ArrayWithArray)
{
    std::stringstream   stream("[[]]");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(YamlParserTest, ArrayWithTwoArray)
{
    std::stringstream   stream("[[],[]]");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(YamlParserTest, ArrayWithMap)
{
    std::stringstream   stream("[{}]");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(YamlParserTest, ArrayWithTwoMap)
{
    std::stringstream   stream("[{},{}]");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(YamlParserTest, MapEmpty)
{
    std::stringstream   stream("{}");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(YamlParserTest, MapOneValue)
{
    std::stringstream   stream(R"({"One": 12})");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(YamlParserTest, MapTwoValue)
{
    std::stringstream   stream(R"({"one": 12, "two": 13})");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(YamlParserTest, MapThreeValue)
{
    std::stringstream   stream(R"({"one":12, "two": 13, "three": 14})");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(YamlParserTest, MapWithArray)
{
    std::stringstream   stream(R"({"one": []})");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(YamlParserTest, MapWithTwoArray)
{
    std::stringstream   stream(R"({"one": [], "two": []}])");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(YamlParserTest, MapWithMap)
{
    std::stringstream   stream(R"({"one": {}})");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(YamlParserTest, MapWithTwoMap)
{
    std::stringstream   stream(R"({"one": {}, "two": {}})");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}

// Value Test

TEST(YamlParserTest, GetKeyValue)
{
    std::stringstream   stream(R"({"one": 15})");
    TA::YamlParser      parser(stream);

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
TEST(YamlParserTest, GetArrayValues)
{
    std::stringstream   stream(R"([true, false, 123, 123.4, "A String"])");
    TA::YamlParser      parser(stream);

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
TEST(YamlParserTest, CheckErrorDoesNotRead)
{
    std::stringstream   stream("][");
    TA::YamlParser      parser(stream);
    std::cout << "1\n";
    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());

    // First Character is an error.
    std::cout << "1\n";
    EXPECT_EQ(ParserInterface::ParserToken::Error,      parser.getToken());

    // Subsequent read should also be an error.
    // But it should not read from the stream
    std::cout << "1\n";
    EXPECT_EQ(ParserInterface::ParserToken::Error,      parser.getToken());

    // char  next;
    // stream >> next;
    // EXPECT_EQ('[', next);
}

TEST(YamlParserTest, getDataFromString)
{
    std::stringstream   stream(R"(["Test"])");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    std::string     value1;
    ASSERT_NO_THROW(
        parser.getValue(value1);
    );
    EXPECT_EQ("Test", value1);

    int             value2;
    ASSERT_ANY_THROW(
        parser.getValue(value2)
    );

    double          value3;
    ASSERT_ANY_THROW(
        parser.getValue(value3)
    );

    bool            value4;
    ASSERT_ANY_THROW(
        parser.getValue(value4)
    );

    ASSERT_ANY_THROW(
        parser.getValue(nullptr)
    );
}
TEST(YamlParserTest, getDataFromInt)
{
    std::stringstream   stream(R"([56])");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    std::string     value1;
    parser.getValue(value1);

    int             value2;
    ASSERT_NO_THROW(
        parser.getValue(value2)
    );
    EXPECT_EQ(56, value2);

    double          value3;
    ASSERT_NO_THROW(
        parser.getValue(value3)
    );
    EXPECT_EQ(56, value3);

    bool            value4;
    ASSERT_ANY_THROW(
        parser.getValue(value4)
    );

    ASSERT_ANY_THROW(
        parser.getValue(nullptr)
    );
}
TEST(YamlParserTest, getDataFromFloat)
{
    std::stringstream   stream(R"([123.56])");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    std::string     value1;
    parser.getValue(value1);

    int             value2;
    ASSERT_ANY_THROW(
        parser.getValue(value2)
    );

    double          value3;
    ASSERT_NO_THROW(
        parser.getValue(value3)
    );
    EXPECT_EQ(123.56, value3);

    bool            value4;
    ASSERT_ANY_THROW(
        parser.getValue(value4)
    );

    ASSERT_ANY_THROW(
        parser.getValue(nullptr)
    );
}
TEST(YamlParserTest, getDataFromBool)
{
    std::stringstream   stream(R"([true, false])");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    std::string     value1;
    parser.getValue(value1);

    int             value2;
    ASSERT_ANY_THROW(
        parser.getValue(value2)
    );

    double          value3;
    ASSERT_ANY_THROW(
        parser.getValue(value3)
    );

    bool            value4 = false;
    ASSERT_NO_THROW(
        parser.getValue(value4)
    );
    EXPECT_EQ(true, value4);

    ASSERT_ANY_THROW(
        parser.getValue(nullptr)
    );

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    ASSERT_NO_THROW(
        parser.getValue(value4)
    );
    EXPECT_EQ(false, value4);
}
TEST(YamlParserTest, getDataFromNull)
{
    std::stringstream   stream(R"([null])");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    std::string     value1;
    parser.getValue(value1);

    int             value2;
    ASSERT_ANY_THROW(
        parser.getValue(value2)
    );

    double          value3;
    ASSERT_ANY_THROW(
        parser.getValue(value3)
    );

    bool            value4;
    ASSERT_ANY_THROW(
        parser.getValue(value4)
    );

    ASSERT_NO_THROW(
        parser.getValue(nullptr);
    );
}
TEST(YamlParserTest, getDataFromNullTilda)
{
    std::stringstream   stream(R"([~])");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    std::string     value1;
    parser.getValue(value1);

    int             value2;
    ASSERT_ANY_THROW(
        parser.getValue(value2)
    );

    double          value3;
    ASSERT_ANY_THROW(
        parser.getValue(value3)
    );

    bool            value4;
    ASSERT_ANY_THROW(
        parser.getValue(value4)
    );

    ASSERT_NO_THROW(
        parser.getValue(nullptr);
    );
}

TEST(YamlParserTest, MapAsKey)
{
    std::stringstream   stream(R"({{}:15})");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());

    ASSERT_ANY_THROW(
        parser.getToken()
    );
}

TEST(YamlParserTest, ArrayAsKey)
{
    std::stringstream   stream(R"({[]:15})");
    TA::YamlParser      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());

    ASSERT_ANY_THROW(
        parser.getToken()
    );
}

#endif

