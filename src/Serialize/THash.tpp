
#ifndef THORS_ANVIL_SERIALIZE_THASH_TPP
#define THORS_ANVIL_SERIALIZE_THASH_TPP

#include "Traits.h"
#include <string>


namespace ThorsAnvil
{
    namespace Serialize
    {

inline std::size_t thash(std::size_t& start, std::string const& input)
{
    static constexpr std::size_t    Mult = 37;
    for(auto loop: input)
    {
        start = start * Mult + loop;
    }
    return start;
}

template<typename T>
struct TraitsHash;


template<typename T, typename M>
inline std::size_t thash(std::size_t& start, std::pair<char const*, M T::*> const& member)
{
    TraitsHash<M>   typeHash;
    start   = typeHash(start);
    return thash(start, member.first);
}

template<typename T>
inline std::size_t thash()
{
    std::size_t     result = 0;
    TraitsHash<T>   hasher;
    return hasher(result);
}

template<typename T>
struct TraitsHash
{
    template<typename Members, std::size_t... Seq>
    std::size_t makeTraitsHashValue(std::size_t& start, Members const& member, std::index_sequence<Seq...> const&)
    {
        std::make_tuple(thash(start, std::get<Seq>(member))...);
        return start;
    }
    template<typename... Members>
    std::size_t makeTraitsHash(std::size_t& start, std::tuple<std::pair<char const*, Members>...>const& members)
    {
        makeTraitsHashValue(start, members, std::make_index_sequence<sizeof...(Members)>());
        return start;
    }
    template<typename Action>
    std::size_t makeTraitsHash(std::size_t& start, Action const& action)
    {
        return action.getHash(start);
    }
    std::size_t operator()(std::size_t& start)    {return makeTraitsHash(start, Traits<T>::getMembers());}
};

template<> struct TraitsHash<short>                 {std::size_t operator()(std::size_t& start){return thash(start, "S");}};
template<> struct TraitsHash<int>                   {std::size_t operator()(std::size_t& start){return thash(start, "I");}};
template<> struct TraitsHash<long>                  {std::size_t operator()(std::size_t& start){return thash(start, "L");}};
template<> struct TraitsHash<long long>             {std::size_t operator()(std::size_t& start){return thash(start, "LL");}};

template<> struct TraitsHash<unsigned short>        {std::size_t operator()(std::size_t& start){return thash(start, "US");}};
template<> struct TraitsHash<unsigned int>          {std::size_t operator()(std::size_t& start){return thash(start, "UI");}};
template<> struct TraitsHash<unsigned long>         {std::size_t operator()(std::size_t& start){return thash(start, "UL");}};
template<> struct TraitsHash<unsigned long long>    {std::size_t operator()(std::size_t& start){return thash(start, "ULL");}};

template<> struct TraitsHash<float>                 {std::size_t operator()(std::size_t& start){return thash(start, "F");}};
template<> struct TraitsHash<double>                {std::size_t operator()(std::size_t& start){return thash(start, "D");}};
template<> struct TraitsHash<long double>           {std::size_t operator()(std::size_t& start){return thash(start, "LD");}};

template<> struct TraitsHash<bool>                  {std::size_t operator()(std::size_t& start){return thash(start, "B");}};
template<> struct TraitsHash<std::string>           {std::size_t operator()(std::size_t& start){return thash(start, "String");}};

    }
}

#endif

