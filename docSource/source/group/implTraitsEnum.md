---
layout: plain
generate: false
---
````C++
template<>
class Traits<Enum_Type>
{
    public:
        static constexpr TraitType type = TraitType::Enum;

        static char const* const*   getValues();
        static Enum_Type            getValue(std::string const& val, std::string const& msg);
};
````
In this case ThorsSerializer expects the `Traits<T>` class to have two extra static methods: `getValues()` and `getValue()`.

* `getValues()`  
Is used for serializing the value by providing an array of `char const*` that represent the text version of the enum value.
* `getValue()`  
Is used for deserializing a specific string into a specifc enum value.

````C++
    ThorsAnvil_MakeEnum(<EnumType>, <EnumValues>...)
````
The easy way to generate the `Traits<>` specialization for an enum with these fields is via the macro `ThorsAnvil_MakeEnum()`.
