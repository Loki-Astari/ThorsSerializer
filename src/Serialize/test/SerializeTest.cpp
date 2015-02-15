
#include "gtest/gtest.h"
#include "test/SerializeTest.h"
#include "Serialize.h"
#include "Traits.h"
#include "Json.h"
#include <cstring>
#include <string>


std::string const testData1 = R"({"theInteger":34,"aNonRealValue":56.78,"test":true,"aCStringObject":"Help","normalString":"Done"})";
std::string const testData2 = R"({"theInteger":456,"aNonRealValue":89.101,"test":false,"aCStringObject":"Bend","normalString":"Akinkthatisnotstraight","data1":1,"data2":2})";
std::string const testData3 = R"({"member1":{"theInteger":234567,"aNonRealValue":123.45,"test":true,"aCStringObject":"Round","normalString":"NotASquareAndOnlyOneSide"})"
                              R"(,"member2":{"theInteger":234567,"aNonRealValue":123.45,"test":true,"aCStringObject":"Round","normalString":"NotASquareAndOnlyOneSide","data1":67,"data2":11}})";

TEST(SerializeTest, SerializeStructureOfValue)
{
    SerializeTestExtra        data(34,56.78, true, "Help", "Done");

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
    EXPECT_EQ(std::string(data.aCStringObject),  "Help");
    EXPECT_EQ(data.normalString,    "Done");
}

TEST(SerializeTest, SerializeStructureOfValueAndParents)
{
    SerializeTestChild     data(1, 2, 456, 89.101, false, "Bend", "Akinkthatisnotstraight");

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
    EXPECT_EQ(std::string(data.aCStringObject),  "Bend");
    EXPECT_EQ(data.normalString,    "Akinkthatisnotstraight");
    EXPECT_EQ(data.data1,           1);
    EXPECT_EQ(data.data2,           2);
}

TEST(SerializeTest, SerializeStructureMemberOfValue)
{
    SerializeTestMembers        data(67, 11, 234567, 123.45, true, "Round", "NotASquareAndOnlyOneSide");

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
    EXPECT_EQ(std::string(data.member1.aCStringObject),  "Round");
    EXPECT_EQ(data.member1.normalString,    "NotASquareAndOnlyOneSide");
    EXPECT_EQ(data.member2.theInteger,      234567);
    EXPECT_EQ(data.member2.aNonRealValue,   123.45);
    EXPECT_EQ(data.member2.test,            true);
    EXPECT_EQ(std::string(data.member2.aCStringObject),  "Round");
    EXPECT_EQ(data.member2.normalString,    "NotASquareAndOnlyOneSide");
    EXPECT_EQ(data.member2.data1,           67);
    EXPECT_EQ(data.member2.data2,           11);
}


