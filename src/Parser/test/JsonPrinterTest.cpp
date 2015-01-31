
#include "gtest/gtest.h"
#include "JsonPrinter.h"
#include <algorithm>

TEST(JsonPrinterTest, ArrayTokens)
{
    std::stringstream                       stream;
    ThorsAnvil::Serialization::JsonPrinter  printer(stream);

    printer.openMap();
    printer.closeMap();

    std::string     result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    EXPECT_EQ("{}", result);
}
TEST(JsonPrinterTest, MapTokens)
{
    std::stringstream                       stream;
    ThorsAnvil::Serialization::JsonPrinter  printer(stream);

    printer.openArray();
    printer.closeArray();

    std::string     result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    EXPECT_EQ("[]", result);
}
TEST(JsonPrinterTest, ArrayValues)
{
    std::stringstream                       stream;
    ThorsAnvil::Serialization::JsonPrinter  printer(stream);

    printer.openArray();
    printer.addValue(true);
    printer.addValue(false);
    printer.addValue(56);
    printer.addValue(78.89);
    printer.addValue(nullptr);
    printer.addValue("Astring");
    printer.closeArray();

    std::string     result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    EXPECT_EQ(R"([true,false,56,78.89,null,"Astring"])", result);
}
TEST(JsonPrinterTest, MapValues)
{
    std::stringstream                       stream;
    ThorsAnvil::Serialization::JsonPrinter  printer(stream);

    printer.openMap();
    printer.addKey("K1");
    printer.addValue(true);
    printer.addKey("K2");
    printer.addValue(false);
    printer.addKey("K3");
    printer.addValue(56);
    printer.addKey("K4");
    printer.addValue(78.89);
    printer.addKey("K5");
    printer.addValue(nullptr);
    printer.addKey("K6");
    printer.addValue(std::string("Astring"));
    printer.closeMap();

    std::string     result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    EXPECT_EQ(R"({"K1":true,"K2":false,"K3":56,"K4":78.89,"K5":null,"K6":"Astring"})", result);
}
TEST(JsonPrinterTest, MapWithMapValues)
{
    std::stringstream                       stream;
    ThorsAnvil::Serialization::JsonPrinter  printer(stream);

    printer.openMap();
    printer.addKey("K1");
    printer.openMap();
    printer.addKey("K1");
    printer.addValue(true);
    printer.addKey("K2");
    printer.addValue(false);
    printer.closeMap();
    printer.addKey("K3");
    printer.addValue(56);
    printer.addKey("K4");
    printer.openMap();
    printer.addKey("K4");
    printer.addValue(78.89);
    printer.addKey("K5");
    printer.addValue(nullptr);
    printer.closeMap();
    printer.addKey("K6");
    printer.addValue(std::string("Astring"));
    printer.closeMap();

    std::string     result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    EXPECT_EQ(R"({"K1":{"K1":true,"K2":false},"K3":56,"K4":{"K4":78.89,"K5":null},"K6":"Astring"})", result);
}
TEST(JsonPrinterTest, MapWithArrayValues)
{
    std::stringstream                       stream;
    ThorsAnvil::Serialization::JsonPrinter  printer(stream);

    printer.openMap();
    printer.addKey("K1");
    printer.openArray();
    printer.addValue(true);
    printer.addValue(false);
    printer.closeArray();
    printer.addKey("K3");
    printer.addValue(56);
    printer.addKey("K4");
    printer.openArray();
    printer.addValue(78.89);
    printer.addValue(nullptr);
    printer.closeArray();
    printer.addKey("K6");
    printer.addValue(std::string("Astring"));
    printer.closeMap();

    std::string     result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    EXPECT_EQ(R"({"K1":[true,false],"K3":56,"K4":[78.89,null],"K6":"Astring"})", result);
}
TEST(JsonPrinterTest, ArrayWithMapValues)
{
    std::stringstream                       stream;
    ThorsAnvil::Serialization::JsonPrinter  printer(stream);

    printer.openArray();
    printer.openMap();
    printer.addKey("K1");
    printer.addValue(true);
    printer.addKey("K2");
    printer.addValue(false);
    printer.closeMap();
    printer.addValue(56);
    printer.openMap();
    printer.addKey("K4");
    printer.addValue(78.89);
    printer.addKey("K5");
    printer.addValue(nullptr);
    printer.closeMap();
    printer.addValue(std::string("Astring"));
    printer.closeArray();

    std::string     result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    EXPECT_EQ(R"([{"K1":true,"K2":false},56,{"K4":78.89,"K5":null},"Astring"])", result);
}
TEST(JsonPrinterTest, ArrayWithArrayValues)
{
    std::stringstream                       stream;
    ThorsAnvil::Serialization::JsonPrinter  printer(stream);

    printer.openArray();
    printer.openArray();
    printer.addValue(true);
    printer.addValue(false);
    printer.closeArray();
    printer.addValue(56);
    printer.openArray();
    printer.addValue(78.89);
    printer.addValue(nullptr);
    printer.closeArray();
    printer.addValue(std::string("Astring"));
    printer.closeArray();

    std::string     result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    EXPECT_EQ(R"([[true,false],56,[78.89,null],"Astring"])", result);
}
TEST(JsonPrinterTest, CheckStreeamIsCompressed)
{
    std::stringstream                       stream;
    ThorsAnvil::Serialization::JsonPrinter  printer(stream, ThorsAnvil::Serialization::PrinterInterface::OutputType::Stream);

    printer.openArray();
    printer.openMap();
    printer.addKey("K1");
    printer.addValue(true);
    printer.addKey("K2");
    printer.addValue(false);
    printer.closeMap();
    printer.addValue(56);
    printer.openMap();
    printer.addKey("K4");
    printer.addValue(78.89);
    printer.addKey("K5");
    printer.addValue(nullptr);
    printer.closeMap();
    printer.addValue(std::string("Astring"));
    printer.closeArray();

    std::string     result  = stream.str();
    int             space   = std::count_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);});
    EXPECT_EQ(0, space);
}
TEST(JsonPrinterTest, CloseMapWithArray)
{
    std::stringstream                       stream;
    ThorsAnvil::Serialization::JsonPrinter  printer(stream, ThorsAnvil::Serialization::PrinterInterface::OutputType::Stream);

    printer.openMap();
    ASSERT_ANY_THROW(
        printer.closeArray();
    );
}
TEST(JsonPrinterTest, CloseArrayWithMap)
{
    std::stringstream                       stream;
    ThorsAnvil::Serialization::JsonPrinter  printer(stream, ThorsAnvil::Serialization::PrinterInterface::OutputType::Stream);

    printer.openArray();
    ASSERT_ANY_THROW(
        printer.closeMap();
    );
}
TEST(JsonPrinterTest, PuttingKeyInArray)
{
    std::stringstream                       stream;
    ThorsAnvil::Serialization::JsonPrinter  printer(stream, ThorsAnvil::Serialization::PrinterInterface::OutputType::Stream);

    printer.openArray();
    ASSERT_ANY_THROW(
        printer.addKey("This old house");
    );
}

