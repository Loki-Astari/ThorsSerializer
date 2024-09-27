#include "Traits.h"
#include <string>
#include <vector>
#include <map>

namespace CountryTest
{
    struct Properties
    {
        std::string     name;
    };

    using   Cord    = std::array<double, 2>; // vector double
    using   CordVec = std::vector<Cord>;
    using   CordMat = std::vector<CordVec>;

    struct Geometry
    {
        std::string     type;
        CordMat         coordinates;
    };

    struct Feature
    {
        std::string     type;
        Properties      properties;
        Geometry        geometry;
    };

    using Features  = std::vector<Feature>;

    struct Country
    {
        std::string     type;
        Features        features;
    };
}

ThorsAnvil_MakeTrait(CountryTest::Properties, name);
ThorsAnvil_MakeTrait(CountryTest::Geometry, type, coordinates);
ThorsAnvil_MakeTrait(CountryTest::Feature, type, properties, geometry);
ThorsAnvil_MakeTrait(CountryTest::Country, type, features);

