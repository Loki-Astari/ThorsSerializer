
#ifndef THORS_ANVIL_SERIALIZE_BINARY_PRINTER_H
#define THORS_ANVIL_SERIALIZE_BINARY_PRINTER_H

#include "../../config.h"
#ifdef NETWORK_BYTE_ORDER

#include "Serialize.h"
#include "THash.h"
#include "ThorBinaryRep/BinaryRep.h"

namespace ThorsAnvil
{
    namespace Serialize
    {

template<typename T>
class BinaryPrinter: public PrinterInterface
{
    void write(UInt128 value)
    {
        UInt128   networkValue    = thor_htobe128(value);
        output.write(reinterpret_cast<char const*>(&networkValue), 16);
    }
    void write(UInt64 value)
    {
        UInt64    networkValue    = thor_htobe64(value);
        output.write(reinterpret_cast<char const*>(&networkValue), 8);
    }
    void write(UInt32 value)
    {
        UInt32    networkValue    = htonl(value);
        output.write(reinterpret_cast<char const*>(&networkValue), 4);
    }
    void write(UInt16 value)
    {
        UInt16    networkValue    = htons(value);
        output.write(reinterpret_cast<char const*>(&networkValue), 2);
    }
    void write(unsigned char value)
    {
        output.write(reinterpret_cast<char const*>(&value), 1);
    }
    void write(std::string const& value)
    {
        UInt32    size            = value.size();
        write(size);
        output.write(value.c_str(), size);
    }
    public:
        BinaryPrinter(std::ostream& output, OutputType characteristics = OutputType::Default)
            : PrinterInterface(output, characteristics)
        {}
        virtual void openDoc()                              override    {write(static_cast<UInt32>(thash<T>()));}
        virtual void closeDoc()                             override {}

        virtual void openMap()                              override {}
        virtual void closeMap()                             override {}
        virtual void openArray()                            override {}
        virtual void closeArray()                           override {}

        virtual void addKey(std::string const& key)         override    {write(key);}

        virtual void addValue(short int value)              override    {write(static_cast<UInt16>(value));}
        virtual void addValue(int value)                    override    {write(static_cast<UInt32>(value));}
        virtual void addValue(long int value)               override    {write(static_cast<UInt64>(value));}
        virtual void addValue(long long int value)          override    {write(static_cast<UInt128>(value));}

        virtual void addValue(unsigned short int value)     override    {write(static_cast<UInt16>(value));}
        virtual void addValue(unsigned int value)           override    {write(static_cast<UInt32>(value));}
        virtual void addValue(unsigned long int value)      override    {write(static_cast<UInt64>(value));}
        virtual void addValue(unsigned long long int value) override    {write(static_cast<UInt128>(value));}

        virtual void addValue(float value)                  override    {write(convertIEEE(value));}
        virtual void addValue(double value)                 override    {write(convertIEEE(value));}
        virtual void addValue(long double value)            override    {write(convertIEEE(value));}

        virtual void addValue(bool value)                   override    {write(static_cast<unsigned char>(value));}

        virtual void addValue(std::string const& value)     override    {write(value);}
};

    }
}

#endif
#endif

