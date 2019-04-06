---
layout: plain
generate: false
---
````C++
// Shirt.h
#include "ThorSerialize/Traits.h"
struct Shirt
{
    int     red;
    int     green;
    int     blue;
};
ThorsAnvil_MakeTrait(Shirt, red, green, blue);
````
````C++
#include "ThorSerialize/JsonThor.h"
#include "Shirt.h"

using ThorsAnvil::Serialize::jsonExport;
using ThorsAnvil::Serialize::jsonImport;

int main()
{
    Shirt          shirt{10, 20, 45};
    std::cout << jsonExport(shirt) << "\n";
}
...
	{
		"red": 10,
		"green": 20,
		"blue": 45
	}
````
In C++ structures are not serializable by default (but often have the appropriate stream operators defined). The advantage of ThorsSerializer library is that it adds a serialization feature to a class without altering the class in any way. This is achieved by building a `Serialization::Traits<>` type for your class. We will go into more detail on how this works in the implementation section.

The easiest way to build the appropriate `Serialization::Traits<>` type is to use the macro `ThorsAnvil_MakeTrait()` naming the type and all members you want to serialize as part of the object. You simply need to include #include "ThorSerialize/Traits.h".

#### Private Members
````C++
// TeamMember.h
#include "Shirt.h"
class TeamMember
{
    std::string     name;
    int             score;
    int             damage;
    Shirt           team;
    public:
    TeamMember(std::string const& name, int score, int damage, Shirt const& team)
        : name(name)
          , score(score)
          , damage(damage)
          , team(team)
    {}
    // Define the trait as a friend to get accesses to private Members.
    friend class ThorsAnvil::Serialize::Traits<TeamMember>;
};
ThorsAnvil_MakeTrait(TeamMember, name, score, damage, team);
````
````C++
#include "ThorSerialize/JsonThor.h"
#include "TeamMember.h"

using ThorsAnvil::Serialize::jsonExport;
using ThorsAnvil::Serialize::jsonImport;

int main()
{
    TeamMember          mark("mark", 10, 5, Shirt{66, 42, 23});
    std::cout << jsonExport(mark) << "\n";
}
...
	{
		"name": "mark",
		"score": 10,
		"damage": 5,
		"team":
		{
			"red": 66,
			"green": 42,
			"blue": 23
		}
	}
````
If you have a class/struct were the members that need to be serialized are private then there is no automatic accesses for the ThorsSerializer library to these members. To give the library accesses your class must declare the `Serialization::Traits<>` type as a friend of the class. This will allow the class to directly accesses these members and both read/write them during the serialization/de-serialization processes.

#### Inheritance
````C++
// ExtendedTeamMember.h
#include "TeamMember.h"
class ExtendedTeamMember: public TeamMember
{
    bool    extension;
    public:
        ExtendedTeamMember(std::string const& name, int score, int damage, Shirt const& team, bool ex)
            : TeamMember(name, score, damage, team)
            , extension(ex)
        {}
    friend class ThorsAnvil::Serialize::Traits<ExtendedTeamMember>;
};
ThorsAnvil_ExpandTrait(TeamMember, ExtendedTeamMember, extension);
````
````C++
#include "ThorSerialize/JsonThor.h"
#include "ExtendedTeamMember.h"

using ThorsAnvil::Serialize::jsonExport;
using ThorsAnvil::Serialize::jsonImport;

int main()
{
    ExtendedTeamMember          rangers("Rangers", 10, 5, Shirt{66, 42, 23}, true);
    std::cout << jsonExport(rangers) << "\n";
}
...
	{
		"name": "Rangers",
		"score": 10,
		"damage": 5,
		"team":
		{
			"red": 66,
			"green": 42,
			"blue": 23
		},
		"extension": true
	}
````
The only difference from a base type is that we use `ThorsAnvil_ExpandTrait()` rather than `ThorsAnvil_MakeTrait()`. The difference between these two is that `ThorsAnvil_ExpandTrait()` takes the parent class as the first parameter followed by the child type as the second parameter.

#### Multiple Inheritance
````C++
#include "ThorSerialize/JsonThor.h"
#include "ThorSerialize/Traits.h"

using ThorsAnvil::Serialize::jsonExport;
using ThorsAnvil::Serialize::jsonImport;

struct Base1
{
    int         data;
};
struct Base2
{
    std::string name;
};
struct Object: public Base1, public Base2
{
    bool        good;
};
ThorsAnvil_MakeTrait(Base1, data);
ThorsAnvil_MakeTrait(Base2, name);

// The macro ThorsAnvil_ExpandTrait() only allows you to declare 1 base type name.
// To get around this limitation you need place both base types into `Serialize::Parents<>` template.
// This can then be used as the parent type in the macro ThorsAnvil_ExpandTrait()␣
using Base1Base2Parent = ThorsAnvil::Serialize::Parents<Base1, Base2>;
ThorsAnvil_ExpandTrait(Base1Base2Parent, Object, good);

int main()
{
    Object  object{12, "Test", true};
    std::cout << jsonExport(object) << "\n";
}
...
	{
		"data": 12,
		"name": "Test",
		"good": true
	}
````
Multiple enheritance is a tiny bit of a hack.  
Multiple parent types must be combined using the template class `ThorsAnvil::Serialize::Parents` and then passed to the `ThorsAnvil_ExpandTrait()` macro as if that was the parent type.

