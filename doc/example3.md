![ThorStream](../img/stream.jpg)

## Example-3: [see doc/example3.cpp](example3.cpp)
The library handles polymorphic types via pointers. The only addition the developer needs to do is add the macro `ThorsAnvil_PolyMorphicSerializer()` into the class (as part of the public) 

```C++
    #include "ThorSerialize/Serialize.h"
    #include "ThorSerialize/Serialize.tpp"
    #include "ThorSerialize/Traits.h"
    #include "ThorSerialize/JsonThor.h"
    #include <string>
    #include <sstream>
    #include <iostream>

    struct Vehicle
    {
        Vehicle(){}
        Vehicle(int speed)
            : speed(speed)
        {}
        virtual ~Vehicle() {}
        int     speed;
        ThorsAnvil_PolyMorphicSerializer(Vehicle);
    };
    struct Car: public Vehicle
    {
        Car(){}
        Car(int speed, std::string const& make)
            : Vehicle(speed)
            , make(make)
        {}
        std::string     make;
        ThorsAnvil_PolyMorphicSerializer(Car);
    };
    struct Bike: public Vehicle
    {
        Bike(){}
        Bike(int speed, int stroke)
            : Vehicle(speed)
            , stroke(stroke)
        {}
        int     stroke;
        ThorsAnvil_PolyMorphicSerializer(Bike);
    };
```

As per normal the class's must also be declared as serializable.
```C++
    ThorsAnvil_MakeTrait(Vehicle, speed);
    ThorsAnvil_ExpandTrait(Vehicle, Car, make);
    ThorsAnvil_ExpandTrait(Vehicle, Bike, stroke);
```

The use cases for serialization/de-serialization are the same:
```C++
    int main()
    {
        Vehicle*    init = new Bike(15, 2);

        std::stringstream   stream;
        stream << ThorsAnvil::Serialize::jsonExporter(init);
        std::cout << ThorsAnvil::Serialize::jsonExporter(init) << "\n\n";

        Vehicle*    result = nullptr;
        std::cout << ThorsAnvil::Serialize::jsonExporter(result) << "\n\n";
        stream >> ThorsAnvil::Serialize::jsonImporter(result);

        std::cout << ThorsAnvil::Serialize::jsonExporter(result) << "\n\n";
    }
```

The one difference from normal serialization is that it adds an extra member to the output class. The key `"__type"` is serialized as the first member of an object. When reading (De-Serializing) a stream the key `"__type"` must be the first member of the object (Otherwise you will get an exception). Notice a `nullptr` is serialized as `null` in JSON.

```bash
    > g++ -std=c++20 -o example3 example3.cpp -lThorSerialize -lThorsLogging
    > # Note on mac you may need to add -I/opt/homebrew/include -L/opt/homebrew/lib/ on Mac's with M1 chip.
    > ./example3
    {
        "__type": "Bike",
        "stroke": 2,
        "speed": 15
    }

    null


    {
        "__type": "Bike",
        "stroke": 2,
        "speed": 15
    }
```

To make this work the `Traits` class for pointers generates a default `alloc()` method that simply calls new on the object (and assumes a default constructor). If you need a custom allocation methods you can specify your own custom one.

```C++
    ThorsAnvil_PointerAllocator(Bike, [](){return new Bike(6,7);});
```
