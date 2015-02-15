

#ifdef COVERAGE_TEST

#include "Serialize.h"
#include "Serialize.tpp"
#include "SerMap.h"

template void ThorsAnvil::Serialize::Serializer::print<std::__1::map<int, double, std::__1::less<int>, std::__1::allocator<std::__1::pair<int const, double> > > >(std::__1::map<int, double, std::__1::less<int>, std::__1::allocator<std::__1::pair<int const, double> > > const&);
template void ThorsAnvil::Serialize::DeSerializer::parse<std::__1::map<int, double, std::__1::less<int>, std::__1::allocator<std::__1::pair<int const, double> > > >(std::__1::map<int, double, std::__1::less<int>, std::__1::allocator<std::__1::pair<int const, double> > >&);

template void ThorsAnvil::Serialize::Serializer::print<std::__1::map<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >, double, std::__1::less<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > >, std::__1::allocator<std::__1::pair<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > const, double> > > >(std::__1::map<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >, double, std::__1::less<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > >, std::__1::allocator<std::__1::pair<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > const, double> > > const&);
template void ThorsAnvil::Serialize::DeSerializer::parse<std::__1::map<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >, bool, std::__1::less<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > >, std::__1::allocator<std::__1::pair<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > const, bool> > > >(std::__1::map<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >, bool, std::__1::less<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > >, std::__1::allocator<std::__1::pair<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> > const, bool> > >&);

#endif


