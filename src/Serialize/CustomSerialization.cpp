#include "SerializeConfig.h"
#include "CustomSerialization.h"


#ifdef COVERAGE_TEST
#ifdef COVERAGE_Serialize

#include "CustomSerialization.tpp"
#include "test/BankAccountTest.h"

template void ThorsAnvil::Serialize::DefaultCustomSerializer<OnLineBank::ID>::readJson(ThorsAnvil::Serialize::JsonParser&, OnLineBank::ID&);
template void ThorsAnvil::Serialize::DefaultCustomSerializer<OnLineBank::ID>::writeJson(ThorsAnvil::Serialize::JsonPrinter&, OnLineBank::ID const&);

template void ThorsAnvil::Serialize::DefaultCustomSerializer<OnLineBank::ID>::readYaml(ThorsAnvil::Serialize::YamlParser&, OnLineBank::ID&);
template void ThorsAnvil::Serialize::DefaultCustomSerializer<OnLineBank::ID>::writeYaml(ThorsAnvil::Serialize::YamlPrinter&, OnLineBank::ID const&);

template std::size_t ThorsAnvil::Serialize::DefaultCustomSerializer<OnLineBank::ID>::getPrintSizeBson(ThorsAnvil::Serialize::BsonPrinter&, OnLineBank::ID const&);
template void ThorsAnvil::Serialize::DefaultCustomSerializer<OnLineBank::ID>::readBson(ThorsAnvil::Serialize::BsonParser&, char, OnLineBank::ID&);
template void ThorsAnvil::Serialize::DefaultCustomSerializer<OnLineBank::ID>::writeBson(ThorsAnvil::Serialize::BsonPrinter&, OnLineBank::ID const&);

#endif
#endif
