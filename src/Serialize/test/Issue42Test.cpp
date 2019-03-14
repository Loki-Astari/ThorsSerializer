
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

struct Vehicle : public BaseVehicle {
    std::unique_ptr<int> id { nullptr };
    ~Vehicle() override = default;
    ThorsAnvil_PolyMorphicSerializer(Vehicle);
};

struct Fleet {
    //! The list of vehicles.
    std::unique_ptr<std::vector<std::unique_ptr<Vehicle>>> vehicles { nullptr };
};

ThorsAnvil_MakeTrait(BaseVehicle, isPreloaded);
ThorsAnvil_ExpandTrait(BaseVehicle, Vehicle, id);
ThorsAnvil_MakeTrait(Fleet, vehicles);

TEST(Issue42Test, PointerUniquePtrMultiple)
{
    Fleet test {};
    string str = R"( {"vehicles":[
         {
            "__type": "Vehicle",
            "id":0
         }
      ]})";
    istringstream stream(str);
    stream >> ThorsAnvil::Serialize::jsonImport(test);
}
