
#include "gtest/gtest.h"
#include "test/SerializeTest.h"
#include "Serialize.h"
#include "Traits.h"
#include "JsonThor.h"
#include <cstring>
#include <string>
#include <algorithm>


std::string const testData1 = R"({"theInteger":34,"aNonRealValue":56.78,"test":true,"normalString":"Done"})";
std::string const testData2 = R"({"theInteger":456,"aNonRealValue":89.101,"test":false,"normalString":"Akinkthatisnotstraight","data1":1,"data2":2})";
std::string const testData3 = R"({"member1":{"theInteger":234567,"aNonRealValue":123.45,"test":true,"normalString":"NotASquareAndOnlyOneSide"})"
                              R"(,"member2":{"theInteger":234567,"aNonRealValue":123.45,"test":true,"normalString":"NotASquareAndOnlyOneSide","data1":67,"data2":11}})";
// testData4 is identical to testData1 but with several ignored fields added.
std::string const testData4 = R"({"theInteger":34,"aNonRealValue":56.78,"test":true,"normalString":"Done","ShouldIgnore":true, "ignoreMap": {"Plop":true}, "ignoreArray":[true, false, [1,2,34], {"key":"value"}]})";
std::string const testData5 = R"({"theInteger":34,"aNonRealValue":56.78,"test":true,"normalString":"Done","anotherValue":14})";
std::string const testDataE1 = R"({"ignoreMap": {"Plop":true, ]}})";
std::string const testDataE2 = R"({"ignoreArray": [}]})";
std::string const testDataE3 = R"({"ignoreArray": [)";
std::string const testDataE4 = R"({"ignoreArray": )";
std::string const testDataE5 = R"({"ignoreArray": ])";
std::string const testDataE6 = R"({"ignoreArray": })";

TEST(SerializeTest, SerializeStructureOfValue)
{
    SerializeTestExtra        data(34,56.78, true, "Done");

    std::stringstream   stream;
    ThorsAnvil::Serialize::JsonPrinter  printer(stream);
    ThorsAnvil::Serialize::Serializer   serializer(printer);

    serializer.print(data);
    std::string result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ(testData1, result);
}

TEST(SerializeTest, DeSerializeStructureOfValue)
{
    SerializeTestExtra      data;

    std::stringstream                   stream(testData1);
    ThorsAnvil::Serialize::JsonParser   parser(stream);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    deSerializer.parse(data);

    EXPECT_EQ(data.theInteger,      34);
    EXPECT_EQ(data.aNonRealValue,   56.78);
    EXPECT_EQ(data.test,            true);
    EXPECT_EQ(data.normalString,    "Done");
}

TEST(SerializeTest, SerializeStructureOfValueAndParents)
{
    SerializeTestChild     data(1, 2, 456, 89.101, false, "Akinkthatisnotstraight");

    std::stringstream   stream;
    ThorsAnvil::Serialize::JsonPrinter  printer(stream);
    ThorsAnvil::Serialize::Serializer   serializer(printer);

    serializer.print(data);
    std::string result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ(testData2, result);
}

TEST(SerializeTest, DeSerializeStructureOfValueAndParent)
{
    SerializeTestChild      data;

    std::stringstream                   stream(testData2);
    ThorsAnvil::Serialize::JsonParser   parser(stream);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    deSerializer.parse(data);

    EXPECT_EQ(data.theInteger,      456);
    EXPECT_EQ(data.aNonRealValue,   89.101);
    EXPECT_EQ(data.test,            false);
    EXPECT_EQ(data.normalString,    "Akinkthatisnotstraight");
    EXPECT_EQ(data.data1,           1);
    EXPECT_EQ(data.data2,           2);
}

TEST(SerializeTest, SerializeStructureMemberOfValue)
{
    SerializeTestMembers        data(67, 11, 234567, 123.45, true, "NotASquareAndOnlyOneSide");

    std::stringstream   stream;
    ThorsAnvil::Serialize::JsonPrinter  printer(stream);
    ThorsAnvil::Serialize::Serializer   serializer(printer);

    serializer.print(data);
    std::string result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ(testData3, result);
}

TEST(SerializeTest, DeSerializeStructureMemberOfValue)
{
    SerializeTestMembers        data;

    std::stringstream                   stream(testData3);
    ThorsAnvil::Serialize::JsonParser   parser(stream);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    deSerializer.parse(data);

    EXPECT_EQ(data.member1.theInteger,      234567);
    EXPECT_EQ(data.member1.aNonRealValue,   123.45);
    EXPECT_EQ(data.member1.test,            true);
    EXPECT_EQ(data.member1.normalString,    "NotASquareAndOnlyOneSide");
    EXPECT_EQ(data.member2.theInteger,      234567);
    EXPECT_EQ(data.member2.aNonRealValue,   123.45);
    EXPECT_EQ(data.member2.test,            true);
    EXPECT_EQ(data.member2.normalString,    "NotASquareAndOnlyOneSide");
    EXPECT_EQ(data.member2.data1,           67);
    EXPECT_EQ(data.member2.data2,           11);
}

TEST(SerializeTest, StrictParserDoesNotIgnoreData)
{
    SerializeTestExtra      data;

    std::stringstream                   stream(testData4);
    ThorsAnvil::Serialize::JsonParser   parser(stream, ThorsAnvil::Serialize::ParserInterface::ParseType::Strict);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    EXPECT_THROW(
        deSerializer.parse(data),
        std::runtime_error
    );
}
TEST(SerializeTest, ExactParserDoesNotIgnoreData)
{
    SerializeTestExtra      data;

    std::stringstream                   stream(testData4);
    ThorsAnvil::Serialize::JsonParser   parser(stream, ThorsAnvil::Serialize::ParserInterface::ParseType::Exact);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    EXPECT_THROW(
        deSerializer.parse(data),
        std::runtime_error
    );
}
TEST(SerializeTest, ExactParserNeedsAllMembersFail)
{
    SerializeExact      data;

    // testData1 has all the members of SerializeTestExtra (parent of SerializeExact)
    // but does not have anotherValue so should throw an exception
    std::stringstream                   stream(testData1);
    ThorsAnvil::Serialize::JsonParser   parser(stream, ThorsAnvil::Serialize::ParserInterface::ParseType::Exact);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    EXPECT_THROW(
        deSerializer.parse(data),
        std::runtime_error
    );
}
TEST(SerializeTest, ExactParserNeedsAllMembersGood)
{
    SerializeExact      data;

    std::stringstream                   stream(testData5);
    ThorsAnvil::Serialize::JsonParser   parser(stream, ThorsAnvil::Serialize::ParserInterface::ParseType::Exact);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    deSerializer.parse(data);
}
TEST(SerializeTest, IgnoreAllTheDataWeDontCareAbout)
{
    SerializeTestExtra      data;

    std::stringstream                   stream(testData4);
    ThorsAnvil::Serialize::JsonParser   parser(stream);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    deSerializer.parse(data);

    EXPECT_EQ(data.theInteger,      34);
    EXPECT_EQ(data.aNonRealValue,   56.78);
    EXPECT_EQ(data.test,            true);
    EXPECT_EQ(data.normalString,    "Done");
}
TEST(SerializeTest, IgnoreDataMapWithBadData1)
{
    SerializeTestExtra      data;

    std::stringstream                   stream(testDataE1);
    ThorsAnvil::Serialize::JsonParser   parser(stream);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    EXPECT_THROW(
        deSerializer.parse(data),
        std::runtime_error
    );
}
TEST(SerializeTest, IgnoreDataArrayWithBadData2)
{
    SerializeTestExtra      data;

    std::stringstream                   stream(testDataE2);
    ThorsAnvil::Serialize::JsonParser   parser(stream);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    EXPECT_THROW(
        deSerializer.parse(data),
        std::runtime_error
    );
}
TEST(SerializeTest, IgnoreDataArrayWithBadData3)
{
    SerializeTestExtra      data;

    std::stringstream                   stream(testDataE3);
    ThorsAnvil::Serialize::JsonParser   parser(stream);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    EXPECT_THROW(
        deSerializer.parse(data),
        std::runtime_error
    );
}
TEST(SerializeTest, IgnoreDataArrayWithBadData4)
{
    SerializeTestExtra      data;

    std::stringstream                   stream(testDataE4);
    ThorsAnvil::Serialize::JsonParser   parser(stream);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    EXPECT_THROW(
        deSerializer.parse(data),
        std::runtime_error
    );
}
TEST(SerializeTest, IgnoreDataArrayWithBadData5)
{
    SerializeTestExtra      data;

    std::stringstream                   stream(testDataE5);
    ThorsAnvil::Serialize::JsonParser   parser(stream);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    EXPECT_THROW(
        deSerializer.parse(data),
        std::runtime_error
    );
}
TEST(SerializeTest, IgnoreDataArrayWithBadData6)
{
    SerializeTestExtra      data;

    std::stringstream                   stream(testDataE6);
    ThorsAnvil::Serialize::JsonParser   parser(stream);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    EXPECT_THROW(
        deSerializer.parse(data),
        std::runtime_error
    );
}

