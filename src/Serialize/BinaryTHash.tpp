#ifndef THORS_ANVIL_SERIALIZE_THASH_TPP
#define THORS_ANVIL_SERIALIZE_THASH_TPP

#include "Traits.h"
#include <string>
#include <array>
#include <list>
#include <vector>
#include <deque>
#include <memory>
#include <set>
#include <map>


namespace ThorsAnvil
{
    namespace Serialize
    {

inline std::size_t thash(std::size_t start, std::string const& input)
{
    static constexpr std::size_t    mult = 37;
    for (auto loop: input)
    {
        start = start * mult + loop;
    }
    return start;
}

template<typename T>
struct TraitsHash;


template<typename T, typename M>
inline std::size_t thash(std::size_t start, std::pair<char const*, M T::*> const& member)
{
    TraitsHash<M>   typeHash;
    start   = typeHash(start);
    return thash(start, member.first);
}

template<typename T>
inline std::size_t thash(std::size_t result)
{
    TraitsHash<T>   hasher;
    return hasher(result);
}

template<typename T>
struct TraitsHash
{
    template<typename Members, std::size_t... Seq>
    std::size_t makeTraitsHashValue(std::size_t start, Members const& member, std::index_sequence<Seq...> const&)
    {
        auto d = {1, (start=thash(start, std::get<Seq>(member)), 1)...};
        d.size();
        return start;
    }
    template<typename... Members>
    std::size_t makeTraitsHash(std::size_t start, std::tuple<std::pair<char const*, Members>...>const& members)
    {
        return makeTraitsHashValue(start, members, std::make_index_sequence<sizeof...(Members)>());
    }
    std::size_t makeTraitsHash(std::size_t start, std::tuple<void*> const&)
    {
        return thash(start, "Empty");
    }
    template<typename Action>
    std::size_t makeTraitsHash(std::size_t start, Action const& action)
    {
        return action.getHash(start);
    }
    std::size_t operator()(std::size_t start)    {return makeTraitsHash(start, Traits<T>::getMembers());}
};

template<> struct TraitsHash<short>                 {std::size_t operator()(std::size_t start){return thash(start, "S");}};
template<> struct TraitsHash<int>                   {std::size_t operator()(std::size_t start){return thash(start, "I");}};
template<> struct TraitsHash<long>                  {std::size_t operator()(std::size_t start){return thash(start, "L");}};
template<> struct TraitsHash<long long>             {std::size_t operator()(std::size_t start){return thash(start, "LL");}};

template<> struct TraitsHash<unsigned short>        {std::size_t operator()(std::size_t start){return thash(start, "US");}};
template<> struct TraitsHash<unsigned int>          {std::size_t operator()(std::size_t start){return thash(start, "UI");}};
template<> struct TraitsHash<unsigned long>         {std::size_t operator()(std::size_t start){return thash(start, "UL");}};
template<> struct TraitsHash<unsigned long long>    {std::size_t operator()(std::size_t start){return thash(start, "ULL");}};

template<> struct TraitsHash<float>                 {std::size_t operator()(std::size_t start){return thash(start, "F");}};
template<> struct TraitsHash<double>                {std::size_t operator()(std::size_t start){return thash(start, "D");}};
template<> struct TraitsHash<long double>           {std::size_t operator()(std::size_t start){return thash(start, "LD");}};

template<> struct TraitsHash<bool>                  {std::size_t operator()(std::size_t start){return thash(start, "B");}};
template<> struct TraitsHash<std::string>           {std::size_t operator()(std::size_t start){return thash(start, "String");}};

template<typename T, std::size_t S>
struct TraitsHash<std::array<T, S>>      {std::size_t operator()(std::size_t start){return thash(thash<T>(start + S), "std::array");}};
template<typename T>
struct TraitsHash<std::list<T>>          {std::size_t operator()(std::size_t start){return thash(thash<T>(start), "std::list");}};
template<typename T>
struct TraitsHash<std::vector<T>>        {std::size_t operator()(std::size_t start){return thash(thash<T>(start), "std::vector");}};
template<typename T>
struct TraitsHash<std::deque<T>>         {std::size_t operator()(std::size_t start){return thash(thash<T>(start), "std::dequeu");}};
template<typename K, typename V>
struct TraitsHash<std::pair<K, V>>       {std::size_t operator()(std::size_t start){return thash(thash<K>(thash<V>(start)), "std::pair");}};
template<typename T>
struct TraitsHash<std::multiset<T>>      {std::size_t operator()(std::size_t start){return thash(thash<T>(start), "std::multiset");}};
template<typename K, typename V>
struct TraitsHash<std::map<K, V>>        {std::size_t operator()(std::size_t start){return thash(thash<K>(thash<V>(start)), "std::map");}};
template<typename K, typename V>
struct TraitsHash<std::multimap<K, V>>   {std::size_t operator()(std::size_t start){return thash(thash<K>(thash<V>(start)), "std::multimap");}};
    }
}

#endif
