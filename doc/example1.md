[![Build Status](https://travis-ci.org/Loki-Astari/ThorsSerializer.svg?branch=master)](https://travis-ci.org/Loki-Astari/ThorsSerializer)

![ThorStream](../img/stream.jpg)

## Example-1 [See doc/example1.cpp](example1.cpp)
````c++
    #include <iostream>
    #include <sstream>
    #include "ThorSerialize/Traits.h"
    #include "ThorSerialize/JsonThor.h"

    struct Shirt
    {
        int     red;
        int     green;
        int     blue;
    };    
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
            // Define the trait as a friend to get accesses to private
            // Members.
            friend class ThorsAnvil::Serialize::Traits<TeamMember>;
    };

    // Declare the traits.
    // Specifying what members need to be serialized.
    ThorsAnvil_MakeTrait(Shirt, red, green, blue);
    ThorsAnvil_MakeTrait(TeamMember, name, score, damage, team);

    int main()
    {
        using ThorsAnvil::Serialize::jsonExporter;

        TeamMember          mark("mark", 10, 5, Shirt{255,0,0});
        // Use the export function to serialize
        std::cout << jsonExporter(mark) << "\n";

        TeamMember          john("Empty", 0, 0, Shirt{0,0,0});
        std::stringstream   input(R"({"name": "John","score": 13,"team":{"red": 0,"green": 0,"blue": 255, "black":25}})");
        input >> jsonImporter(john);
        std::cout << jsonExporter(john) << "\n";
    }
````

### Build and run
````bash
    > g++ -std=c++17 expample1.cpp -lThorSerialize17
    > ./a.out
        { 
            "name": "mark", 
            "score": 10, 
            "damage": 5, 
            "team": 
            { 
                "red": 255, 
                "green": 0, 
                "blue": 0
            }
        }
        {
            "name": "John",
            "score": 13,
            "damage": 0,
            "team":
            {
                "red": 0,
                "green": 0,
                "blue": 255
            }
        }
````
