
#include "Serialize.h"

#ifdef COVERAGE_TEST

#include "test/SerializeTest.h"
#define INLINE
#include "Serialize.tpp"
#undef  INLINE

template void ThorsAnvil::Serialize::Serializer::print<SerializeTestExtra>(SerializeTestExtra const&);
template void ThorsAnvil::Serialize::Serializer::print<SerializeTestChild>(SerializeTestChild const&);
template void ThorsAnvil::Serialize::Serializer::print<SerializeTestMembers>(SerializeTestMembers const&);

template void ThorsAnvil::Serialize::DeSerializer::parse<SerializeTestExtra>(SerializeTestExtra&);
template void ThorsAnvil::Serialize::DeSerializer::parse<SerializeTestChild>(SerializeTestChild&);

#endif


