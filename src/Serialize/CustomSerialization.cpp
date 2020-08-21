#include "SerializeConfig.h"
#include "CustomSerialization.h"


#ifdef COVERAGE_TEST
#ifdef COVERAGE_Serialize

#include "CustomSerialization.tpp"
#include "test/BankAccountTest.h"
#include "test/BsonUtilitySerializationTest.h"

template void ThorsAnvil::Serialize::DefaultCustomSerializer<OnLineBank::ID>::readJson(ThorsAnvil::Serialize::JsonParser&, OnLineBank::ID&) const;
template void ThorsAnvil::Serialize::DefaultCustomSerializer<OnLineBank::ID>::writeJson(ThorsAnvil::Serialize::JsonPrinter&, OnLineBank::ID const&) const;

template void ThorsAnvil::Serialize::DefaultCustomSerializer<OnLineBank::ID>::readYaml(ThorsAnvil::Serialize::YamlParser&, OnLineBank::ID&) const;
template void ThorsAnvil::Serialize::DefaultCustomSerializer<OnLineBank::ID>::writeYaml(ThorsAnvil::Serialize::YamlPrinter&, OnLineBank::ID const&) const;

template std::size_t ThorsAnvil::Serialize::DefaultCustomSerializer<OnLineBank::ID>::getPrintSizeBson(ThorsAnvil::Serialize::BsonPrinter&, OnLineBank::ID const&) const;
template void ThorsAnvil::Serialize::DefaultCustomSerializer<OnLineBank::ID>::readBson(ThorsAnvil::Serialize::BsonParser&, char, OnLineBank::ID&) const;
template void ThorsAnvil::Serialize::DefaultCustomSerializer<OnLineBank::ID>::writeBson(ThorsAnvil::Serialize::BsonPrinter&, OnLineBank::ID const&) const;


template void ThorsAnvil::Serialize::Serializer::print<MongoObjectID>(MongoObjectID const&);
template void ThorsAnvil::Serialize::Serializer::print<MongoUTCDateTime>(MongoUTCDateTime const&);
template void ThorsAnvil::Serialize::Serializer::print<MongoBsonTimeStamp>(MongoBsonTimeStamp const&);
template void ThorsAnvil::Serialize::DeSerializer::parse<MongoObjectID>(MongoObjectID&);
template void ThorsAnvil::Serialize::DeSerializer::parse<MongoUTCDateTime>(MongoUTCDateTime&);
template void ThorsAnvil::Serialize::DeSerializer::parse<MongoBsonTimeStamp>(MongoBsonTimeStamp&);


template void ThorsAnvil::Serialize::Serializer::print<MongoBsonBinary>(MongoBsonBinary const&);
template void ThorsAnvil::Serialize::Serializer::print<MongoBsonJsavScript>(MongoBsonJsavScript const&);
template void ThorsAnvil::Serialize::Serializer::print<MongoBsonRegExp>(MongoBsonRegExp const&);
template void ThorsAnvil::Serialize::DeSerializer::parse<MongoBsonBinary>(MongoBsonBinary&);
template void ThorsAnvil::Serialize::DeSerializer::parse<MongoBsonJsavScript>(MongoBsonJsavScript&);
template void ThorsAnvil::Serialize::DeSerializer::parse<MongoBsonRegExp>(MongoBsonRegExp&);

#endif
#endif
