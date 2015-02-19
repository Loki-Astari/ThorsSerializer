
#include "Serialize.h"

#ifdef COVERAGE_TEST

#include "Serialize.tpp"
#include "SerUtil.h"
#include "Json.h"
#include "test/SerializeTest.h"

template void ThorsAnvil::Serialize::Serializer::print<SerializeTestExtra>(SerializeTestExtra const&);
template void ThorsAnvil::Serialize::Serializer::print<SerializeTestChild>(SerializeTestChild const&);
template void ThorsAnvil::Serialize::Serializer::print<SerializeTestMembers>(SerializeTestMembers const&);

template void ThorsAnvil::Serialize::DeSerializer::parse<SerializeTestExtra>(SerializeTestExtra&);
template void ThorsAnvil::Serialize::DeSerializer::parse<SerializeTestChild>(SerializeTestChild&);
template void ThorsAnvil::Serialize::DeSerializer::parse<SerializeTestMembers>(SerializeTestMembers&);


template void ThorsAnvil::Serialize::Serializer::print<std::__1::array<int, 12ul> >(std::__1::array<int, 12ul> const&);
template void ThorsAnvil::Serialize::Serializer::print<std::__1::pair<int, double> >(std::__1::pair<int, double> const&);
template void ThorsAnvil::Serialize::Serializer::print<std::__1::list<int, std::__1::allocator<int> > >(std::__1::list<int, std::__1::allocator<int> > const&);
template void ThorsAnvil::Serialize::Serializer::print<std::__1::deque<int, std::__1::allocator<int> > >(std::__1::deque<int, std::__1::allocator<int> > const&);
template void ThorsAnvil::Serialize::Serializer::print<std::__1::vector<int, std::__1::allocator<int> > >(std::__1::vector<int, std::__1::allocator<int> > const&);
template void ThorsAnvil::Serialize::Serializer::print<std::__1::set<int, std::__1::less<int>, std::__1::allocator<int> > >(std::__1::set<int, std::__1::less<int>, std::__1::allocator<int> > const&);
template void ThorsAnvil::Serialize::Serializer::print<std::__1::multiset<int, std::__1::less<int>, std::__1::allocator<int> > >(std::__1::multiset<int, std::__1::less<int>, std::__1::allocator<int> > const&);
template void ThorsAnvil::Serialize::Serializer::print<std::__1::map<int, double, std::__1::less<int>, std::__1::allocator<std::__1::pair<int const, double> > > >(std::__1::map<int, double, std::__1::less<int>, std::__1::allocator<std::__1::pair<int const, double> > > const&);
template void ThorsAnvil::Serialize::Serializer::print<std::__1::multimap<int, double, std::__1::less<int>, std::__1::allocator<std::__1::pair<int const, double> > > >(std::__1::multimap<int, double, std::__1::less<int>, std::__1::allocator<std::__1::pair<int const, double> > > const&);
template void ThorsAnvil::Serialize::Serializer::print<std::__1::map<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >, double, std::__1::less<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > >, std::__1::allocator<std::__1::pair<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > const, double> > > >(std::__1::map<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >, double, std::__1::less<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > >, std::__1::allocator<std::__1::pair<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > const, double> > > const&);
template void ThorsAnvil::Serialize::Serializer::print<std::__1::multimap<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >, double, std::__1::less<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > >, std::__1::allocator<std::__1::pair<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > const, double> > > >(std::__1::multimap<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >, double, std::__1::less<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > >, std::__1::allocator<std::__1::pair<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > const, double> > > const&);


template void ThorsAnvil::Serialize::DeSerializer::parse<std::__1::array<int, 0ul> >(std::__1::array<int, 0ul>&);
template void ThorsAnvil::Serialize::DeSerializer::parse<std::__1::array<int, 12ul> >(std::__1::array<int, 12ul>&);
template void ThorsAnvil::Serialize::DeSerializer::parse<std::__1::pair<int, double> >(std::__1::pair<int, double>&);
template void ThorsAnvil::Serialize::DeSerializer::parse<std::__1::list<int, std::__1::allocator<int> > >(std::__1::list<int, std::__1::allocator<int> >&);
template void ThorsAnvil::Serialize::DeSerializer::parse<std::__1::deque<int, std::__1::allocator<int> > >(std::__1::deque<int, std::__1::allocator<int> >&);
template void ThorsAnvil::Serialize::DeSerializer::parse<std::__1::vector<int, std::__1::allocator<int> > >(std::__1::vector<int, std::__1::allocator<int> >&);
template void ThorsAnvil::Serialize::DeSerializer::parse<std::__1::set<int, std::__1::less<int>, std::__1::allocator<int> > >(std::__1::set<int, std::__1::less<int>, std::__1::allocator<int> >&);
template void ThorsAnvil::Serialize::DeSerializer::parse<std::__1::multiset<int, std::__1::less<int>, std::__1::allocator<int> > >(std::__1::multiset<int, std::__1::less<int>, std::__1::allocator<int> >&);
template void ThorsAnvil::Serialize::DeSerializer::parse<std::__1::map<int, double, std::__1::less<int>, std::__1::allocator<std::__1::pair<int const, double> > > >(std::__1::map<int, double, std::__1::less<int>, std::__1::allocator<std::__1::pair<int const, double> > >&);
template void ThorsAnvil::Serialize::DeSerializer::parse<std::__1::multimap<int, double, std::__1::less<int>, std::__1::allocator<std::__1::pair<int const, double> > > >(std::__1::multimap<int, double, std::__1::less<int>, std::__1::allocator<std::__1::pair<int const, double> > >&);
template void ThorsAnvil::Serialize::DeSerializer::parse<std::__1::map<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >, bool, std::__1::less<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > >, std::__1::allocator<std::__1::pair<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > const, bool> > > >(std::__1::map<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >, bool, std::__1::less<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > >, std::__1::allocator<std::__1::pair<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > const, bool> > >&);
template void ThorsAnvil::Serialize::DeSerializer::parse<std::__1::multimap<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >, bool, std::__1::less<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > >, std::__1::allocator<std::__1::pair<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > const, bool> > > >(std::__1::multimap<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >, bool, std::__1::less<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > >, std::__1::allocator<std::__1::pair<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > const, bool> > >&);

void fake_Serialize_Force_Initializeation_For_Coverage_Test()
{
    ThorsAnvil::Serialize::JsonPrinter  printer(std::cout);
    ThorsAnvil::Serialize::Serializer   serializer(printer);

    ThorsAnvil::Serialize::JsonParser   parser(std::cin);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);

    parser.pushBackToken(ThorsAnvil::Serialize::ParserInterface::ParserToken::Value);
}

#endif


