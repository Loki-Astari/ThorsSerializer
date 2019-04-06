---
layout: plain
generate: false
---
````C++
#include "ThorSerialize/JsonThor.h"

using ThorsAnvil::Serialize::jsonExport;
using ThorsAnvil::Serialize::jsonImport;

int main()
{
    int         v1 = 12;        // All the different types of int are supported)
    double      v2 = 13.5;      // float/double/long double all supported
    bool        v3 = true;
    std::string v4 = "A string";

    std::cout << jsonExport(v1) << " "
              << jsonExport(v2) << " "
              << jsonExport(v3) << " "
              << jsonExport(v4) << "\n";
}
...
 12  13.5  true  "A string"
````
The built-in types `integer/float/bool/std::string` are serialalable out of the box. You may notice a couple of notable exceptions `char` and `char*`. The `char` type is not supported as it is very easily confused with an integer and `char*` is not supported because I did not want to encourage C-Strings when `std::string` is available (sorry).

Note: I know this is not very useful by itself. Bare with me it becomes useful when you start composing types.
