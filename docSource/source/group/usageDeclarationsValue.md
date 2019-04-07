---
layout: plain
generate: false
---
````C++
#include "ThorSerialize/JsonThor.h"
#include "ThorSerialize/Traits.h"

using ThorsAnvil::Serialize::jsonExport;
using ThorsAnvil::Serialize::jsonImport;

struct ID
{
    int id;
    friend std::ostream& operator<<(std::ostream& s, ID const& data) {return s << data.id;}
    friend std::istream& operator>>(std::istream& s, ID& data)       {return s >> data.id;}
};
ThorsAnvil_MakeTraitCustom(ID);

int main()
{
    ID  id{23};
    std::cout << jsonExport(id) << "\n";
}
...
 23
````
In situations where your class already has appropriate input and output operators (that generate JSON like values (Bool,Integer/Float/String) then you can simply declare your type as serializeable using the macro `ThorsAnvil_MakeTraitCustom()`.
