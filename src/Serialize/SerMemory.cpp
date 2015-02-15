

#ifdef COVERAGE_TEST

#include "Serialize.h"
#include "Serialize.tpp"
#include "SerMemory.h"

template void ThorsAnvil::Serialize::Serializer::print<std::__1::pair<int, double> >(std::__1::pair<int, double> const&);
template void ThorsAnvil::Serialize::DeSerializer::parse<std::__1::pair<int, double> >(std::__1::pair<int, double>&);

#endif


