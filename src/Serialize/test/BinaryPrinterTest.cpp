#include "../../config.h"
#ifdef NETWORK_BYTE_ORDER


#include "gtest/gtest.h"
#include "BinaryPrinter.h"
#include <algorithm>

TEST(BinaryPrinterTest, ArrayTokens)
{
    std::stringstream                     stream;
    ThorsAnvil::Serialize::BinaryPrinter<int>  printer(stream);

    printer.openDoc();
    printer.openMap();
    printer.closeMap();
    printer.closeDoc();

    std::string     result  = stream.str();
    EXPECT_EQ(4, result.size());
    EXPECT_EQ(0, result.compare(0, 4, "\0\0\0I", 4));
}
TEST(BinaryPrinterTest, MapTokens)
{
    std::stringstream                     stream;
    ThorsAnvil::Serialize::BinaryPrinter<int>  printer(stream);

    printer.openDoc();
    printer.openArray();
    printer.closeArray();
    printer.closeDoc();

    std::string     result  = stream.str();
    EXPECT_EQ(4, result.size());
    EXPECT_EQ(0, result.compare(0, 4, "\0\0\0I", 4));
}
TEST(BinaryPrinterTest, intToken)
{
    std::stringstream                     stream;
    ThorsAnvil::Serialize::BinaryPrinter<int>  printer(stream);

    printer.addValue(static_cast<short>(0x4567));   // 2
    EXPECT_EQ(2, stream.str().size());
    printer.addValue(0x89ABCDEF);                   // 4
    EXPECT_EQ(6, stream.str().size());
    printer.addValue(0x123456780FEDCBA9L);          // 8
    EXPECT_EQ(14, stream.str().size());
    printer.addValue(0x123456780FEDCBA9LL);         // 16
    EXPECT_EQ(30, stream.str().size());

    printer.addValue(static_cast<unsigned short>(0x4567));
    EXPECT_EQ(32, stream.str().size());
    printer.addValue(0x89ABCDEFU);
    EXPECT_EQ(36, stream.str().size());
    printer.addValue(0x123456780FEDCBA9UL);
    EXPECT_EQ(44, stream.str().size());
    printer.addValue(0x123456780FEDCBA9ULL);
    EXPECT_EQ(60, stream.str().size());

    printer.addValue(true);
    EXPECT_EQ(61, stream.str().size());
    printer.addValue(false);
    EXPECT_EQ(62, stream.str().size());
    std::string     result  = stream.str();
    EXPECT_EQ(62, result.size());
    EXPECT_EQ(0, result.compare(0, 46, "\x45\x67"
                                       "\x89\xAB\xCD\xEF"
                                       "\x12\x34\x56\x78\x0F\xED\xCB\xA9"
                                       "\x00\x00\x00\x00\x00\x00\x00\x00\x12\x34\x56\x78\x0F\xED\xCB\xA9"
                                       "\x45\x67"
                                       "\x89\xAB\xCD\xEF"
                                       "\x12\x34\x56\x78\x0F\xED\xCB\xA9"
                                       "\x00\x00\x00\x00\x00\x00\x00\x00\x12\x34\x56\x78\x0F\xED\xCB\xA9"
                                       "\x01"
                                       "\x00"
                                       , 46));

    /*
       BinaryPrinterTest.cpp:49: Failure
       Value of: stream.str().size()
         Actual: 30
Expected: 22
BinaryPrinterTest.cpp:52: Failure
Value of: stream.str().size()
  Actual: 32
Expected: 24
BinaryPrinterTest.cpp:54: Failure
Value of: stream.str().size()
  Actual: 36
Expected: 28
BinaryPrinterTest.cpp:56: Failure
Value of: stream.str().size()
  Actual: 44
Expected: 36
BinaryPrinterTest.cpp:58: Failure
Value of: stream.str().size()
  Actual: 60
Expected: 44
BinaryPrinterTest.cpp:61: Failure
Value of: stream.str().size()
  Actual: 61
Expected: 45
BinaryPrinterTest.cpp:63: Failure
Value of: stream.str().size()
  Actual: 62
Expected: 46
BinaryPrinterTest.cpp:65: Failure
Value of: result.size()
  Actual: 62
  Expected: 46
  */

    /*
    [ RUN      ] BinaryPrinterTest.intToken
    BinaryPrinterTest.cpp:55: Failure
    Value of: result.size()
    Actual: 62
    Expected: 46
    BinaryPrinterTest.cpp:66: Failure
    Value of: result.compare(0, 46, "\x45\x67" "\x89\xAB\xCD\xEF" "\x12\x34\x56\x78\x0F\xED\xCB\xA9" "\x12\x34\x56\x78\x0F\xED\xCB\xA9" "\x45\x67" "\x89\xAB\xCD\xEF" "\x12\x34\x56\x78\x0F\xED\xCB\xA9" "\x12\x34\x56\x78\x0F\xED\xCB\xA9" "\x01" "\x00" , 46)
    Actual: -18
    Expected: 0
    */
}
TEST(BinaryPrinterTest, stringToken)
{
    std::stringstream                     stream;
    ThorsAnvil::Serialize::BinaryPrinter<int>  printer(stream);

    printer.addValue(std::string("The long good bye"));
    printer.addKey(std::string("Live for a day"));

    std::string     result  = stream.str();
    EXPECT_EQ(39,   result.size());
    EXPECT_EQ(0,    result.compare(0, 39, "\x00\x00\x00\x11The long good bye\x00\x00\x00\x0ELive for a day", 39));
}
#if 0
TEST(BinaryPrinterTest, floatToken)
{
    std::stringstream                     stream;
    ThorsAnvil::Serialize::BinaryPrinter<int>  printer(stream);

    printer.addValue(34.0F);    // 4
    printer.addValue(35.0);     // 8
    printer.addValue(36.0L);    // 16


    std::string     result  = stream.str();
    EXPECT_EQ(28,   result.size());
    EXPECT_EQ(0,    result.compare(0, 28, "", 28));

    std::cout << "DIG: " << std::numeric_limits<float>::digits << "   RAD: " << std::numeric_limits<float>::radix
        << "  MIN: " << std::numeric_limits<float>::min_exponent << "  MAX: " << std::numeric_limits<float>::max_exponent << "\n";
    std::cout << "DIG: " << std::numeric_limits<double>::digits << "   RAD: " << std::numeric_limits<double>::radix
        << "  MIN: " << std::numeric_limits<double>::min_exponent << "  MAX: " << std::numeric_limits<double>::max_exponent << "\n";
    std::cout << "DIG: " << std::numeric_limits<long double>::digits << "   RAD: " << std::numeric_limits<long double>::radix
        << "  MIN: " << std::numeric_limits<long double>::min_exponent << "  MAX: " << std::numeric_limits<long double>::max_exponent << "\n";
}
TEST(BinaryPrinterTest, MapValues)
{
    std::stringstream                     stream;
    ThorsAnvil::Serialize::BinaryPrinter  printer(stream);

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
    printer.addKey("K6");
    printer.addValue(std::string("Astring"));
    printer.closeMap();
    printer.closeDoc();

    std::string     result  = stream.str();
    EXPECT_EQ(R"({"K1":true,"K2":false,"K3":56,"K4":78.89,"K6":"Astring"})", result);
}
TEST(BinaryPrinterTest, MapWithMapValues)
{
    std::stringstream                     stream;
    ThorsAnvil::Serialize::BinaryPrinter  printer(stream);

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
    printer.closeMap();
    printer.addKey("K6");
    printer.addValue(std::string("Astring"));
    printer.closeMap();
    printer.closeDoc();

    std::string     result  = stream.str();
    EXPECT_EQ(R"({"K1":{"K1":true,"K2":false},"K3":56,"K4":{"K4":78.89},"K6":"Astring"})", result);
}
TEST(BinaryPrinterTest, MapWithArrayValues)
{
    std::stringstream                     stream;
    ThorsAnvil::Serialize::BinaryPrinter  printer(stream);

    printer.openDoc();
    printer.openMap();
    printer.addKey("K1");
    printer.openArray();
    printer.addValue(true);
    printer.addValue(false);
    printer.addValue(static_cast<unsigned short>(55));
    printer.addValue(56u);
    printer.addValue(57ul);
    printer.addValue(58ull);
    printer.addValue(60.f);
    printer.addValue(61.0L);
    printer.closeArray();
    printer.addKey("K3");
    printer.addValue(56);
    printer.addKey("K4");
    printer.openArray();
    printer.addValue(78.89);
    printer.closeArray();
    printer.addKey("K6");
    printer.addValue(std::string("Astring"));
    printer.closeMap();
    printer.closeDoc();

    std::string     result  = stream.str();
    EXPECT_EQ(R"({"K1":[true,false,55,56,57,58,60,61],"K3":56,"K4":[78.89],"K6":"Astring"})", result);
}
TEST(BinaryPrinterTest, ArrayWithMapValues)
{
    std::stringstream                     stream;
    ThorsAnvil::Serialize::BinaryPrinter  printer(stream);

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
    printer.closeMap();
    printer.addValue(std::string("Astring"));
    printer.closeArray();
    printer.closeDoc();

    std::string     result  = stream.str();
    EXPECT_EQ(R"([{"K1":true,"K2":false},56,{"K4":78.89},"Astring"])", result);
}
TEST(BinaryPrinterTest, ArrayWithArrayValues)
{
    std::stringstream                     stream;
    ThorsAnvil::Serialize::BinaryPrinter  printer(stream);

    printer.openDoc();
    printer.openArray();
    printer.openArray();
    printer.addValue(true);
    printer.addValue(false);
    printer.closeArray();
    printer.addValue(56);
    printer.openArray();
    printer.addValue(78.89);
    printer.closeArray();
    printer.addValue(std::string("Astring"));
    printer.closeArray();
    printer.closeDoc();

    std::string     result  = stream.str();
    EXPECT_EQ(R"([[true,false],56,[78.89],"Astring"])", result);
}
TEST(BinaryPrinterTest, CheckStreeamIsCompressed)
{
    std::stringstream                     stream;
    ThorsAnvil::Serialize::BinaryPrinter  printer(stream, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream);

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
    printer.closeMap();
    printer.addValue(std::string("Astring"));
    printer.closeArray();
    printer.closeDoc();

    std::string     result  = stream.str();
    int             space   = std::count_if(std::begin(result), std::end(result), [](char x){return ::isspace(x);});
    EXPECT_EQ(0, space);
}
TEST(BinaryPrinterTest, CloseMapWithArray)
{
    std::stringstream                     stream;
    ThorsAnvil::Serialize::BinaryPrinter  printer(stream, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream);

    printer.openDoc();
    printer.openMap();
    ASSERT_ANY_THROW(
        printer.closeArray();
    );
}
TEST(BinaryPrinterTest, CloseArrayWithMap)
{
    std::stringstream                     stream;
    ThorsAnvil::Serialize::BinaryPrinter  printer(stream, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream);

    printer.openDoc();
    printer.openArray();
    ASSERT_ANY_THROW(
        printer.closeMap();
    );
}
TEST(BinaryPrinterTest, PuttingKeyInArray)
{
    std::stringstream                     stream;
    ThorsAnvil::Serialize::BinaryPrinter  printer(stream, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream);

    printer.openDoc();
    printer.openArray();
    ASSERT_ANY_THROW(
        printer.addKey("This old house");
    );
}
#endif
#endif
