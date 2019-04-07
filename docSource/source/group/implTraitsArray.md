---
layout: plain
generate: false
---
````C++
template<>
class Traits<ArrayType>
{
    public:
        static constexpr TraitType type = TraitType::Array;

        struct MemberExtractor
        {
            void operator()(PrinterInterface& printer, ArrayType const& object) const;
            void operator()(ParserInterface& parser, std::size_t index, ArrayType& object) const;
        };
        static ExtractorType const& getMembers()
};
````
If the `Traits<>::type` is `TraitType::Array` then the `Traits<>` specialization is expected to have a static `getMembers()` method that returns an `MemberExtractor` object (see below for details).

When serializing an object where the `Traits<>::type` is `TraitType::Array` the library will call `openArray()` on the `printerInterface` (generates a '[' in JSON) and conversely will call `closeArray()` (generates a ']' in JSON) after all the members have been serialized. Conversily when de-serializing into an object with these `Traits<>::type` the parser will expect an arrayOpen/arrayClose marker (in JSON '[' amd ']' respecively).

The method using `PrinterInterface` is called once and is expected to serialize the object using this interface. The method using the `ParserInterface` is called for each new value that is available on the stream and is expected to de-serialize the value directly into the destination object. Note: each time it is called the index is passed.

