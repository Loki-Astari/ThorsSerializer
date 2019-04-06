---
layout: plain
generate: false
---
````C++
#include "ThorSerialize/JsonThor.h"
#include "ThorSerialize/Traits.h"

using ThorsAnvil::Serialize::jsonExport;
using ThorsAnvil::Serialize::jsonImport;

enum Color { red, green, blue };
ThorsAnvil_MakeEnum(Color, red, green, blue);

int main()
{
    Color c = red;
    std::cout << jsonExport(c) << "\n";
}
...
 "red"
````
In C++ enums are serialized as integer types. This can work but you loose meaning in this translation. It also binds you contractually to never changing the order of any enum items in the type.

The ThorsSerializer library provides you a mechanism to stream the type as a string. This maintains its symantic meaning while in the JSON format and when de-serialized is converted back to the correct enum value automatically.

For each enum type that you want to serialize simply use `ThorsAnvil_MakeEnum()` macros to declare the enum and all valid streamable values in the enum range. You simply need to include #include "ThorSerialize/Traits.h".
