---
layout: plain
generate: false
---
````C++
template<>
class Traits<MapType>
{
    public:
        static constexpr TraitType type = TraitType::Map;   // or TraitType::Parent

        static ExtractorType const& getMembers();
};
//  ExtractorType   => std::tuple<Item...>
//                  or MemberExtractor
//
//  Item    =>  std::pair<char const*, M*>              // M*            pointer to a static member of the class.
//          =>  std::pair<char const*, M MapType::*>    // M MapType::*  pointer to a member of the class
//              struct MemberExtractor
//              {
//                  void operator()(PrinterInterface& printer, ArrayType const& object) const;
//                  void operator()(ParserInterface& parser,  std::string const& key, ArrayType& object) const;
//              };
````
If the `Traits<>::type` is `TraitType::Map` or `TraitType::Parent` then the `Traits<>` specialization is expected to have a static `getMembers()` method that returns an `Extractor` object (see below for details).

When serializing an object where the `Traits<>::type` is `TraitType::Map` or `TraitType::Parent` the library will call `openMap()` on the `printerInterface` (generates a '{' in JSON) and conversely will call `closeMap()` (generates a '}' in JSON) after all the members have been serialized. Conversily when de-serializing into an object with these `Traits<>::type` the parser will expect an mapOpen/mapClose marker (in JSON '{' amd '}' respecively).

#### Tuple of pair
````C++
    ThorsAnvil_MakeTrait(DataType, ...);
    ThorsAnvil_ExpandTrait(ParentType, DataType, ...);
````
If the `getMembers()` method returns a `std::tuple` with a set of `std::pair<>`. Then each pair represents a member of the map that needs to be serialized. The `pair<>::first` represents the key and is serialized as string and when de-serializing we search the `std::tuple` to see if we can match the key that was read from the input. The `pair<>::second` is a pointer to the object that represents the value. A recursive call to de-serialize the value is made.

The easy way to generate the `Traits<>` specialization for an Map with  fields is via the macro `ThorsAnvil_MakeTrait()` or `ThorsAnvil_ExpandTrait()`.
#### MemberExtractor

If the `getMembers()` method returns any other type it is expected to have an interface that matchs the `MemberExtractor` definition. The method using `PrinterInterface` is called once and is expected to serialize the object using this interface. The method using the `ParserInterface` is called after each key has been extracted and is expected to de-serialize the value directly into the destination object.
