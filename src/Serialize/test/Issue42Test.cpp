
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

ThorsAnvil_MakeTrait(BaseVehicle, isPreloaded);
ThorsAnvil_ExpandTrait(BaseVehicle, VehicleHolder, id);
ThorsAnvil_MakeTrait(Fleet, vehicles);

TEST(Issue42Test, PointerUniquePtrMultiple)
{
    Fleet test {};
    string str = R"( {"vehicles":[
         {
            "__type": "VehicleHolder",
            "id":0
         }
      ]})";
    istringstream stream(str);
    stream >> ThorsAnvil::Serialize::jsonImport(test);
}
