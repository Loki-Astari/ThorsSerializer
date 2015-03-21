
#ifndef THORS_ANVIL_SERIALIZE_BINARY_PRINTER_H
#define THORS_ANVIL_SERIALIZE_BINARY_PRINTER_H

#include "../../config.h"
#ifdef NETWORK_BYTE_ORDER

#include "Serialize.h"
#include "THash.h"
#include "ThorBinaryRep/BinaryRep.h"

namespace TBin  = ThorsAnvil::BinaryRep;
namespace ThorsAnvil
{
    namespace Serialize
    {

template<typename T>
class BinaryPrinter: public PrinterInterface
{
    void write(TBin::UInt128 value)
    {
        TBin::UInt128   networkValue    = TBin::thor_htobe128(value);
        output.write(reinterpret_cast<char const*>(&networkValue), 16);
    }
    void write(TBin::UInt64 value)
    {
        TBin::UInt64    networkValue    = TBin::thor_htobe64(value);
        output.write(reinterpret_cast<char const*>(&networkValue), 8);
    }
    void write(TBin::UInt32 value)
    {
        TBin::UInt32    networkValue    = htonl(value);
        output.write(reinterpret_cast<char const*>(&networkValue), 4);
    }
    void write(TBin::UInt16 value)
    {
        TBin::UInt16    networkValue    = htons(value);
        output.write(reinterpret_cast<char const*>(&networkValue), 2);
    }
    void write(unsigned char value)
    {
        output.write(reinterpret_cast<char const*>(&value), 1);
    }
    void write(std::string const& value)
    {
        TBin::UInt32    size            = value.size();
        write(size);
        output.write(value.c_str(), size);
    }
    public:
        BinaryPrinter(std::ostream& output, OutputType characteristics = OutputType::Default)
            : PrinterInterface(output, characteristics)
        {}
        virtual void openDoc()                              override    {write(static_cast<TBin::UInt32>(thash<T>()));}
        virtual void closeDoc()                             override {}

        virtual void openMap()                              override {}
        virtual void closeMap()                             override {}
        virtual void openArray()                            override {}
        virtual void closeArray()                           override {}

        virtual void addKey(std::string const& key)         override    {write(key);}

        virtual void addValue(short int value)              override    {write(static_cast<TBin::UInt16>(value));}
        virtual void addValue(int value)                    override    {write(static_cast<TBin::UInt32>(value));}
        virtual void addValue(long int value)               override    {write(static_cast<TBin::UInt64>(value));}
        virtual void addValue(long long int value)          override    {write(static_cast<TBin::UInt128>(value));}

        virtual void addValue(unsigned short int value)     override    {write(static_cast<TBin::UInt16>(value));}
        virtual void addValue(unsigned int value)           override    {write(static_cast<TBin::UInt32>(value));}
        virtual void addValue(unsigned long int value)      override    {write(static_cast<TBin::UInt64>(value));}
        virtual void addValue(unsigned long long int value) override    {write(static_cast<TBin::UInt128>(value));}

        virtual void addValue(float value)                  override    {write(TBin::convertIEEE(value));}
        virtual void addValue(double value)                 override    {write(TBin::convertIEEE(value));}
        virtual void addValue(long double value)            override    {write(TBin::convertIEEE(value));}

        virtual void addValue(bool value)                   override    {write(static_cast<unsigned char>(value));}

        virtual void addValue(std::string const& value)     override    {write(value);}
};

    }
}

#endif
#endif

