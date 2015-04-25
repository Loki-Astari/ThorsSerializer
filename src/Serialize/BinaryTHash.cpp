
#include "BinaryTHash.h"

#ifdef COVERAGE_TEST
#include "BinaryTHash.tpp"
#include "test/THashTest.h"
#include "test/BinaryParserTest.h"


template std::size_t ThorsAnvil::Serialize::thash<D1>(std::size_t);
template std::size_t ThorsAnvil::Serialize::thash<T1>(std::size_t);
template std::size_t ThorsAnvil::Serialize::thash<T2>(std::size_t);

template std::size_t ThorsAnvil::Serialize::thash<short>(std::size_t);
template std::size_t ThorsAnvil::Serialize::thash<int>(std::size_t);
template std::size_t ThorsAnvil::Serialize::thash<long>(std::size_t);
template std::size_t ThorsAnvil::Serialize::thash<long long>(std::size_t);

template std::size_t ThorsAnvil::Serialize::thash<unsigned short>(std::size_t);
template std::size_t ThorsAnvil::Serialize::thash<unsigned int>(std::size_t);
template std::size_t ThorsAnvil::Serialize::thash<unsigned long>(std::size_t);
template std::size_t ThorsAnvil::Serialize::thash<unsigned long long>(std::size_t);

template std::size_t ThorsAnvil::Serialize::thash<double>(std::size_t);
template std::size_t ThorsAnvil::Serialize::thash<long double>(std::size_t);
template std::size_t ThorsAnvil::Serialize::thash<float>(std::size_t);

template std::size_t ThorsAnvil::Serialize::thash<bool>(std::size_t);
template std::size_t ThorsAnvil::Serialize::thash<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > >(std::size_t);

template std::size_t ThorsAnvil::Serialize::thash<Base>(std::size_t);
template std::size_t ThorsAnvil::Serialize::thash<Derived>(std::size_t);

template std::size_t ThorsAnvil::Serialize::thash<std::vector<int>>(std::size_t);

template struct ThorsAnvil::Serialize::TraitsHash<short>;
template struct ThorsAnvil::Serialize::TraitsHash<int>;
template struct ThorsAnvil::Serialize::TraitsHash<long>;
template struct ThorsAnvil::Serialize::TraitsHash<long long>;

template struct ThorsAnvil::Serialize::TraitsHash<unsigned short>;
template struct ThorsAnvil::Serialize::TraitsHash<unsigned int>;
template struct ThorsAnvil::Serialize::TraitsHash<unsigned long>;
template struct ThorsAnvil::Serialize::TraitsHash<unsigned long long>;

template struct ThorsAnvil::Serialize::TraitsHash<float>;
template struct ThorsAnvil::Serialize::TraitsHash<double>;
template struct ThorsAnvil::Serialize::TraitsHash<long double>;

template struct ThorsAnvil::Serialize::TraitsHash<bool>;
template struct ThorsAnvil::Serialize::TraitsHash<std::string>;

template unsigned long ThorsAnvil::Serialize::thash<MapWithMap>(unsigned long);
template unsigned long ThorsAnvil::Serialize::thash<MapOneValue>(unsigned long);
template unsigned long ThorsAnvil::Serialize::thash<MapTwoValue>(unsigned long);
template unsigned long ThorsAnvil::Serialize::thash<MapEmptyTest>(unsigned long);
template unsigned long ThorsAnvil::Serialize::thash<MapWithArray>(unsigned long);
template unsigned long ThorsAnvil::Serialize::thash<MapThreeValue>(unsigned long);
template unsigned long ThorsAnvil::Serialize::thash<MapWithTwoMap>(unsigned long);
template unsigned long ThorsAnvil::Serialize::thash<MapWithTwoArray>(unsigned long);
template unsigned long ThorsAnvil::Serialize::thash<std::vector<MapEmptyTest>>(unsigned long);
template unsigned long ThorsAnvil::Serialize::thash<std::vector<std::string>>(unsigned long);
template unsigned long ThorsAnvil::Serialize::thash<std::vector<std::vector<int>>>(unsigned long);
template unsigned long ThorsAnvil::Serialize::thash<std::vector<bool>>(unsigned long);
template unsigned long ThorsAnvil::Serialize::thash<std::vector<double>>(unsigned long);

#endif


