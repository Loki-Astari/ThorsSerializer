
#include "gtest/gtest.h"
#include "Traits.h"
#include "SerUtil.h"
#include "JsonThor.h"
#include "YamlThor.h"
#include "BsonThor.h"

using namespace std::string_literals;

struct FilterTestType
{
    std::string     m1;
    std::string     m2;

    std::map<std::string, bool> filter;
};

ThorsAnvil_MakeFilter(FilterTestType, filter);
ThorsAnvil_MakeTrait(FilterTestType, m1, m2);


TEST(FilterValuesTest, JsonFilterOutZeroMember)
{
    FilterTestType      test{"Data 1", "Other Stuff", {{"m1", true}, {"m2", true}}};

    std::stringstream   stream;
    stream << ThorsAnvil::Serialize::jsonExporter(test);
    std::string         streamData = stream.str();

    auto findM1 = streamData.find("m1");
    EXPECT_NE(std::string::npos, findM1);

    auto findM2 = streamData.find("m2");
    EXPECT_NE(std::string::npos, findM2);
}
TEST(FilterValuesTest, JsonFilterOutM1Member)
{
    FilterTestType      test{"Data 1", "Other Stuff", {{"m1", false}, {"m2", true}}};

    std::stringstream   stream;
    stream << ThorsAnvil::Serialize::jsonExporter(test);
    std::string         streamData = stream.str();

    auto findM1 = streamData.find("m1");
    EXPECT_EQ(std::string::npos, findM1);

    auto findM2 = streamData.find("m2");
    EXPECT_NE(std::string::npos, findM2);
}
TEST(FilterValuesTest, JsonFilterOutM2Member)
{
    FilterTestType      test{"Data 1", "Other Stuff", {{"m1", true}, {"m2", false}}};

    std::stringstream   stream;
    stream << ThorsAnvil::Serialize::jsonExporter(test);
    std::string         streamData = stream.str();

    auto findM1 = streamData.find("m1");
    EXPECT_NE(std::string::npos, findM1);

    auto findM2 = streamData.find("m2");
    EXPECT_EQ(std::string::npos, findM2);
}
TEST(FilterValuesTest, JsonFilterOutAllMember)
{
    FilterTestType      test{"Data 1", "Other Stuff", {{"m1", false}, {"m2", false}}};

    std::stringstream   stream;
    stream << ThorsAnvil::Serialize::jsonExporter(test);
    std::string         streamData = stream.str();

    auto findM1 = streamData.find("m1");
    EXPECT_EQ(std::string::npos, findM1);

    auto findM2 = streamData.find("m2");
    EXPECT_EQ(std::string::npos, findM2);
}


TEST(FilterValuesTest, YamlFilterOutZeroMember)
{
    FilterTestType      test{"Data 1", "Other Stuff", {{"m1", true}, {"m2", true}}};

    std::stringstream   stream;
    stream << ThorsAnvil::Serialize::yamlExporter(test);
    std::string         streamData = stream.str();

    auto findM1 = streamData.find("m1");
    EXPECT_NE(std::string::npos, findM1);

    auto findM2 = streamData.find("m2");
    EXPECT_NE(std::string::npos, findM2);
}
TEST(FilterValuesTest, YamlFilterOutM1Member)
{
    FilterTestType      test{"Data 1", "Other Stuff", {{"m1", false}, {"m2", true}}};

    std::stringstream   stream;
    stream << ThorsAnvil::Serialize::yamlExporter(test);
    std::string         streamData = stream.str();

    auto findM1 = streamData.find("m1");
    EXPECT_EQ(std::string::npos, findM1);

    auto findM2 = streamData.find("m2");
    EXPECT_NE(std::string::npos, findM2);
}
TEST(FilterValuesTest, YamlFilterOutM2Member)
{
    FilterTestType      test{"Data 1", "Other Stuff", {{"m1", true}, {"m2", false}}};

    std::stringstream   stream;
    stream << ThorsAnvil::Serialize::yamlExporter(test);
    std::string         streamData = stream.str();

    auto findM1 = streamData.find("m1");
    EXPECT_NE(std::string::npos, findM1);

    auto findM2 = streamData.find("m2");
    EXPECT_EQ(std::string::npos, findM2);
}
TEST(FilterValuesTest, YamlFilterOutAllMember)
{
    FilterTestType      test{"Data 1", "Other Stuff", {{"m1", false}, {"m2", false}}};

    std::stringstream   stream;
    stream << ThorsAnvil::Serialize::yamlExporter(test);
    std::string         streamData = stream.str();

    auto findM1 = streamData.find("m1");
    EXPECT_EQ(std::string::npos, findM1);

    auto findM2 = streamData.find("m2");
    EXPECT_EQ(std::string::npos, findM2);
}


TEST(FilterValuesTest, BsonFilterOutZeroMember)
{
    FilterTestType      test{"Data 1", "Other Stuff", {{"m1", true}, {"m2", true}}};

    std::stringstream   stream;
    stream << ThorsAnvil::Serialize::bsonExporter(test);

    std::string         expected(   "\x28\x00\x00\x00"
                                    "\x02" "m1\x00" "\x07\x00\x00\x00" "Data 1\x00"
                                    "\x02" "m2\x00" "\x0C\x00\x00\x00" "Other Stuff\x00"
                                    "\x00"s
                                );

    EXPECT_EQ(expected, stream.str());
}
TEST(FilterValuesTest, BsonFilterOutM1Member)
{
    FilterTestType      test{"Data 1", "Other Stuff", {{"m1", false}, {"m2", true}}};

    std::stringstream   stream;
    stream << ThorsAnvil::Serialize::bsonExporter(test);

    std::string         expected(   "\x19\x00\x00\x00"
                                    "\x02" "m2\x00" "\x0C\x00\x00\x00" "Other Stuff\x00"
                                    "\x00"s
                                );

    EXPECT_EQ(expected, stream.str());
}
TEST(FilterValuesTest, BsonFilterOutM2Member)
{
    FilterTestType      test{"Data 1", "Other Stuff", {{"m1", true}, {"m2", false}}};

    std::stringstream   stream;
    stream << ThorsAnvil::Serialize::bsonExporter(test);

    std::string         expected(   "\x14\x00\x00\x00"
                                    "\x02" "m1\x00" "\x07\x00\x00\x00" "Data 1\x00"
                                    "\x00"s
                                );

    EXPECT_EQ(expected, stream.str());
}
TEST(FilterValuesTest, BsonFilterOutAllMember)
{
    FilterTestType      test{"Data 1", "Other Stuff", {{"m1", false}, {"m2", false}}};

    std::stringstream   stream;
    stream << ThorsAnvil::Serialize::bsonExporter(test);

    std::string         expected(   "\x05\x00\x00\x00"
                                    "\x00"s
                                );

    EXPECT_EQ(expected, stream.str());
}

