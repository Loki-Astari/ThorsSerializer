
#include "../../../config.h"
#ifdef  HAVE_YAML
#include "gtest/gtest.h"
#include "YamlPrinter.h"
#include <algorithm>

TEST(YamlPrinterTest, ArrayTokens)
{
    std::stringstream                   stream;
    ThorsAnvil::Serialize::YamlPrinter  printer(stream);

    printer.openDoc();
    printer.openMap();
    printer.closeMap();
    printer.closeDoc();

    std::string     result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    EXPECT_EQ("---{}...", result);
}
TEST(YamlPrinterTest, MapTokens)
{
    std::stringstream                   stream;
    ThorsAnvil::Serialize::YamlPrinter  printer(stream);

    printer.openDoc();
    printer.openArray();
    printer.closeArray();
    printer.closeDoc();

    std::string     result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    EXPECT_EQ("---[]...", result);
}
TEST(YamlPrinterTest, ArrayValues)
{
    std::stringstream                   stream;
    using ThorsAnvil::Serialize::PrinterInterface;
    ThorsAnvil::Serialize::YamlPrinter  printer(stream, PrinterInterface::OutputType::Stream);

    printer.openDoc();
    printer.openArray();
    printer.addValue(true);
    printer.addValue(false);
    printer.addValue(56);
    printer.addValue(78.89);
    printer.addValue(nullptr);
    printer.addValue("Astring");
    printer.closeArray();
    printer.closeDoc();

    std::string     result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    EXPECT_EQ(R"(---[true,false,56,78.89,null,Astring]...)", result);
}
TEST(YamlPrinterTest, MapValues)
{
    std::stringstream                   stream;
    using ThorsAnvil::Serialize::PrinterInterface;
    ThorsAnvil::Serialize::YamlPrinter  printer(stream, PrinterInterface::OutputType::Stream);

    printer.openDoc();
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
    printer.closeDoc();

    std::string     result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    EXPECT_EQ(R"(---{K1:true,K2:false,K3:56,K4:78.89,K5:null,K6:Astring}...)", result);
}
TEST(YamlPrinterTest, MapWithMapValues)
{
    std::stringstream                   stream;
    using ThorsAnvil::Serialize::PrinterInterface;
    ThorsAnvil::Serialize::YamlPrinter  printer(stream, PrinterInterface::OutputType::Stream);

    printer.openDoc();
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
    printer.closeDoc();

    std::string     result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    EXPECT_EQ(R"(---{K1:{K1:true,K2:false},K3:56,K4:{K4:78.89,K5:null},K6:Astring}...)", result);
}
TEST(YamlPrinterTest, MapWithArrayValues)
{
    std::stringstream                   stream;
    using ThorsAnvil::Serialize::PrinterInterface;
    ThorsAnvil::Serialize::YamlPrinter  printer(stream, PrinterInterface::OutputType::Stream);

    printer.openDoc();
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
    printer.closeDoc();

    std::string     result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    EXPECT_EQ(R"(---{K1:[true,false],K3:56,K4:[78.89,null],K6:Astring}...)", result);
}
TEST(YamlPrinterTest, ArrayWithMapValues)
{
    std::stringstream                   stream;
    using ThorsAnvil::Serialize::PrinterInterface;
    ThorsAnvil::Serialize::YamlPrinter  printer(stream, PrinterInterface::OutputType::Stream);

    printer.openDoc();
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
    printer.closeDoc();

    std::string     result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    EXPECT_EQ(R"(---[{K1:true,K2:false},56,{K4:78.89,K5:null},Astring]...)", result);
}
TEST(YamlPrinterTest, ArrayWithArrayValues)
{
    std::stringstream                   stream;
    using ThorsAnvil::Serialize::PrinterInterface;
    ThorsAnvil::Serialize::YamlPrinter  printer(stream, PrinterInterface::OutputType::Stream);

    printer.openDoc();
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
    printer.closeDoc();

    std::string     result  = stream.str();
    result.erase(std::remove_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);}), std::end(result));
    EXPECT_EQ(R"(---[[true,false],56,[78.89,null],Astring]...)", result);
}
TEST(YamlPrinterTest, CloseMapWithArray)
{
    std::stringstream                   stream;
    ThorsAnvil::Serialize::YamlPrinter  printer(stream, ThorsAnvil::Serialize::PrinterInterface::OutputType::Config);

    printer.openDoc();
    printer.openMap();
    ASSERT_ANY_THROW(
        printer.closeArray();
    );
}
TEST(YamlPrinterTest, CloseArrayWithMap)
{
    std::stringstream                   stream;
    ThorsAnvil::Serialize::YamlPrinter  printer(stream, ThorsAnvil::Serialize::PrinterInterface::OutputType::Config);

    printer.openDoc();
    printer.openArray();
    ASSERT_ANY_THROW(
        printer.closeMap();
    );
}
TEST(YamlPrinterTest, PuttingKeyInArray)
{
    std::stringstream                   stream;
    ThorsAnvil::Serialize::YamlPrinter  printer(stream, ThorsAnvil::Serialize::PrinterInterface::OutputType::Config);

    printer.openDoc();
    printer.openArray();
    ASSERT_ANY_THROW(
        printer.addKey("This old house");
    );
}

#endif

