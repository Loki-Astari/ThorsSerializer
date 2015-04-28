
#ifndef THORS_ANVIL_SERIALIZE_BINARY_PARSER_H
#define THORS_ANVIL_SERIALIZE_BINARY_PARSER_H
/*
 * BinaryParser<T>
 *      This is used in conjunction with BinaryPrinter<T> 
 *
 *      Together these provide an implementation of:
 *          the ParserInterface for type T
 *          and PrinterInterface for type T
 *
 *      These Interfaces are used by Serializer and DeSerializer (see Serialize.h)
 *
 *      It uses ThorsAnvil::Serialize::Traits<T> to know what objects to pull from the stream.
 *      The binary representation stores only the data (no member names); because of this the
 *      data is stored/read in a particular order. To make sure that the data being read matches
 *      the data being stored a hash based on the Traits is generated and stored as a prefix to
 *      the data. This allows the parser to validate it is reading the same object that was stored.
 *      
 *      This uses BinaryParserUtil<T> to do that actual work of parsing and generating the appropriate
 *      tokens needed by a user of the ParserInterface. If an member is a serializeable user type `U` we
 *      push BinaryParserUtil<U> onto the stack for generating tokens. When all tokens have been generated
 *      the object is popped from the stack.
 */

#include "../../config.h"
#ifdef NETWORK_BYTE_ORDER

#include "Serialize.h"
#include "BinaryTHash.h"
#include "ThorBinaryRep/BinaryRep.h"
#include <iostream>
#include <vector>

namespace TBin  = ThorsAnvil::BinaryRep;
namespace ThorsAnvil
{
    namespace Serialize
    {


template<typename T>
class BinaryParser;
class BinaryParserUtilBase;

typedef ParserInterface::ParserToken                        ParserToken;
typedef std::vector<std::unique_ptr<BinaryParserUtilBase>>  ParserState;

class BinaryParserUtilBase
{
    private:
    ParserToken         nextToken;
    ParserToken         objClose;
    ParserToken         objNextValue;
    unsigned int        position;
    unsigned int        end;
    bool                root;
    bool                started;
    bool                finished;

    public:
        virtual ~BinaryParserUtilBase();
        BinaryParserUtilBase(bool root, ParserToken first, ParserToken last, ParserToken nextValue);
        virtual ParserToken getNextToken(ParserInterface& parser, ParserState& state);

                std::string getKey()                            {return getKeyFor(position);}
        virtual std::size_t readSize(ParserInterface&)          = 0;
        virtual std::string getKeyFor(std::size_t position)     = 0;
        virtual ParserToken pushNextState(std::size_t position, ParserInterface& parser, ParserState& state, ParserToken norm)    = 0;
};

template<typename T>
class BinaryParserMapParentCommon: public BinaryParserUtilBase
{
    protected:
        template<typename R, TraitType traitSpec = ThorsAnvil::Serialize::Traits<typename std::remove_reference<R>::type>::type>
        class MemberAdder;

    private:
    using Traits   = ThorsAnvil::Serialize::Traits<typename std::remove_reference<T>::type>;
    std::vector<std::string>    keys;
    ParserState                 utils;

                             void addMember(void*) {}
        template<typename P> void addMember(std::pair<char const*, P> const& token);

        template<typename Tuple, std::size_t... Seq> void fillMembers(Tuple const& members, std::index_sequence<Seq...> const&);
        template<typename... M>                      void fill(std::tuple<M...> const& members);
    public:
        BinaryParserMapParentCommon(bool root, ParserToken first, ParserToken last, ParserToken nextValue);

        std::size_t readSize(ParserInterface&)      override {return keys.size();}
        std::string getKeyFor(std::size_t position) override {return keys[position];}
        ParserToken pushNextState(std::size_t position, ParserInterface& parser, ParserState& state, ParserToken norm) override;
};

// Duck Class type for Map/Parent/Array/Value
// Each has a specialization that understands the interface:
//      readSize()
//      getKeyFor()
//      pushNextState()
//
//      Map/Parent Use the common base BinaryParserMapParentCommon to do the heavy lifting.
//      Array works slightly differently (and implements its own versions)
//      Value basically does nothing and is just required to compile.
template<typename T, TraitType traitSpec = ThorsAnvil::Serialize::Traits<typename std::remove_reference<T>::type>::type>
class BinaryParserUtil;

// Functions specific to Map
template<typename T>
class BinaryParserUtil<T, TraitType::Map>: public BinaryParserMapParentCommon<T>
{
    public:
        BinaryParserUtil(bool root = true);
};

// Functions specific to Parent (Slightly complicated Map)
template<typename T>
class BinaryParserUtil<T, TraitType::Parent>: public BinaryParserMapParentCommon<T>
{
    public:
        BinaryParserUtil(bool root = true);
};

// Functions specific to Array
template<typename T>
class BinaryParserUtil<T, TraitType::Array>: public BinaryParserUtilBase
{
    using Traits   = ThorsAnvil::Serialize::Traits<typename std::remove_reference<T>::type>;
    public:
        BinaryParserUtil(bool root = true);
        std::size_t readSize(ParserInterface&)      override;
        std::string getKeyFor(std::size_t) override {throw std::runtime_error("Should Never Get Here");}
        ParserToken pushNextState(std::size_t, ParserInterface& parser, ParserState& state, ParserToken norm) override;
};

template<typename T>
class BinaryParserUtil<T, TraitType::Value>: public BinaryParserUtilBase
{
    public:
        BinaryParserUtil(bool root = true);
        std::size_t readSize(ParserInterface&)      override    {return 1;}
        std::string getKeyFor(std::size_t)          override    {return "";}
        ParserToken pushNextState(std::size_t, ParserInterface&, ParserState&, ParserToken norm) override
        {   return norm;
        }
};

template<typename T>
class BinaryParser: public ParserInterface
{
    using Traits   = ThorsAnvil::Serialize::Traits<T>;

    ParserState  state;

    template<typename Obj>
    Obj read()
    {
        Obj   netwworkValue;
        input.read(reinterpret_cast<char*>(&netwworkValue), sizeof(Obj));
        if (!input || input.gcount() != sizeof(Obj))
        {
            throw std::runtime_error("Unexpected read failure");
        }
        return netwworkValue;
    }
    std::string readString()
    {
        unsigned int size;
        getValue(size);
        std::string     result(size, '\0');
        result.resize(size);
        input.read(&result[0], size);
        return result;
    }
    public:
        BinaryParser(std::istream& stream)
            : ParserInterface(stream)
        {
            std::size_t hash   = TBin::net2Host(read<TBin::BinForm32>());
            std::size_t expect = std::uint32_t(thash<T>());
            if (hash != expect) {
                throw "Fail";
            }
            
            state.emplace_back(new BinaryParserUtil<T>());
        }
        virtual ParserToken     getNextToken()                 override
        {
            if (!state.empty())
            {
                return state.back()->getNextToken(*this, state);
            }
            return ParserToken::Error;
        }
        virtual std::string     getKey()                       override {return state.back()->getKey();}

        virtual void    getValue(short int& value)             override {value = TBin::net2Host(read<TBin::BinForm16>());}
        virtual void    getValue(int& value)                   override {value = TBin::net2Host(read<TBin::BinForm32>());}
        virtual void    getValue(long int& value)              override {value = TBin::net2Host(read<TBin::BinForm64>());}
        virtual void    getValue(long long int& value)         override {value = static_cast<unsigned long long int>(TBin::net2Host(read<TBin::BinForm128>()));}

        virtual void    getValue(unsigned short int& value)    override {value = TBin::net2Host(read<TBin::BinForm16>());}
        virtual void    getValue(unsigned int& value)          override {value = TBin::net2Host(read<TBin::BinForm32>());}
        virtual void    getValue(unsigned long int& value)     override {value = TBin::net2Host(read<TBin::BinForm64>());}
        virtual void    getValue(unsigned long long int& value)override {value = static_cast<unsigned long long int>(TBin::net2Host(read<TBin::BinForm128>()));}

        virtual void    getValue(float& value)                 override {value = TBin::net2HostIEEE<float>(read<TBin::BinForm32>());}
        virtual void    getValue(double& value)                override {value = TBin::net2HostIEEE<double>(read<TBin::BinForm64>());}
        virtual void    getValue(long double& value)           override {value = TBin::net2HostIEEE<long double>(read<TBin::BinForm128>());}

        virtual void    getValue(bool& value)                  override {value = read<unsigned char>();}

        virtual void    getValue(std::string& value)           override {value = readString();};
};

    }
}

#endif
#endif

