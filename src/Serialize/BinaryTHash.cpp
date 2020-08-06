#include "SerializeConfig.h"
#include "BinaryTHash.h"

#ifdef COVERAGE_TEST
#ifdef COVERAGE_Serialize
/*
 * This code is only compiled into the unit tests for code coverage purposes
 * It is not part of the live code.
 */
#include "BinaryTHash.tpp"
#include "test/THashTest.h"
#include "test/BinaryParserTest.h"
#include "test/IgnoreUneededData.h"


HEADER_ONLY_INCLUDE template std::size_t ThorsAnvil::Serialize::thash<THashTest::D1>(std::size_t);
HEADER_ONLY_INCLUDE template std::size_t ThorsAnvil::Serialize::thash<THashTest::T1>(std::size_t);
HEADER_ONLY_INCLUDE template std::size_t ThorsAnvil::Serialize::thash<THashTest::T2>(std::size_t);

HEADER_ONLY_INCLUDE template std::size_t ThorsAnvil::Serialize::thash<short>(std::size_t);
HEADER_ONLY_INCLUDE template std::size_t ThorsAnvil::Serialize::thash<int>(std::size_t);
HEADER_ONLY_INCLUDE template std::size_t ThorsAnvil::Serialize::thash<long>(std::size_t);
HEADER_ONLY_INCLUDE template std::size_t ThorsAnvil::Serialize::thash<long long>(std::size_t);

HEADER_ONLY_INCLUDE template std::size_t ThorsAnvil::Serialize::thash<unsigned short>(std::size_t);
HEADER_ONLY_INCLUDE template std::size_t ThorsAnvil::Serialize::thash<unsigned int>(std::size_t);
HEADER_ONLY_INCLUDE template std::size_t ThorsAnvil::Serialize::thash<unsigned long>(std::size_t);
HEADER_ONLY_INCLUDE template std::size_t ThorsAnvil::Serialize::thash<unsigned long long>(std::size_t);

HEADER_ONLY_INCLUDE template std::size_t ThorsAnvil::Serialize::thash<double>(std::size_t);
HEADER_ONLY_INCLUDE template std::size_t ThorsAnvil::Serialize::thash<long double>(std::size_t);
HEADER_ONLY_INCLUDE template std::size_t ThorsAnvil::Serialize::thash<float>(std::size_t);

HEADER_ONLY_INCLUDE template std::size_t ThorsAnvil::Serialize::thash<bool>(std::size_t);
HEADER_ONLY_INCLUDE template std::size_t ThorsAnvil::Serialize::thash<std::string>(std::size_t);

HEADER_ONLY_INCLUDE template std::size_t ThorsAnvil::Serialize::thash<BinaryParserTest::Base>(std::size_t);
HEADER_ONLY_INCLUDE template std::size_t ThorsAnvil::Serialize::thash<BinaryParserTest::Derived>(std::size_t);

HEADER_ONLY_INCLUDE template std::size_t ThorsAnvil::Serialize::thash<std::vector<int>>(std::size_t);

/*
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
*/

HEADER_ONLY_INCLUDE template std::size_t ThorsAnvil::Serialize::thash<BinaryParserTest::MapWithMap>(std::size_t);
HEADER_ONLY_INCLUDE template std::size_t ThorsAnvil::Serialize::thash<BinaryParserTest::MapOneValue>(std::size_t);
HEADER_ONLY_INCLUDE template std::size_t ThorsAnvil::Serialize::thash<BinaryParserTest::MapTwoValue>(std::size_t);
HEADER_ONLY_INCLUDE template std::size_t ThorsAnvil::Serialize::thash<BinaryParserTest::MapEmptyTest>(std::size_t);
HEADER_ONLY_INCLUDE template std::size_t ThorsAnvil::Serialize::thash<BinaryParserTest::MapWithArray>(std::size_t);
HEADER_ONLY_INCLUDE template std::size_t ThorsAnvil::Serialize::thash<BinaryParserTest::MapThreeValue>(std::size_t);
HEADER_ONLY_INCLUDE template std::size_t ThorsAnvil::Serialize::thash<BinaryParserTest::MapWithTwoMap>(std::size_t);
HEADER_ONLY_INCLUDE template std::size_t ThorsAnvil::Serialize::thash<BinaryParserTest::MapWithTwoArray>(std::size_t);
HEADER_ONLY_INCLUDE template std::size_t ThorsAnvil::Serialize::thash<std::vector<BinaryParserTest::MapEmptyTest>>(std::size_t);
HEADER_ONLY_INCLUDE template std::size_t ThorsAnvil::Serialize::thash<std::vector<std::string>>(std::size_t);
HEADER_ONLY_INCLUDE template std::size_t ThorsAnvil::Serialize::thash<std::vector<std::vector<int>>>(std::size_t);
HEADER_ONLY_INCLUDE template std::size_t ThorsAnvil::Serialize::thash<std::vector<bool>>(std::size_t);
HEADER_ONLY_INCLUDE template std::size_t ThorsAnvil::Serialize::thash<std::vector<double>>(std::size_t);
HEADER_ONLY_INCLUDE template std::size_t ThorsAnvil::Serialize::thash<IgnoreUneededData::ThingVersion>(std::size_t);
HEADER_ONLY_INCLUDE template std::size_t ThorsAnvil::Serialize::thash<IgnoreUneededData::Thing>(std::size_t);

#endif
#endif
