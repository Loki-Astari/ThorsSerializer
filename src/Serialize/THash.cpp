
#include "THash.h"

#ifdef COVERAGE_TEST
#include "THash.tpp"
#include "test/THashTest.h"


template std::size_t ThorsAnvil::Serialize::thash<D1>();
template std::size_t ThorsAnvil::Serialize::thash<T1>();
template std::size_t ThorsAnvil::Serialize::thash<T2>();

template std::size_t ThorsAnvil::Serialize::thash<short>();
template std::size_t ThorsAnvil::Serialize::thash<int>();
template std::size_t ThorsAnvil::Serialize::thash<long>();
template std::size_t ThorsAnvil::Serialize::thash<long long>();

template std::size_t ThorsAnvil::Serialize::thash<unsigned short>();
template std::size_t ThorsAnvil::Serialize::thash<unsigned int>();
template std::size_t ThorsAnvil::Serialize::thash<unsigned long>();
template std::size_t ThorsAnvil::Serialize::thash<unsigned long long>();

template std::size_t ThorsAnvil::Serialize::thash<double>();
template std::size_t ThorsAnvil::Serialize::thash<long double>();
template std::size_t ThorsAnvil::Serialize::thash<float>();

template std::size_t ThorsAnvil::Serialize::thash<bool>();
template std::size_t ThorsAnvil::Serialize::thash<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > >();

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

#endif


