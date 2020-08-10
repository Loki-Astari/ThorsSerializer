#include "SerializeConfig.h"
#include "BsonPrinter.h"
#include "GitUtility/ieee754_types.h"
#include <iomanip>
#include <algorithm>
#include <boost/endian/conversion.hpp>

using namespace ThorsAnvil::Serialize;

namespace
{
}

HEADER_ONLY_INCLUDE
BsonPrinter::BsonPrinter(std::ostream& output, PrinterConfig config)
    : PrinterInterface(output, config)
{}

HEADER_ONLY_INCLUDE bool BsonPrinter::printerUsesSize()                         {return true;}

HEADER_ONLY_INCLUDE void BsonPrinter::openDoc()                                 {}
HEADER_ONLY_INCLUDE void BsonPrinter::closeDoc()                                {}

// Add a new Key
HEADER_ONLY_INCLUDE
void BsonPrinter::addKey(std::string const& key)
{
    currentKey = key;
}

HEADER_ONLY_INCLUDE
void BsonPrinter::writeKey(char value)
{
    if (!currentKey.empty())
    {
        output.write(&value, 1);
        output.write(currentKey.c_str(), currentKey.size() + 1);
    }
}

template<typename Int>
void BsonPrinter::writeSize(Int size)
{
    Int docSize = boost::endian::native_to_little(size);
    output.write(reinterpret_cast<char*>(&docSize), sizeof(docSize));
}

// MAP
HEADER_ONLY_INCLUDE
std::size_t BsonPrinter::getSizeMap(std::size_t count)
{
    /*
     * A map is a document:
     *      <size 4bytes> <Element-List> <Terminator 1byte>
     * Each element int the <Element-List> consists of:
     *      <type 1byte> <e-name (size accounted for) + '\0' 1byte> <object (size accounted for)>
     */
    return 4 + (count * (1 + 1)) + 1;
}
HEADER_ONLY_INCLUDE
void BsonPrinter::openMap(std::size_t size)
{
    writeKey('\x03');
    writeSize<std::int32_t>(size);
}

HEADER_ONLY_INCLUDE
void BsonPrinter::closeMap()
{
    output.write("",1);
}

// ARRAY
HEADER_ONLY_INCLUDE
std::size_t BsonPrinter::getSizeArray(std::size_t count)
{
    /*
     * A map is a document:
     *      <size 4bytes> <Element-List> <Terminator 1byte>
     * Each element int the <Element-List> consists of:
     *      <type 1byte> <e-name (which is a string of the index number) + '\0' 1byte> <object (size accounted for)>
     */
     /*
      * This is the same as Map (see above)
      * The difference we have not accounted for the string that define the index
      * So we must calculate the string length need to store all the index strings.
      */
    std::size_t indexTotalStringLen     = 0;
    std::size_t sizeLeft                = count;
    std::size_t nextLevel               = 10;
    std::size_t numberOfDigitsThisLevel = 1;
    std::size_t accountedFor            = 0;

    while (sizeLeft > 0)
    {
        if (count <= nextLevel)
        {
            indexTotalStringLen += (count - accountedFor) * numberOfDigitsThisLevel;
            break;
        }
        indexTotalStringLen += (nextLevel - accountedFor) * numberOfDigitsThisLevel;
        accountedFor            += nextLevel;
        numberOfDigitsThisLevel += 1;
        nextLevel               *= 10;
    }

    return getSizeMap(count) + indexTotalStringLen;
}
HEADER_ONLY_INCLUDE
void BsonPrinter::openArray(std::size_t size)
{
    writeKey('\x04');
    writeSize<std::int32_t>(size);
}

HEADER_ONLY_INCLUDE
void BsonPrinter::closeArray()
{
    output.write("",1);
}

template<std::size_t Size>
class IntWriter;

template<>
class IntWriter<2>
{
    BsonPrinter& printer;
    public:
        IntWriter(BsonPrinter& printer)
            : printer(printer)
    {}

    void operator()(std::int16_t value)
    {
        printer.writeKey('\x10');
        printer.writeSize<std::int32_t>(value);
    }
};
template<>
class IntWriter<4>
{
    BsonPrinter& printer;
    public:
        IntWriter(BsonPrinter& printer)
            : printer(printer)
    {}

    void operator()(std::int32_t value)
    {
        printer.writeKey('\x10');
        printer.writeSize<std::int32_t>(value);
    }
};

template<>
class IntWriter<8>
{
    BsonPrinter& printer;
    public:
        IntWriter(BsonPrinter& printer)
            : printer(printer)
    {}

    void operator()(std::int64_t value)
    {
        printer.writeKey('\x12');
        printer.writeSize<std::int64_t>(value);
    }
};

HEADER_ONLY_INCLUDE
template<std::size_t Size, typename Int>
void BsonPrinter::writeInt(Int value)
{
    IntWriter<Size>     writer(*this);
    writer(value);
}


HEADER_ONLY_INCLUDE std::size_t BsonPrinter::getSizeValue(short int)                {return sizeof(short int);}
HEADER_ONLY_INCLUDE std::size_t BsonPrinter::getSizeValue(int)                      {return sizeof(int);}
HEADER_ONLY_INCLUDE std::size_t BsonPrinter::getSizeValue(long int)                 {return sizeof(long int);}
HEADER_ONLY_INCLUDE std::size_t BsonPrinter::getSizeValue(long long int)            {return sizeof(long long int);}
HEADER_ONLY_INCLUDE std::size_t BsonPrinter::getSizeValue(unsigned short int)       {return sizeof(unsigned short int);}
HEADER_ONLY_INCLUDE std::size_t BsonPrinter::getSizeValue(unsigned int)             {return sizeof(unsigned int);}
HEADER_ONLY_INCLUDE std::size_t BsonPrinter::getSizeValue(unsigned long int)        {return sizeof(unsigned long int);}
HEADER_ONLY_INCLUDE std::size_t BsonPrinter::getSizeValue(unsigned long long int)   {return sizeof(unsigned long long int);}
HEADER_ONLY_INCLUDE void BsonPrinter::addValue(short int value)                     {writeInt<sizeof(short int)>(value);}
HEADER_ONLY_INCLUDE void BsonPrinter::addValue(int value)                           {writeInt<sizeof(int)>(value);}
HEADER_ONLY_INCLUDE void BsonPrinter::addValue(long int value)                      {writeInt<sizeof(long int)>(value);}
HEADER_ONLY_INCLUDE void BsonPrinter::addValue(long long int value)                 {writeInt<sizeof(long long int)>(value);}
HEADER_ONLY_INCLUDE void BsonPrinter::addValue(unsigned short int value)            {writeInt<sizeof(unsigned short int)>(value);}
HEADER_ONLY_INCLUDE void BsonPrinter::addValue(unsigned int value)                  {writeInt<sizeof(unsigned int)>(value);}
HEADER_ONLY_INCLUDE void BsonPrinter::addValue(unsigned long int value)             {writeInt<sizeof(unsigned long int)>(value);}
HEADER_ONLY_INCLUDE void BsonPrinter::addValue(unsigned long long int value)        {writeInt<sizeof(unsigned long long int)>(value);}

HEADER_ONLY_INCLUDE std::size_t BsonPrinter::getSizeValue(float)                    {return 8;}
HEADER_ONLY_INCLUDE std::size_t BsonPrinter::getSizeValue(double)                   {return 8;}
HEADER_ONLY_INCLUDE std::size_t BsonPrinter::getSizeValue(long double)              {return 16;}

HEADER_ONLY_INCLUDE
void BsonPrinter::addValue(float value)
{
    writeKey('\x01');
    IEEE_754::_2008::Binary<64> outVal = value;
    output.write(reinterpret_cast<char*>(&outVal), 8);
}
// Double
HEADER_ONLY_INCLUDE
void BsonPrinter::addValue(double value)
{
    writeKey('\x01');
    IEEE_754::_2008::Binary<64> outVal = value;
    output.write(reinterpret_cast<char*>(&outVal), 8);
}
HEADER_ONLY_INCLUDE void BsonPrinter::addValue(long double /*value*/)
{
#if 0
    writeKey('\x13');
    IEEE_754::_2008::Binary<128> outVal = value;
    output.write(reinterpret_cast<char*>(&outVal), 16);
#endif
}

// Bool
HEADER_ONLY_INCLUDE
std::size_t BsonPrinter::getSizeValue(bool)
{
    return 1;
}
HEADER_ONLY_INCLUDE
void BsonPrinter::addValue(bool value)
{
    writeKey('\x08');
    char outVal = (value ? '\x01' : '\x00');
    output.write(&outVal, 1);
}

// String
HEADER_ONLY_INCLUDE
std::size_t BsonPrinter::getSizeValue(std::string const& value)
{
    return 4 + value.size() + 1;
}
HEADER_ONLY_INCLUDE
void BsonPrinter::addValue(std::string const& value)
{
    writeKey('\x02');
    writeSize<std::int32_t>(value.size() + 1);
    output.write(value.c_str(), value.size() + 1);
}


// nullptr
HEADER_ONLY_INCLUDE
std::size_t BsonPrinter::getSizeNull()
{
    return 0;
}
HEADER_ONLY_INCLUDE
void BsonPrinter::addNull()
{
    writeKey('\x0A');
}

// RAW data saved as binary
HEADER_ONLY_INCLUDE void BsonPrinter::addRawValue(std::string const& value)
{
    writeKey('\x05');    // binary
    writeSize<std::int32_t>(value.size());
    output.write("\x80", 1);
    output.write(value.c_str(), value.size());
}
