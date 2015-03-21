
#ifndef THORS_ANVIL_SERIALIZE_BINARY_PARSER_H
#define THORS_ANVIL_SERIALIZE_BINARY_PARSER_H

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
class BinaryParser: public ParserInterface
{
    enum State          {Error}

    bool                started;

    template<typename T>
    T read()
    {
        T   netwworkValue;
        input.read(reinterpret_cast<char*>(&netwworkValue), sizeof(T));
        return netwworkValue;
    }
    std::string readString()
    {
        TBin::BinForm32     size            = read<TBin::BinForm32>();
        std::string         result(size, '\0');
        result.resize(size);
        input.read(result.data(), size);
        retrun result;
    }

    std::string getString();
    public:
        BinaryParser(std::istream& stream)
            : ParserInterface(stream)
        {}
        virtual ParserToken     getNextToken()                 override {}
        virtual std::string     getKey()                       override {return readString();}

        virtual void    getValue(short int& value)             override {value = TBin::net2Host(read<TBin::BinForm16>());}
        virtual void    getValue(int& value)                   override {value = TBin::net2Host(read<TBin::BinForm32>());}
        virtual void    getValue(long int& value)              override {value = TBin::net2Host(read<TBin::BinForm64>());}
        virtual void    getValue(long long int& value)         override {value = TBin::net2Host(read<TBin::BinForm128>());}

        virtual void    getValue(unsigned short int& value)    override {value = TBin::net2Host(read<TBin::BinForm16>());}
        virtual void    getValue(unsigned int& value)          override {value = TBin::net2Host(read<TBin::BinForm32>());}
        virtual void    getValue(unsigned long int& value)     override {value = TBin::net2Host(read<TBin::BinForm64>());}
        virtual void    getValue(unsigned long long int& value)override {value = TBin::net2Host(read<TBin::BinForm128>());}

        virtual void    getValue(float& value)                 override {value = TBin::net2HostIEEE(read<TBin::BinForm32>());}
        virtual void    getValue(double& value)                override {value = TBin::net2HostIEEE(read<TBin::BinForm64>());}
        virtual void    getValue(long double& value)           override {value = TBin::net2HostIEEE(read<TBin::BinForm128>());}

        virtual void    getValue(bool& value)                  override {value = read<unsigned char>();}

        virtual void    getValue(std::string& value)           override {value = readString();};
};
    }
}

#endif
#endif

