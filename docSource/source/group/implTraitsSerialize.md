---
layout: plain
generate: false
---
````C++
template<>
class Traits<StremableType>
{
    public:
        static constexpr TraitType type = TraitType::Serialize;
};
````
In this case ThorsSerializer expects the object to serialize itself via `operator<<` and `operator>>`. The resulting value should be a simple JSON value (Bool/Integer/Float/String).

````C++
    ThorsAnvil_MakeTraitCustom(<SerializableType>);
````
The easy way to generate the `Traits<>` specialization for a Serialize type is via the macro `ThorsAnvil_MakeTraitCustom()`.
