#ifndef THORS_ANVIL_SERIALIZER_THORSSERIALIZERUTIL_H
#define THORS_ANVIL_SERIALIZER_THORSSERIALIZERUTIL_H

namespace ThorsAnvil
{
    namespace Serialize
    {

template<typename T>
class Traits;

template <typename, typename = void>
struct HasParent: std::false_type
{};

template <class T>
struct HasParent<T, std::enable_if_t<(sizeof(typename Traits<T>::Parent) >= 0)>>: std::true_type
{};

    }
}

#endif
