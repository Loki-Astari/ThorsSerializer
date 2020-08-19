#ifndef THORS_ANVIL_SERIALIZATION_CUSTOM_SERIALIZATION_TPP
#define THORS_ANVIL_SERIALIZATION_CUSTOM_SERIALIZATION_TPP

//#include "SerializeConfig.h"
//#include "Serialize.h"
//#include "Traits.h"
#include "JsonThor.h"
#include "YamlThor.h"
#include "BsonThor.h"
//#include "SerUtil.h"
#include "ThorsIOUtil/Utility.h"


namespace ThorsAnvil
{
    namespace Serialize
    {


template<typename T>
void DefaultCustomSerializer<T>::writeJson(JsonPrinter& /*printer*/, T const& /*object*/)
{
    throw CriticalException(
            ThorsAnvil::Utility::buildErrorMessage("ThorsAnvil::Serialize::DefaultCustomSerializer", "writeJson",
                                                   "Using an unimplemented translation:\n",
                                                   "This means you are a streaming a type you have marked with the macro: ThorsAnvil_MakeTraitCustomSerialize.\n",
                                                   "But have not implemented the writeJson() method on the SerializationClass")
                            );
}

template<typename T>
void DefaultCustomSerializer<T>::readJson(JsonParser& /*parser*/, T& /*object*/)
{
    throw CriticalException(
            ThorsAnvil::Utility::buildErrorMessage("ThorsAnvil::Serialize::DefaultCustomSerializer", "readJson",
                                                   "Using an unimplemented translation:\n",
                                                   "This means you are a streaming a type you have marked with the macro: ThorsAnvil_MakeTraitCustomSerialize.\n",
                                                   "But have not implemented the readJson() method on the SerializationClass")
                            );
}

template<typename T>
void DefaultCustomSerializer<T>::writeYaml(YamlPrinter& /*printer*/, T const& /*object*/)
{
    throw CriticalException(
            ThorsAnvil::Utility::buildErrorMessage("ThorsAnvil::Serialize::DefaultCustomSerializer", "writeYaml",
                                                   "Using an unimplemented translation:\n",
                                                   "This means you are a streaming a type you have marked with the macro: ThorsAnvil_MakeTraitCustomSerialize.\n",
                                                   "But have not implemented the writeYaml() method on the SerializationClass")
                            );
}

template<typename T>
void DefaultCustomSerializer<T>::readYaml(YamlParser& /*parser*/, T& /*object*/)
{
    throw CriticalException(
            ThorsAnvil::Utility::buildErrorMessage("ThorsAnvil::Serialize::DefaultCustomSerializer", "readYaml",
                                                   "Using an unimplemented translation:\n",
                                                   "This means you are a streaming a type you have marked with the macro: ThorsAnvil_MakeTraitCustomSerialize.\n",
                                                   "But have not implemented the readYaml() method on the SerializationClass")
                            );
}

template<typename T>
std::size_t DefaultCustomSerializer<T>::getPrintSizeBson(BsonPrinter& /*printer*/, T const& /*object*/)
{
    throw CriticalException(
            ThorsAnvil::Utility::buildErrorMessage("ThorsAnvil::Serialize::DefaultCustomSerializer", "getPrintSizeBson",
                                                   "Using an unimplemented translation:\n",
                                                   "This means you are a streaming a type you have marked with the macro: ThorsAnvil_MakeTraitCustomSerialize.\n",
                                                   "But have not implemented the getPrintSizeBson() method on the SerializationClass")
                            );
}

template<typename T>
void DefaultCustomSerializer<T>::writeBson(BsonPrinter& /*printer*/, T const& /*object*/)
{
    throw CriticalException(
            ThorsAnvil::Utility::buildErrorMessage("ThorsAnvil::Serialize::DefaultCustomSerializer", "writeBson",
                                                   "Using an unimplemented translation:\n",
                                                   "This means you are a streaming a type you have marked with the macro: ThorsAnvil_MakeTraitCustomSerialize.\n",
                                                   "But have not implemented the writeBson() method on the SerializationClass")
                            );
}

template<typename T>
void DefaultCustomSerializer<T>::readBson(BsonParser& /*parser*/, char /*byteMarker*/, T& /*object*/)
{
    throw CriticalException(
            ThorsAnvil::Utility::buildErrorMessage("ThorsAnvil::Serialize::DefaultCustomSerializer", "readBson",
                                                   "Using an unimplemented translation:\n",
                                                   "This means you are a streaming a type you have marked with the macro: ThorsAnvil_MakeTraitCustomSerialize.\n",
                                                   "But have not implemented the readBson() method on the SerializationClass")
                            );
}

    }
}

#endif
