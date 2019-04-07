---
layout: plain
generate: false
children:
    - name:  Format
      value: usageSerializingFormat.md
    - name:  Strictness
      value: usageSerializingStrictness.md
    - name:  Exceptions
      value: usageSerializingExceptions.md
---
There are two serialization formats supported out o the box (JSON/YAML) and an experimental binary format (I would love if somebody added the google Protocol Buffers).

````C++
#include "ThorSerialize/JsonThor.h"

using ThorsAnvil::Serialize::jsonExport;
using ThorsAnvil::Serialize::jsonImport;

int main()
{
    std::cout << jsonExport(12) << "\n";

    int value;
    std::cin >> jsonImport(value);
}
````
Each format has two commands `<format>Import(<object>)` and `<format>Export(<object>)`. e.g. `jsonExport(12)`.

These functions return a very lightweight object (it simply contains a reference to the object being serialized) that can be passed to the standard stream operators. Thats at it for a the user of serialization library.

To include all the functionality all you need to do is include `#include "ThorSerialize/<format>Thor.h"` and link against `libThorSerialize17.so`.
