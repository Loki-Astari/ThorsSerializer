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
TEST(BinaryPrinterTest, floatToken)
{
    std::stringstream                     stream;
    ThorsAnvil::Serialize::BinaryPrinter<int>  printer(stream);

    printer.addValue(34.0F);    // 4    1 0 0 0 1 0. => S 0  E(5) => 1 0 0 0 0 1 0 0                Si 00010000     => 4208 0000
    printer.addValue(35.0);     // 8    1 0 0 0 1 1. => S 0  E(5) => 1 0 0 0 0 0 0 0 1 0 0          Si 00011000...  => 4041 8000 0000 0000
    printer.addValue(36.0L);    // 16   1 0 0 1 0 0. -> S 0  E(5) => 1 0 0 0 0 0 0 0 0 0 0 0 1 0 0  Si 00100000...  => 4004 2000 0000 0000 0000 0000 0000 0000


    std::string     result  = stream.str();
    EXPECT_EQ(28,   result.size());
    EXPECT_EQ(0,    result.compare(0, 28, "\x42\x08\x00\x00\x40\x41\x80\x00\x00\x00\x00\x00\x40\x04\x20\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00", 28));
}
TEST(BinaryPrinterTest, MapValues)
{
    std::stringstream                     stream;
    ThorsAnvil::Serialize::BinaryPrinter<int>  printer(stream);

    printer.openMap();
    printer.addKey("K1");
    printer.addValue(true);
    printer.addKey("K2");
    printer.addValue(false);
    printer.addKey("K3");
    printer.addValue(56);   // 11 1000 0x38
    printer.addKey("K4");
    printer.addValue(35.75); // 0x4041 E000 0000 0000
    printer.addKey("K6");
    printer.addValue(std::string("Astring"));
    printer.closeMap();
    printer.closeDoc();

    std::string     result  = stream.str();
    EXPECT_EQ(55,   result.size());
    EXPECT_EQ(0,    result.compare(0, 55, "\x00\x00\x00\x02K1\x01\x00\x00\x00\x02K2\x00\x00\x00\x00\x02K3\x00\x00\x00\x38\x00\x00\x00\x02K4\x40\x41\xE0\x00\x00\x00\x00\x00\x00\x00\x00\x02K6\x00\x00\x00\x07\x41string", 55));
}
TEST(BinaryPrinterTest, MapWithMapValues)
{
    std::stringstream                     stream;
    ThorsAnvil::Serialize::BinaryPrinter<int>  printer(stream);

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
    printer.addValue(35.75);
    printer.closeMap();
    printer.addKey("K6");
    printer.addValue(std::string("Astring"));
    printer.closeMap();
    printer.closeDoc();

    std::string     result  = stream.str();
    EXPECT_EQ(67,   result.size());
    EXPECT_EQ(0,    result.compare(0, 67, "\x00\x00\x00\x02K1\x00\x00\x00\x02K1\x01\x00\x00\x00\x02K2\x00\x00\x00\x00\x02K3\x00\x00\x00\x38\x00\x00\x00\x02K4\x00\x00\x00\x02K4\x40\x41\xE0\x00\x00\x00\x00\x00\x00\x00\x00\x02K6\x00\x00\x00\x07\x41string", 67));
}
TEST(BinaryPrinterTest, MapWithArrayValues)
{
    std::stringstream                     stream;
    ThorsAnvil::Serialize::BinaryPrinter<int>  printer(stream);

    printer.openMap();
    printer.addKey("K1");
    printer.openArray();
    printer.addValue(true);
    printer.addValue(false);
    printer.addValue(static_cast<unsigned short>(55));
    printer.addValue(56u);
    printer.addValue(57ul);
    printer.addValue(58ull);
    printer.addValue(60.f);     // V 1 1 1 1 0 0.    S 0  E 1 0 0 0 0 1 0 0                 Si 1110 0000... => 4270 0000
    printer.addValue(61.0L);    // V 1 1 1 1 0 1.    S 0  E 1 0 0 0 0 0 0 0 0 0 0 0 1 0 0   Si 1110 1000... => 4004 e800 0000 0000 0000 0000 0000 0000
    printer.closeArray();
    printer.addKey("K3");
    printer.addValue(56);
    printer.addKey("K4");
    printer.openArray();
    printer.addValue(35.75);
    printer.closeArray();
    printer.addKey("K6");
    printer.addValue(std::string("Astring"));
    printer.closeMap();
    printer.closeDoc();

    std::string     result  = stream.str();
    EXPECT_EQ(99,   result.size());
    EXPECT_EQ(0,    result.compare(0, 99, "\x00\x00\x00\x02K1"
                                            "\x01"
                                            "\x00"
                                            "\x00\x37"
                                            "\x00\x00\x00\x38"
                                            "\x00\x00\x00\x00\x00\x00\x00\x39"
                                            "\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x3a"
                                            "\x42\x70\x00\x00"
                                            "\x40\x04\xe8\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
                                          "\x00\x00\x00\x02K3\x00\x00\x00\x38"
                                          "\x00\x00\x00\x02K4\x40\x41\xE0\x00\x00\x00\x00\x00"
                                          "\x00\x00\x00\x02K6\x00\x00\x00\x07\x41string", 99));
}
TEST(BinaryPrinterTest, ArrayWithMapValues)
{
    std::stringstream                     stream;
    ThorsAnvil::Serialize::BinaryPrinter<int>  printer(stream);

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
    printer.addValue(35.75);
    printer.closeMap();
    printer.addValue(std::string("Astring"));
    printer.closeArray();
    printer.closeDoc();

    std::string     result  = stream.str();
    EXPECT_EQ(43,   result.size());
    EXPECT_EQ(0,    result.compare(0, 43, "\x00\x00\x00\x02K1\x01"
                                          "\x00\x00\x00\x02K2\x00"
                                          "\x00\x00\x00\x38"
                                          "\x00\x00\x00\x02K4\x40\x41\xE0\x00\x00\x00\x00\x00"
                                          "\x00\x00\x00\x07\x41string", 43));
}
TEST(BinaryPrinterTest, ArrayWithArrayValues)
{
    std::stringstream                     stream;
    ThorsAnvil::Serialize::BinaryPrinter<int>  printer(stream);

    printer.openArray();
    printer.openArray();
    printer.addValue(true);
    printer.addValue(false);
    printer.closeArray();
    printer.addValue(56);
    printer.openArray();
    printer.addValue(35.75);
    printer.closeArray();
    printer.addValue(std::string("Astring"));
    printer.closeArray();
    printer.closeDoc();

    std::string     result  = stream.str();
    EXPECT_EQ(25,   result.size());
    EXPECT_EQ(0,    result.compare(0, 25, "\x01\x00\x00\x00\x00\x38\x40\x41\xE0\x00\x00\x00\x00\x00\x00\x00\x00\x07\x41string", 25));
}
TEST(BinaryPrinterTest, CheckStreeamIsCompressed)
{
    std::stringstream                     stream;
    ThorsAnvil::Serialize::BinaryPrinter<int>  printer(stream, ThorsAnvil::Serialize::PrinterInterface::OutputType::Stream);

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
    printer.addValue(35.75);
    printer.closeMap();
    printer.addValue(std::string("Astring"));
    printer.closeArray();
    printer.closeDoc();

    std::string     result  = stream.str();
    EXPECT_EQ(43,   result.size());
    EXPECT_EQ(0,    result.compare(0, 43, "\x00\x00\x00\x02K1\x01\x00\x00\x00\x02K2\x00\x00\x00\x00\x38\x00\x00\x00\x02K4\x40\x41\xE0\x00\x00\x00\x00\x00\x00\x00\x00\x07\x41string", 43));
}
#endif
