[![endorse](http://api.coderwall.com/lokiastari/endorsecount.png)](http://coderwall.com/lokiastari)
[![Build Status](https://travis-ci.org/Loki-Astari/ThorsSerializer.svg?branch=master)](https://travis-ci.org/Loki-Astari/ThorsSerializer)

![ThorStream](https://raw.github.com/Loki-Astari/ThorsSerializer/ReWriteDocumentation/img/stream.jpg)


##Marking your class as Serializeable

* Include the header file: `ThorSerialize/Traits.h`
* Use the macro to declare your type as serializable
 * `ThorsAnvil_MakeTrait(<Type>, <members>...)`
 * `ThorsAnvil_ExpandTrait(<Parent-Type>, <Type>, <members>...)`

````bash
    Type:           The name of a class (includeing namespace) of the type
                    you want to be able to serialize at some point.
    Parent-Type:    The name of a class that has previously been declared
                    using `ThorsAnvil_MakeTrait` and the parent of `Type`
    members:        A list of member (names) of the class `Type` that need to be serialized.
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

##Private Members
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

##Standard containers
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

##Serialization

###Json
* Include the header file "ThorSerialize/JsonThor.h".
* There are two functions in the namespace `ThorsAnvil::Serialize`.
 * `jsonExport(<YourObject>, characteristics = Default);`
 * `jsonImport(<YourObject>);`

Both these methods return an object that simply contains a reference to `YourObject` (no actual serialization happens). When this object is serialized to a stream using `operator<<` or `operator>>` respectively then will read the appropriate members and serialize them to the stream. Because the returned object contains a reference to the object that needs to be serialized there lifespan should be shorted than `YourObject` to avoid a dangling reference. Therefore it is usually best to just use them directly in the stream operation.

````c++
    std::vector<int>        data{1,2,3,4,5,6};

    std::cout << jsonExport(data);
    std::cin  >> jsonImport(data);
````

On export there is a second parameter that allows some simple control on serialization (it basically affects white space to make debugging easier). Values are:

```bash
     Default:     What ever the implementation likes.
                  Currently this means `Config` but I have plans for an application level setting that is checked.
     Stream:      Compressed for over the wire protocol.            ie. No Space.
     Config:      Human readable                                    Potentially config file like
````

###Yaml/Binary

The description above is for Json Serialization/Deserialization. But the exact same description can be used for Yaml or Binary versions. Simply replace Json with Yaml or Binary and replace json with yaml or binary.


