
#ifndef THORS_ANVIL_SERIALIZE_BINARY_PARSER_TPP
#define THORS_ANVIL_SERIALIZE_BINARY_PARSER_TPP

#include "../../config.h"
#ifdef NETWORK_BYTE_ORDER

#include "Traits.h"

namespace ThorsAnvil
{
    namespace Serialize
    {


template<typename T>
template<typename R>
class BinaryParserMapParentCommon<T>::MemberAdder<R, TraitType::Map>
{
    public:
    void operator()(BinaryParserMapParentCommon<T>& obj)
    {   
        using Traits = ThorsAnvil::Serialize::Traits<typename std::remove_reference<R>::type>;
        obj.fill(Traits::getMembers());
    }
};

template<typename T>
template<typename R>
class BinaryParserMapParentCommon<T>::MemberAdder<R, TraitType::Parent>
{
    public:
    void operator()(BinaryParserMapParentCommon<T>& obj)
    {   
        MemberAdder<typename ThorsAnvil::Serialize::Traits<T>::Parent>    addParent;
        addParent(obj);

        using Traits = ThorsAnvil::Serialize::Traits<typename std::remove_reference<R>::type>;
        obj.fill(Traits::getMembers());
    }
};

template<typename T>
BinaryParserMapParentCommon<T>::BinaryParserMapParentCommon(bool root, ParserToken first, ParserToken last, ParserToken nextValue)
    : BinaryParserUtilBase( root, first, last, nextValue)
{
    MemberAdder<T>  addMembers;
    addMembers(*this);
}


template<typename T>
template<typename P>
void BinaryParserMapParentCommon<T>::addMember(std::pair<char const*, P> const& token)
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

template<typename T>
template<typename Tuple, std::size_t... Seq>
void BinaryParserMapParentCommon<T>::fillMembers(Tuple const& members, std::index_sequence<Seq...> const&)
{
    std::make_tuple((addMember(std::get<Seq>(members)),1)...);
}

template<typename T>
template<typename... M>
void BinaryParserMapParentCommon<T>::fill(std::tuple<M...> const& members)
{
    fillMembers(members, std::make_index_sequence<sizeof...(M)>());
}

template<typename T>
ParserToken BinaryParserMapParentCommon<T>
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
BinaryParserUtil<T, TraitType::Map>::BinaryParserUtil(bool root)
    : BinaryParserMapParentCommon<T>(root,
                                    ParserToken::MapStart,
                                    ParserToken::MapEnd,
                                    ParserToken::Key)
{}

template<typename T>
BinaryParserUtil<T, TraitType::Parent>::BinaryParserUtil(bool root)
    : BinaryParserMapParentCommon<T>(root,
                                    ParserToken::MapStart,
                                    ParserToken::MapEnd,
                                    ParserToken::Key)
{}

template<typename T>
BinaryParserUtil<T, TraitType::Array>::BinaryParserUtil(bool root)
    : BinaryParserUtilBase( root,
                            ParserToken::ArrayStart,
                            ParserToken::ArrayEnd,
                            ParserToken::Value)
{}

template<typename T>
BinaryParserUtil<T, TraitType::Value>::BinaryParserUtil(bool root)
    : BinaryParserUtilBase( root,
                            ParserToken::Value,
                            ParserToken::DocEnd,
                            ParserToken::Error)
{}

template<typename T>
std::size_t BinaryParserUtil<T, TraitType::Array>::readSize(ParserInterface& parent)
{
    unsigned int    result;
    parent.getValue(result);
    return result;
}

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

