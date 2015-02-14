
#include "gtest/gtest.h"
#include "test/SerializeTest.h"
#include "Serialize.h"
#include "Traits.h"
#include "Json.h"
#include <cstring>
#include <string>


std::string const testData = R"({"theInteger":34,"aNonRealValue":56.78,"test":true,"aCStringObject":"Help","normalString":"Done"})";

TEST(SerializeTest, SerializeStructureOfValue)
{
    SerializeTestExtra        data(34,56.78, true, "Help", "Done");

    std::stringstream   stream;
    ThorsAnvil::Serialize::JsonPrinter  printer(stream);
    ThorsAnvil::Serialize::Serializer   serializer(printer);

    serializer.print(data);
    std::string result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));

    EXPECT_EQ(testData, result);
 }

 TEST(SerializeTest, DeSerializeStructureOfValue)
 {
    SerializeTestExtra      data;

    std::stringstream                   stream(testData);
    ThorsAnvil::Serialize::JsonParser   parser(stream);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    deSerializer.parse(data);

    EXPECT_EQ(data.theInteger,      34);
    EXPECT_EQ(data.aNonRealValue,   56.78);
    EXPECT_EQ(data.test,            true);
    EXPECT_EQ(std::string(data.aCStringObject),  "Help");
    EXPECT_EQ(data.normalString,    "Done");
}

