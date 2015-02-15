
#include "Serialize.h"

#ifdef COVERAGE_TEST

#include "test/SerializeTest.h"
#include "Serialize.tpp"
#include "Json.h"

template void ThorsAnvil::Serialize::Serializer::print<SerializeTestExtra>(SerializeTestExtra const&);
template void ThorsAnvil::Serialize::Serializer::print<SerializeTestChild>(SerializeTestChild const&);
template void ThorsAnvil::Serialize::Serializer::print<SerializeTestMembers>(SerializeTestMembers const&);

template void ThorsAnvil::Serialize::DeSerializer::parse<SerializeTestExtra>(SerializeTestExtra&);
template void ThorsAnvil::Serialize::DeSerializer::parse<SerializeTestChild>(SerializeTestChild&);
template void ThorsAnvil::Serialize::DeSerializer::parse<SerializeTestMembers>(SerializeTestMembers&);

void fake_Serialize_Force_Initializeation_For_Coverage_Test()
{
    ThorsAnvil::Serialize::JsonPrinter  printer(std::cout);
    ThorsAnvil::Serialize::Serializer   serializer(printer);

    ThorsAnvil::Serialize::JsonParser   parser(std::cin);
    ThorsAnvil::Serialize::DeSerializer deSerializer(parser);
}

#endif


