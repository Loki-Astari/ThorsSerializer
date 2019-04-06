---
layout: plain
generate: false
---
````C++
template<>
class Traits<FundamentType>
{
    public:
        static constexpr TraitType type = TraitType::Value;
};
````
This is used for all the fundamental types. These types use the `ParserInterface` and `PrinterInterface` to serialize/de-serialize. You should only use this value if your value can be parsed via: `ParserInterface::getValue()` and printed via `PrinterInterface::addValue()`.
