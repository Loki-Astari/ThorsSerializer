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

