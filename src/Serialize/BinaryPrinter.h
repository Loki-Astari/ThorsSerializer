
#ifndef THORS_ANVIL_SERIALIZE_BINARY_PRINTER_H
#define THORS_ANVIL_SERIALIZE_BINARY_PRINTER_H

#include "../../config.h"
#ifdef NETWORK_BYTE_ORDER

#include "Serialize.h"
#include "THash.h"

namespace ThorsAnvil
{
    namespace Serialize
    {

template<typename T>
class BinaryPrinter: public PrinterInterface
{
    static_assert(sizeof(short)       * CHAR_BIT <= 16, "Binary interface assumes short       are not larger than 16 bits");
    static_assert(sizeof(int)         * CHAR_BIT <= 32, "Binary interface assumes int         are not larger than 32 bits");
    static_assert(sizeof(long)        * CHAR_BIT <= 64, "Binary interface assumes long        are not larger than 64 bits");
    static_assert(sizeof(long long)   * CHAR_BIT <= 64, "Binary interface assumes long long   are not larger than 64 bits");

    static_assert(sizeof(float)       * CHAR_BIT <= 32, "Binary interface assumes float       are not larger than 32  bits");
    static_assert(sizeof(double)      * CHAR_BIT <= 64, "Binary interface assumes double      are not larger than 64  bits");
    static_assert(sizeof(long double) * CHAR_BIT <= 128, "Binary interface assumes long double are not larger than 80  bits");

    static_assert(static_cast<unsigned char>(true)  == '\x01',    "Binary interface assumes true has value of 1");
    static_assert(static_cast<unsigned char>(false) == '\x00',    "Binary interface assumes false has value of 0");

    static_assert(std::numeric_limits<float>::is_iec559,       "Binary interface assumes float       is IEEE754");
    static_assert(std::numeric_limits<double>::is_iec559,      "Binary interface assumes double      is IEEE754");
    static_assert(std::numeric_limits<long double>::is_iec559, "Binary interface assumes long double is IEEE754");


    void write(uint64_t value)
    {
        uint32_t    lowOrder        = value & 0x00000000FFFFFFFFLL;
        uint32_t    highOrder       = value >> 32;
        write(highOrder);
        write(lowOrder);
    }
    void write(uint32_t value)
    {
        uint32_t    networkValue    = htonl(value);
        output.write(reinterpret_cast<char const*>(&networkValue), 4);
    }
    void write(uint16_t value)
    {
        uint16_t    networkValue    = htons(value);
        output.write(reinterpret_cast<char const*>(&networkValue), 2);
    }
    void write(unsigned char value)
    {
        output.write(reinterpret_cast<char const*>(&value), 1);
    }
    void write(std::string const& value)
    {
        uint32_t    size            = value.size();
        write(size);
        output.write(value.c_str(), size);
    }
    public:
        BinaryPrinter(std::ostream& output, OutputType characteristics = OutputType::Default)
            : PrinterInterface(output, characteristics)
        {}
        virtual void openDoc()                              override    {write(static_cast<uint32_t>(thash<T>()));}
        virtual void closeDoc()                             override {}

        virtual void openMap()                              override {}
        virtual void closeMap()                             override {}
        virtual void openArray()                            override {}
        virtual void closeArray()                           override {}

        virtual void addKey(std::string const& key)         override    {write(key);}

        virtual void addValue(short int value)              override    {write(static_cast<uint16_t>(value));}
        virtual void addValue(int value)                    override    {write(static_cast<uint32_t>(value));}
        virtual void addValue(long int value)               override    {write(static_cast<uint64_t>(value));}
        virtual void addValue(long long int value)          override    {write(static_cast<uint64_t>(value));}

        virtual void addValue(unsigned short int value)     override    {write(static_cast<uint16_t>(value));}
        virtual void addValue(unsigned int value)           override    {write(static_cast<uint32_t>(value));}
        virtual void addValue(unsigned long int value)      override    {write(static_cast<uint64_t>(value));}
        virtual void addValue(unsigned long long int value) override    {write(static_cast<uint64_t>(value));}

        virtual void addValue(float value)                  override    {write(static_cast<uint32_t>(value));}
        virtual void addValue(double value)                 override    {write(static_cast<uint64_t>(value));}
        virtual void addValue(long double value)            override    {write(static_cast<uint64_t>(value));}

        virtual void addValue(bool value)                   override    {write(static_cast<unsigned char>(value));}

        virtual void addValue(std::string const& value)     override    {write(value);}
};

    }
}

#endif
#endif

