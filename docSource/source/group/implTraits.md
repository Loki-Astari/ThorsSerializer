---
layout: plain
generate: false
children:
    - name:     Traits Value
      value:    implTraitsValue.md
    - name:     Traits Enum
      value:    implTraitsEnum.md
    - name:     Traits Serialize
      value:    implTraitsSerialize.md
    - name:     Traits Pointer
      value:    implTraitsPointer.md
    - name:     Traits Map
      value:    implTraitsMap.md
    - name:     Traits Array
      value:    implTraitsArray.md
---
````C++
namespace ThorsAnvil
{
    namespace Serialize
    {

template<typename T>
class Traits
{
    public:
        static constexpr TraitType type = TraitType::Invalid;
};

    }
}
````
The serialization processes is built around around a traits class `Traits<T>` that is specialized for each type. This is similar in technique to the `std::iterator_traits<>` used by the standard library.

The generic (and thus default) `Traits<T>` has a single member `type` that has the value `TraitType::Invalid`.

The `type` member of the `Traits<>` specialization indicates how the member will be serialized/de-serialized and defines what other members of the `Traits<>` class are needed for that speialization.

The following values are allowed: `{Invalid, Parent, Value, Map, Array, Enum, Pointer, Serialize}`
