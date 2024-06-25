#ifndef THORSANVIl_THORS_SOCKET_MOCK_HEADER_INCLUDE
#define THORSANVIl_THORS_SOCKET_MOCK_HEADER_INCLUDE

#include <functional>

// Please add includes for all mocked libraries here.
// PART-1-Start
// PART-1-End
namespace ThorsAnvil::BuildTools::Mock
{

// Please define all FuncType_<XXX> here
// There should be one for each MOCK_TFUNC you use in the code.
// The make files will provide the declaration but these need to be filled in by
// the developer and committed to source control
// PART-2-Start
// PART-2-End
// This default implementation of overridden functions
// Please provide a lambda for the implementation
// When you add/remove a MOCK_FUNC or MOCK_TFUNC to the source
// This list will be updated.

}

#include "coverage/MockHeaders.h"

namespace ThorsAnvil::BuildTools::Mock
{
class MockAllDefaultFunctions
{
    int version;
// PART-3-Start
// PART-3-End

    public:
        MockAllDefaultFunctions()
            : version(2)
// PART-4-Start
// PART-4-End
        {}
};


}

#endif

