
#include "BinaryTHash.h"

#ifdef COVERAGE_TEST
/*
 * This code is only compiled into the unit tests for code coverage purposes
 * It is not part of the live code.
 */
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
template std::size_t ThorsAnvil::Serialize::thash<std::string>(std::size_t);

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

template std::size_t ThorsAnvil::Serialize::thash<MapWithMap>(std::size_t);
template std::size_t ThorsAnvil::Serialize::thash<MapOneValue>(std::size_t);
template std::size_t ThorsAnvil::Serialize::thash<MapTwoValue>(std::size_t);
template std::size_t ThorsAnvil::Serialize::thash<MapEmptyTest>(std::size_t);
template std::size_t ThorsAnvil::Serialize::thash<MapWithArray>(std::size_t);
template std::size_t ThorsAnvil::Serialize::thash<MapThreeValue>(std::size_t);
template std::size_t ThorsAnvil::Serialize::thash<MapWithTwoMap>(std::size_t);
template std::size_t ThorsAnvil::Serialize::thash<MapWithTwoArray>(std::size_t);
template std::size_t ThorsAnvil::Serialize::thash<std::vector<MapEmptyTest>>(std::size_t);
template std::size_t ThorsAnvil::Serialize::thash<std::vector<std::string>>(std::size_t);
template std::size_t ThorsAnvil::Serialize::thash<std::vector<std::vector<int>>>(std::size_t);
template std::size_t ThorsAnvil::Serialize::thash<std::vector<bool>>(std::size_t);
template std::size_t ThorsAnvil::Serialize::thash<std::vector<double>>(std::size_t);

#endif


