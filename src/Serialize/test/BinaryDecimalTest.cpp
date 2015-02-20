#include "gtest/gtest.h"
#include "BinaryDecial.h"

#include <limits>
#include <sstream>
#include <cmath>

namespace TA=ThorsAnvil::Serialize;

TEST(BinaryDecimalTest, BasicConversionTests)
{
    std::stringstream       stream;
    double result;
    
    TA::writeFloatingPoint(stream, std::numeric_limits<double>::quiet_NaN());
    result = TA::readFloatingPoint<double>(stream);
    EXPECT_TRUE(std::isnan(result));

    TA::writeFloatingPoint(stream, 0.0);
    result = TA::readFloatingPoint<double>(stream);
    EXPECT_EQ(0, result);

    TA::writeFloatingPoint(stream, +std::numeric_limits<double>::min());
    result = TA::readFloatingPoint<double>(stream);
    EXPECT_EQ(+std::numeric_limits<double>::min(), result);

    TA::writeFloatingPoint(stream, -std::numeric_limits<double>::min());
    result = TA::readFloatingPoint<double>(stream);
    EXPECT_EQ(-std::numeric_limits<double>::min(), result);

    TA::writeFloatingPoint(stream, +1.0);
    result = TA::readFloatingPoint<double>(stream);
    EXPECT_EQ(+1.0, result);

    TA::writeFloatingPoint(stream, -1.0);
    result = TA::readFloatingPoint<double>(stream);
    EXPECT_EQ(-1.0, result);

    double  value   = +3.14159269;
    TA::writeFloatingPoint(stream, value);
    result = TA::readFloatingPoint<double>(stream);
    EXPECT_EQ(value, result);

    value   = -3.14159269;
    TA::writeFloatingPoint(stream, value);
    result = TA::readFloatingPoint<double>(stream);
    EXPECT_EQ(value, result);

    TA::writeFloatingPoint(stream, +std::numeric_limits<double>::max());
    result = TA::readFloatingPoint<double>(stream);
    EXPECT_EQ(+std::numeric_limits<double>::max(), result);

    TA::writeFloatingPoint(stream, -std::numeric_limits<double>::max());
    result = TA::readFloatingPoint<double>(stream);
    EXPECT_EQ(-std::numeric_limits<double>::max(), result);

    TA::writeFloatingPoint(stream, +std::numeric_limits<double>::infinity());
    result = TA::readFloatingPoint<double>(stream);
    EXPECT_EQ(+std::numeric_limits<double>::infinity(), result);

    TA::writeFloatingPoint(stream, -std::numeric_limits<double>::infinity());
    result = TA::readFloatingPoint<double>(stream);
    EXPECT_EQ(-std::numeric_limits<double>::infinity(), result);
}


