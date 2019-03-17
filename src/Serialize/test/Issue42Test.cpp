
#include "gtest/gtest.h"
#include "test/SerializeTest.h"
#include "Serialize.h"
#include "Traits.h"
#include "JsonThor.h"
#include "SerUtil.h"
#include <memory>
#include <iostream>



using namespace ThorsAnvil::Serialize;
using namespace std;

namespace Issue42Test
{
struct BaseVehicle {
    std::unique_ptr<bool> isPreloaded { nullptr };
    virtual ~BaseVehicle() = default;
    ThorsAnvil_PolyMorphicSerializer(BaseVehicle);
};

struct VehicleHolder : public BaseVehicle {
    std::unique_ptr<int> id { nullptr };
    ThorsAnvil_PolyMorphicSerializer(VehicleHolder);
};

struct Fleet {
    //! The list of vehicles.
    std::unique_ptr<std::vector<std::unique_ptr<VehicleHolder>>> vehicles { nullptr };
};

}

ThorsAnvil_MakeTrait(Issue42Test::BaseVehicle, isPreloaded);
ThorsAnvil_ExpandTrait(Issue42Test::BaseVehicle, Issue42Test::VehicleHolder, id);
ThorsAnvil_MakeTrait(Issue42Test::Fleet, vehicles);

TEST(Issue42Test, PointerUniquePtrMultiple)
{
    Issue42Test::Fleet test {};
    string str = R"( {"vehicles":[
         {
            "__type": "Issue42Test::VehicleHolder",
            "id":0
         }
      ]})";
    istringstream stream(str);
    stream >> ThorsAnvil::Serialize::jsonImport(test);
}
