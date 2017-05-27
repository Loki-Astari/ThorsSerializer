[![Build Status](https://travis-ci.org/Loki-Astari/ThorsSerializer.svg?branch=master)](https://travis-ci.org/Loki-Astari/ThorsSerializer)

![ThorStream](../img/stream.jpg)


## Marking your class Serializeable/Deserializable
* Include the header file: `ThorSerialize/Traits.h`
* Use one of these macros to declare your type as serializable
 * `ThorsAnvil_MakeTrait(<Type>, <members>...)`
 * `ThorsAnvil_ExpandTrait(<Parent-Type>, <Type>, <members>...)`
 * `ThorsAnvil_Template_MakeTrait(<TemplateParamCount>, <Type>, <members>...)`
 * `ThorsAnvil_Template_ExpandTrait(<TemplateParamCount>, <Parent-Type>, <Type>, <members>...)`
 * `ThorsAnvil_MakeEnum(<EnumType>, <EnumMembers>...)`

````bash
    Type:               The name of a class (includeing namespace) of the type
                        you want to be able to serialize at some point.
    Parent-Type:        The name of a class that has previously been declared
                        using `ThorsAnvil_MakeTrait` or `ThorsAnvil_ExpandTrait`
                        and the parent of `Type`
    TemplateParamCount: If `Type` is a template type the number of parameters it needs
                        so that it is fully generalized.
    members:            A list of member (names) of the class `Type` that need
                        to be serialized.
````
The two macros above build a template specialization of the class `ThorsAnvil::Serialize::Traits<Type>` specific to your class. As a consequence these macros should not be placed inside any namespace blocks.
````c++
    #include "ThorSerialize/Traits.h"

    namespace MyNameSpace
    {
        class MyClass
        {
            public:
                int x;
        };
        // This will fail as it is being used inside the `MyNameSpace` namespace
        ThorsAnvil_MakeTrait(MyClass, x);
    }

    // The correct location to use the macro is here
    ThorsAnvil_MakeTrait(MyNameSpace::MyClass, x);
````

## Private Members
If any members of the class that need to be serialized are private you must define a friendship to allow the `Traits<X>` class to have access to the private members.
````c++
    #include "ThorSerialize/Traits.h"

    namespace MyNameSpace
    {
        class MyClass
        {
            // Allow the traits class to access private members of your class.
            friend class ThorsAnvil::Serialize::Traits<MyClass>;
            double  y;
            public:
                int x;

        };
    }

    ThorsAnvil_MakeTrait(MyNameSpace::MyClass, x, y);
````

## Standard containers
The appropriate declarations for all the standard containers are provided. You simply need to include "ThorSerialize/SerUtil.h" to include these declarations.
````c++
    #include "ThorSerialize/SerUtil.h"
    #include "ThorSerialize/JsonThor.h"
    #include <vector>
    #include <iostream>

    int main()
    {
        using ThorsAnvil::Serialize::jsonExport;
        using ThorsAnvil::Serialize::PrinterInterface;
        std::vector<int>    data {1,2,3,4,5};
        std::cout << ThorsAnvil::Serialize::jsonExport(data, PrinterInterface::OutputType::Stream);
    }
````

## Serialization
### Json
* Include the header file "ThorSerialize/JsonThor.h".
* There are two functions in the namespace `ThorsAnvil::Serialize`.
 * `jsonExport(<YourObject>, characteristics = Default);`
 * `jsonImport(<YourObject>);`

Both these methods return an object that simply contains a reference to `YourObject` (no actual serialization happens). When this object is serialized to a stream using `operator<<` or `operator>>` respectively then the code will read/write the appropriate members and serialize/deserialzie them to/from the stream. Because the returned object contains a reference to the object that needs to be serialized; the lifespan should be shorted than `YourObject` to avoid a dangling reference. Therefore it is usually best to just use them directly in the stream operation.

````c++
    std::vector<int>        data{1,2,3,4,5,6};

    std::cout << jsonExport(data);
    std::cin  >> jsonImport(data);
````

On export there is a second parameter `characteristics` that allows some simple control on serialization (it basically affects white space to make debugging easier). Values are:
````bash
     Default:     What ever the implementation likes.
                  Currently this means `Config` but I have plans for an
                  application level setting that is checked.
     Stream:      Compressed for over the wire protocol.            ie. No Space.
     Config:      Human readable                                    Potentially config file like.
````

### Yaml
The description above is for Json Serialization/Deserialization. But the exact same description can be used for Yaml. Simply replace Json with Yaml and replace json with yaml.

The export parameter `characteristics` has slightly different meaning for printing yaml. See the [libyaml documentation](http://libyaml.sourcearchive.com/documentation/0.1.1/group__styles_g1efef592e2e3df6f00432c04ef77d98f.html) for the meaning of these flags.
````bash
     Default:     What ever the implementation likes.
                  Currently this means YAML_BLOCK_MAPPING_STYLE but I have plans for an
                  application level setting that is checked.
     Stream:      YAML_FLOW_MAPPING_STYLE
     Config:      YAML_BLOCK_MAPPING_STYLE
````

### Binary
The description above is for Json Serialization/Deserialization. But the exact same description can be used for Binary versions. Simply replace Json with Binary and replace json with binary.

The export parameter `characteristics` has no affect on binary.

## Notes on std::map (Json)
The JSON "Object" is a set of "name"/"value" pairs. But the name part is always a "String". If you use a `std::map<Key, Value>` where the "Key" is a `std::string` then the `std::map<>` will be represented by a JSON "Object". If any other type is used as the "Key" then `std::map<>` will be represented as a Json "Array" where each member of the array is `std::pair<Key,Value>`.
````c++
    // Example:
    int main()
    {
        std::map<std::string, int>      data1{{"M": 1}};
        std::cout << jsonExport(data1) << "\n";             // {"M":1}

        std::map<int,int>               data2{{15,2}};
        std::cout << jsonExport(data2) << "\n";             // [{"first":15, "second":2}]
    }
````

## Strict Vs Weak Parsing.

By defaul the parser is linient.  
If it finds a "Key" that it does not recognize (or know how to decode) then it will ignore the "Value". This is controlled via the second parameter passed to the parser which defaults to "Weak"

````c++
        using TS = ThorsAnvil::Serializer;
        using PT = TS::ParserInterface::ParseType;

        TS::JasonParser         parser(stream, PT::Strict /* or Weak*/);
        TS::DeSerializeMember   deSer(parser);

        T object;
        deSer.parse(object);

        // -----------
        // Or Short hand

        T object;
        stream >> TS::jsonImport(object, PT::Strict);
````
