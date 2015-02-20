
#ifndef THORS_ANVIL_SERIALIZE_BINARY_DECIMAL_H
#define THORS_ANVIL_SERIALIZE_BINARY_DECIMAL_H

#include <istream>
#include <ostream>

namespace ThorsAnvil
{
    namespace Serialize
    {

template<typename T>
void writeFloatingPoint(std::ostream& stream, T value);

template<typename T>
T readFloatingPoint(std::istream& stream);

template<> void writeFloatingPoint<int>(std::ostream&, int) = delete;
template<> int  readFloatingPoint<int>(std::istream&) = delete;


    }
}

#endif

