
#ifndef THORS_ANVIL_SERIALIZE_BINARY_PARSER_H
#define THORS_ANVIL_SERIALIZE_BINARY_PARSER_H

#include "../../config.h"
#ifdef NETWORK_BYTE_ORDER

#include "Serialize.h"
#include "THash.h"
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

class BinaryParserUtilBase
{
    public:
    typedef ParserInterface::ParserToken    ParserToken;

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
        virtual ~BinaryParserUtilBase() {}
        BinaryParserUtilBase(bool root, ParserToken first, ParserToken last, ParserToken nextValue)
            : nextToken(first)
            , objClose(last)
            , objNextValue(nextValue)
            , position(0)
            , end(0)
            , root(root)
            , started(false)
            , finished(false)
        {}
        virtual ParserToken getNextToken(ParserInterface& parser, std::vector<std::unique_ptr<BinaryParserUtilBase>>& state)
        {
            if (!started)
            {
                started     = true;
                end         = readSize(parser);
                if (root)
                {
                    return ParserToken::DocStart;
                }
            }
            if (nextToken == ParserToken::MapStart || nextToken == ParserToken::ArrayStart)
            {
                ParserToken     result  = nextToken;
                nextToken = objNextValue;
                return result;
            }
            if (position < end)
            {
                switch(nextToken)
                {
                    case ParserToken::Key:
                        nextToken = ParserToken::Value;
                        return ParserToken::Key;
                    case ParserToken::Value:
                        nextToken = objNextValue;
                        ++position;
                        return pushNextState(position - 1, parser, state, ParserToken::Value);
                    default:
                        throw std::runtime_error("KKK");
                }
            }
            if (!finished)
            {
                finished    = true;
                if (!root)
                {
                    state.pop_back();
                }
                return objClose;
            }
            state.pop_back();
            return ParserToken::DocEnd;
        }
        std::string getKey()                            {return getKeyFor(position);}

        virtual std::size_t readSize(ParserInterface&)          = 0;
        virtual std::string getKeyFor(std::size_t position)     = 0;
        virtual ParserToken pushNextState(std::size_t position, ParserInterface& parser, std::vector<std::unique_ptr<BinaryParserUtilBase>>& state, ParserToken norm)    = 0;
};

// Default: Functions specific to Map
template<typename T, TraitType traitSpec = ThorsAnvil::Serialize::Traits<typename std::remove_reference<T>::type>::type>
class BinaryParserUtil: public BinaryParserUtilBase
{
    using Traits   = ThorsAnvil::Serialize::Traits<typename std::remove_reference<T>::type>;
    std::vector<std::string>                            keys;
    std::vector<std::unique_ptr<BinaryParserUtilBase>>  utils;

        template<typename P>
        void addMember(std::pair<char const*, P> const& token)
        {
            keys.emplace_back(token.first);
            typedef decltype(((T*)nullptr)->*(token.second))            DestTypeBase;
            typedef typename std::remove_reference<DestTypeBase>::type  DestType;

            if (    ThorsAnvil::Serialize::Traits<DestType>::type == TraitType::Map 
                ||  ThorsAnvil::Serialize::Traits<DestType>::type == TraitType::Array
                ||  ThorsAnvil::Serialize::Traits<DestType>::type == TraitType::Parent)
            {
                utils.emplace_back(new BinaryParserUtil<DestType>(false));
            }
            else
            {
                utils.emplace_back(nullptr);
            }
        }
        void addMember(void*) {}
        template<typename Tuple, std::size_t... Seq>
        void fillMembers(Tuple const& members, std::index_sequence<Seq...> const&)
        {
            std::make_tuple((addMember(std::get<Seq>(members)),1)...);
        }
        template<typename... M>
        void fill(std::tuple<M...> const& members)
        {
            fillMembers(members, std::make_index_sequence<sizeof...(M)>());
        }
    public:
        BinaryParserUtil(bool root = true)
            : BinaryParserUtilBase( root,
                                    ParserInterface::ParserToken::MapStart,
                                    ParserInterface::ParserToken::MapEnd,
                                    ParserInterface::ParserToken::Key)
        {
            fill(Traits::getMembers());
        }
        std::size_t readSize(ParserInterface&)      override {return keys.size();}
        std::string getKeyFor(std::size_t position) override {return keys[position];}
        ParserToken pushNextState(std::size_t position, ParserInterface& parser, std::vector<std::unique_ptr<BinaryParserUtilBase>>& state, ParserToken norm) override
        {
            if (utils[position].get())
            {
                state.push_back(std::move(utils[position]));
                return state.back()->getNextToken(parser, state);
            }
            return norm;
        }
};

// Functions specific to Array
template<typename T>
class BinaryParserUtil<T, TraitType::Array>: public BinaryParserUtilBase
{
    using Traits   = ThorsAnvil::Serialize::Traits<T>;
    public:
        BinaryParserUtil(bool root = true)
            : BinaryParserUtilBase( root,
                                    ParserInterface::ParserToken::ArrayStart,
                                    ParserInterface::ParserToken::ArrayEnd,
                                    ParserInterface::ParserToken::Value)
        {}
        std::size_t readSize(ParserInterface&)      override;
        std::string getKeyFor(std::size_t) override {throw std::runtime_error("Should Never Get Here");}
        ParserToken pushNextState(std::size_t, ParserInterface& parser, std::vector<std::unique_ptr<BinaryParserUtilBase>>& state, ParserToken norm) override
        {
            typedef typename T::value_type       ChildType;
            if (    ThorsAnvil::Serialize::Traits<ChildType>::type == TraitType::Map 
                ||  ThorsAnvil::Serialize::Traits<ChildType>::type == TraitType::Array
                ||  ThorsAnvil::Serialize::Traits<ChildType>::type == TraitType::Parent)
            {
                state.emplace_back(new BinaryParserUtil<ChildType>(false));
                return state.back()->getNextToken(parser, state);
            }
            return norm;
        }
};
template<typename T>
class BinaryParserUtil<T, TraitType::Value>: public BinaryParserUtilBase
{
    public:
        BinaryParserUtil(bool root = true)
            : BinaryParserUtilBase( root,
                                    ParserInterface::ParserToken::Error,
                                    ParserInterface::ParserToken::Error,
                                    ParserInterface::ParserToken::Error)
        {}
        std::size_t readSize(ParserInterface&)      override    {return 0;}
        std::string getKeyFor(std::size_t)          override    {return "";}
        ParserToken pushNextState(std::size_t, ParserInterface&, std::vector<std::unique_ptr<BinaryParserUtilBase>>&, ParserToken norm) override
        {   return norm;
        }
};

template<typename T>
class BinaryParser: public ParserInterface
{
    using Traits   = ThorsAnvil::Serialize::Traits<T>;

    std::vector<std::unique_ptr<BinaryParserUtilBase>>  state;

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
template<typename T>
std::size_t BinaryParserUtil<T, TraitType::Array>::readSize(ParserInterface& parent)
{
    unsigned int    result;
    parent.getValue(result);
    return result;
}

    }
}

#endif
#endif

