#include "gtest/gtest.h"
#include "Traits.h"
#include <string>
#include <map>
#include <sstream>
#include "JsonThor.h"

namespace Issue72
{

    struct FilterTestType
    {
        std::string m1;
        std::string m2;

        std::map<std::string_view, bool> filter;
    };
}

ThorsAnvil_MakeFilter(Issue72::FilterTestType, filter);
ThorsAnvil_MakeTrait(Issue72::FilterTestType, m1, m2);


TEST(Issue72Test, JsonConnection)
{
    Issue72::FilterTestType  testData{"data1", "data2", {}};
    std::stringstream stream;

    stream << ThorsAnvil::Serialize::jsonExporter(testData);
}
