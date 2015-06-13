[![endorse](http://api.coderwall.com/lokiastari/endorsecount.png)](http://coderwall.com/lokiastari)
[![Build Status](https://travis-ci.org/Loki-Astari/ThorsSerializer.svg?branch=master)](https://travis-ci.org/Loki-Astari/ThorsSerializer)


Yet another JSON/YAML/Binary serialization library for C++

###Objective:

    The objective is to make serialization/de-serialization of C++ object to/from
    JSON/YAML/Binary trivial.

    This means:
        1) does not build a JSON/YAML object. Reads data directly into C++ object.
        2) In normal usage there should be NO need to write any code.
        3) User should not need to understand JSON/YAML or validate its input.
        4) Should work seamlessly with streams.
        5) Standard containers should automatically work

    I am not concerned about speed.
    Though my trivial test work just fine in terms of speed.
    
    The design was done with the primary goal of communicating with WEB-Servers
    that speak JSON. The main envisioned usage was for mobile devices were many
    small JSON objects are transfered in both directions.

###Example Usage with ThorsStream

````c++
    #include "ThorSerialize/Traits.h"
    #include "ThorSerialize/JsonThor.h"

    struct Color
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
        Color           team;
        public:
            TeamMember(std::string const& name, int score, int damage, Color const& team)
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
    ThorsAnvil_MakeTrait(Color, red, green, blue);
    ThorsAnvil_MakeTrait(TeamMember, name, score, damage, team);

    int main()
    {
        using ThorsAnvil::Serialize::jsonExport;

        TeamMember          mark("mark", 10, 5, Color{255,0,0});
        // Use the export function to serialize
        std::cout << jsonExport(mark) << "\n";
    }
````

###Build and run
````json
    > g++ -std=c++14 main.cpp -lThorSerialize14
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
````
