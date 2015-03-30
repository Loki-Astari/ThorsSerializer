#include "../../config.h"
#ifdef NETWORK_BYTE_ORDER

#include "gtest/gtest.h"
#include "BinaryParser.h"
#include "SerUtil.h"
#include "test/BinaryParserTest.h"

namespace TA=ThorsAnvil::Serialize;
using TA::ParserInterface;


TEST(BinaryParserTest, ArrayEmpty)
{
    std::stringstream   stream(std::string("\x00\x00\x00\x00", 4)); // []
    TA::BinaryParser<std::vector<int>>    parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(BinaryParserTest, ArrayOneValue)
{
    std::stringstream   stream(std::string("\x00\x00\x00\x01\x00\x00\x00\x0c", 8)); // [12]
    TA::BinaryParser<std::vector<int>>      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(BinaryParserTest, ArrayTwoValue)
{
    std::stringstream   stream(std::string("\x00\x00\x00\x02\x00\x00\x00\x0c\x00\x00\x00\x0d",12)); // [12,13]
    TA::BinaryParser<std::vector<int>>      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(BinaryParserTest, ArrayThreeValue)
{
    std::stringstream   stream(std::string("\x00\x00\x00\x03\x00\x00\x00\x0c\x00\x00\x00\x0d\x00\x00\x00\x0e", 16));    // [12,13,14]
    TA::BinaryParser<std::vector<int>>      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(BinaryParserTest, ArrayWithArray)
{
    std::stringstream   stream(std::string("\x00\x00\x00\x01\x00\x00\x00\x00", 8)); // [[]]
    TA::BinaryParser<std::vector<std::vector<int>>>      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(BinaryParserTest, ArrayWithTwoArray)
{
    std::stringstream   stream(std::string("\x00\x00\x00\x02\x00\x00\x00\x00\x00\x00\x00\x00", 12)); // [[],[]]
    TA::BinaryParser<std::vector<std::vector<int>>>      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(BinaryParserTest, ArrayWithMap)
{
    std::stringstream   stream(std::string("\x00\x00\x00\x01", 4)); // [{}]
    TA::BinaryParser<std::vector<MapEmptyTest>>      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(BinaryParserTest, ArrayWithTwoMap)
{
    std::stringstream   stream(std::string("\x00\x00\x00\x02", 4)); // [{},{}]
    TA::BinaryParser<std::vector<MapEmptyTest>>      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(BinaryParserTest, MapEmpty)
{
    std::stringstream               stream("");
    TA::BinaryParser<MapEmptyTest>  parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(BinaryParserTest, MapOneValue)
{
    std::stringstream               stream(std::string("\x00\x00\x00\x0c", 4));
    TA::BinaryParser<MapOneValue>   parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(BinaryParserTest, MapTwoValue)
{
    std::stringstream               stream(std::string("\x00\x00\x00\x0c\x00\x00\x00\x0d",8));
    TA::BinaryParser<MapTwoValue>   parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(BinaryParserTest, MapThreeValue)
{
    std::stringstream               stream(std::string("\x00\x00\x00\x0c\x00\x00\x00\x0d\x00\x00\x00\x0e", 12));
    TA::BinaryParser<MapThreeValue> parser(stream);

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
TEST(BinaryParserTest, MapWithArray)
{
    std::stringstream   stream(std::string("\x00\x00\x00\x00", 4)); // {"one": []}
    TA::BinaryParser<MapWithArray>      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(BinaryParserTest, MapWithTwoArray)
{
    std::stringstream   stream(std::string("\x00\x00\x00\x00\x00\x00\x00\x00", 8)); // {"one": [], "two": []}
    TA::BinaryParser<MapWithTwoArray>      parser(stream);

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
TEST(BinaryParserTest, MapWithMap)
{
    std::stringstream   stream(""); // R"({"one": {}})"
    TA::BinaryParser<MapWithMap>      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(BinaryParserTest, MapWithTwoMap)
{
    std::stringstream   stream(""); // {"one": {}, "two": {}}
    TA::BinaryParser<MapWithTwoMap>      parser(stream);

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
TEST(BinaryParserTest, GetKeyValue)
{
    std::stringstream   stream(std::string("\x00\x00\x00\x0F",4)); // {"One": 15}
    TA::BinaryParser<MapOneValue>      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::MapStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Key,        parser.getToken());

    std::string key     = parser.getKey();
    EXPECT_EQ("One", key);

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    int value;
    parser.getValue(value);
    EXPECT_EQ(15, value);

    EXPECT_EQ(ParserInterface::ParserToken::MapEnd,     parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(BinaryParserTest, GetArrayBoolValues)
{
    std::stringstream   stream(std::string("\x00\x00\x00\x02\x01\x00", 6)); // [true, false]
    TA::BinaryParser<std::vector<bool>>      parser(stream);

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

    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(BinaryParserTest, GetArrayIntValues)
{
    std::stringstream   stream(std::string("\x00\x00\x00\x03\x00\x00\x00\x7b\x00\x00\x01\x7b\x00\x00\x99\x7b", 16)); // [123, 379, 39291]
    TA::BinaryParser<std::vector<int>>      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    int    test3   = 0;
    parser.getValue(test3);
    EXPECT_EQ(123, test3);

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    parser.getValue(test3);
    EXPECT_EQ(379, test3);
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    parser.getValue(test3);
    EXPECT_EQ(39291, test3);

    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(BinaryParserTest, GetArrayFloatValues)
{
    std::stringstream   stream(std::string("\x00\x00\x00\x03"
                                            "\x40\x5e\xe0\x00\x00\x00\x00\x00"      // 123.5
                                            "\x40\x8a\xdd\x00\x00\x00\x00\x00"      // 859.625
                                            "\x40\x6d\x5c\x00\x00\x00\x00\x00"      // 234.875
                                            , 28)); // [123.5, 859.625, 234.875]
    TA::BinaryParser<std::vector<double>>      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    double test4   = 80;
    parser.getValue(test4);
    EXPECT_EQ(1235, (int)(test4*10));
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    parser.getValue(test4);
    EXPECT_EQ(859625, (int)(test4*1000));
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    parser.getValue(test4);
    EXPECT_EQ(234875, (int)(test4*1000));


    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(BinaryParserTest, GetArrayStringValues)
{
    std::stringstream   stream(std::string( "\x00\x00\x00\x03"
                                            "\x00\x00\x00\x08" "A String"
                                            "\x00\x00\x00\x05" "Blurb"
                                            "\x00\x00\x00\x0e" "Risk The world",
                                            4 + (4 + 8) + (4 + 5) + (4 + 14))); // ["A String", "Blurb", "Risk The world"]
    TA::BinaryParser<std::vector<std::string>>      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());

    std::string    test5;
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    parser.getValue(test5);
    EXPECT_EQ("A String", test5);

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    parser.getValue(test5);
    EXPECT_EQ("Blurb", test5);

    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());
    parser.getValue(test5);
    EXPECT_EQ("Risk The world", test5);

    EXPECT_EQ(ParserInterface::ParserToken::ArrayEnd,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::DocEnd,     parser.getToken());
}
TEST(BinaryParserTest, getDataFromString)
{
    std::stringstream   stream(std::string("\x00\x00\x00\x01\x00\x00\x00\x04" "Test", 12)); // ["Test"]
    TA::BinaryParser<std::vector<std::string>>      parser(stream);

    EXPECT_EQ(ParserInterface::ParserToken::DocStart,   parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::ArrayStart, parser.getToken());
    EXPECT_EQ(ParserInterface::ParserToken::Value,      parser.getToken());

    std::string     value1;
    parser.getValue(value1);
    EXPECT_EQ("Test", value1);

    bool            value4;
    ASSERT_ANY_THROW(
        parser.getValue(value4)
    );
}
#endif

