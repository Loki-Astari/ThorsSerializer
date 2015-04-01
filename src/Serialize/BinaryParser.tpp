
#ifndef THORS_ANVIL_SERIALIZE_BINARY_PARSER_TPP
#define THORS_ANVIL_SERIALIZE_BINARY_PARSER_TPP

#include "../../config.h"
#ifdef NETWORK_BYTE_ORDER

namespace ThorsAnvil
{
    namespace Serialize
    {

template<typename T, TraitType traitSpec>
BinaryParserUtil<T, traitSpec>::BinaryParserUtil(bool root)
    : BinaryParserUtilBase( root,
                            ParserToken::MapStart,
                            ParserToken::MapEnd,
                            ParserToken::Key)
{
    fill(Traits::getMembers());
}

template<typename T, TraitType traitSpec>
template<typename P>
void BinaryParserUtil<T, traitSpec>::addMember(std::pair<char const*, P> const& token)
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

template<typename T, TraitType traitSpec>
template<typename Tuple, std::size_t... Seq>
void BinaryParserUtil<T, traitSpec>::fillMembers(Tuple const& members, std::index_sequence<Seq...> const&)
{
    std::make_tuple((addMember(std::get<Seq>(members)),1)...);
}

template<typename T, TraitType traitSpec>
template<typename... M>
void BinaryParserUtil<T, traitSpec>::fill(std::tuple<M...> const& members)
{
    fillMembers(members, std::make_index_sequence<sizeof...(M)>());
}

template<typename T>
std::size_t BinaryParserUtil<T, TraitType::Array>::readSize(ParserInterface& parent)
{
    unsigned int    result;
    parent.getValue(result);
    return result;
}

template<typename T, TraitType traitSpec>
ParserToken BinaryParserUtil<T, traitSpec>
    ::pushNextState(    std::size_t         position,
                        ParserInterface&    parser,
                        ParserState&        state,
                        ParserToken         norm)
{
    if (utils[position].get())
    {
        state.push_back(std::move(utils[position]));
        return state.back()->getNextToken(parser, state);
    }
    return norm;
}

template<typename T>
BinaryParserUtil<T, TraitType::Array>::BinaryParserUtil(bool root)
    : BinaryParserUtilBase( root,
                            ParserToken::ArrayStart,
                            ParserToken::ArrayEnd,
                            ParserToken::Value)
{}

template<typename T>
ParserToken BinaryParserUtil<T, TraitType::Array>
    ::pushNextState(std::size_t, ParserInterface& parser, ParserState& state, ParserToken norm)
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

    }
}

#endif
#endif

