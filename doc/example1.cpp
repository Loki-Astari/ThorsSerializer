#include "ThorSerialize/Traits.h"
#include "ThorSerialize/JsonThor.h"

namespace X
{
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
}

// Declare the traits.
// Specifying what members need to be serialized.
ThorsAnvil_MakeTrait(X::Shirt, red, green, blue);
ThorsAnvil_MakeTrait(X::TeamMember, name, score, damage, team);

int main()
{
        using ThorsAnvil::Serialize::jsonImporter;
        using ThorsAnvil::Serialize::jsonExporter;

        X::TeamMember          mark("mark", 10, 5, X::Shirt{255,0,0});
        // Use the export function to serialize
        std::cout << jsonExporter(mark) << "\n";

        X::TeamMember          john("Empty", 0, 0, X::Shirt{0,0,0});
        std::stringstream   input(R"({"name": "John","score": 13,"team":{"red": 0,"green": 0,"blue": 255, "black":25}})");
        input >> jsonImporter(john);
        std::cout << jsonExporter(john) << "\n";
}

