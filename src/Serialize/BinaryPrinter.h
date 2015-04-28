
#ifndef THORS_ANVIL_SERIALIZE_BINARY_PRINTER_H
#define THORS_ANVIL_SERIALIZE_BINARY_PRINTER_H
/*
 * BinaryPrinter<T>
 *  See documentation in BinaryParser.h
 */

#include "../../config.h"
#ifdef NETWORK_BYTE_ORDER

#include "Serialize.h"
#include "BinaryTHash.h"
#include "ThorBinaryRep/BinaryRep.h"

namespace TBin  = ThorsAnvil::BinaryRep;
namespace ThorsAnvil
{
    namespace Serialize
    {

template<typename T>
class BinaryPrinter: public PrinterInterface
{
    template<typename Out>
    void write(Out value)
    {
        output.write(reinterpret_cast<char const*>(&value), sizeof(Out));
    }
    void writeString(std::string const& value)
    {
        TBin::BinForm32    size            = value.size();
        write(TBin::host2Net(size));
        output.write(value.c_str(), size);
    }
    public:
        BinaryPrinter(std::ostream& output, OutputType characteristics = OutputType::Default)
            : PrinterInterface(output, characteristics)
        {}
        virtual void openDoc()                              override    {write(TBin::host2Net(static_cast<TBin::BinForm32>(thash<T>())));}
        virtual void closeDoc()                             override    {}

        virtual void openMap()                              override    {}
        virtual void closeMap()                             override    {}
        virtual void openArray(std::size_t size)            override    {write(TBin::host2Net(static_cast<TBin::BinForm32>(size)));}
        virtual void closeArray()                           override    {}

        virtual void addKey(std::string const& key)         override    {}

        virtual void addValue(short int value)              override    {write(TBin::host2Net(static_cast<TBin::BinForm16>(value)));}
        virtual void addValue(int value)                    override    {write(TBin::host2Net(static_cast<TBin::BinForm32>(value)));}
        virtual void addValue(long int value)               override    {write(TBin::host2Net(static_cast<TBin::BinForm64>(value)));}
        virtual void addValue(long long int value)          override    {write(TBin::host2Net(static_cast<TBin::BinForm128>(value)));}

        virtual void addValue(unsigned short int value)     override    {write(TBin::host2Net(static_cast<TBin::BinForm16>(value)));}
        virtual void addValue(unsigned int value)           override    {write(TBin::host2Net(static_cast<TBin::BinForm32>(value)));}
        virtual void addValue(unsigned long int value)      override    {write(TBin::host2Net(static_cast<TBin::BinForm64>(value)));}
        virtual void addValue(unsigned long long int value) override    {write(TBin::host2Net(static_cast<TBin::BinForm128>(value)));}

        virtual void addValue(float value)                  override    {write(TBin::host2NetIEEE(value));}
        virtual void addValue(double value)                 override    {write(TBin::host2NetIEEE(value));}
        virtual void addValue(long double value)            override    {write(TBin::host2NetIEEE(value));}

        virtual void addValue(bool value)                   override    {write(static_cast<unsigned char>(value));}

        virtual void addValue(std::string const& value)     override    {writeString(value);}
};

    }
}

#endif
#endif

