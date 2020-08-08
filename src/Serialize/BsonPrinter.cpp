#include "SerializeConfig.h"
#include "BsonPrinter.h"
#include <iomanip>
#include <algorithm>

using namespace ThorsAnvil::Serialize;

namespace
{
}

HEADER_ONLY_INCLUDE
BsonPrinter::BsonPrinter(std::ostream& output, PrinterConfig config)
    : PrinterInterface(output, config)
{}

HEADER_ONLY_INCLUDE
void BsonPrinter::openDoc()
{}

HEADER_ONLY_INCLUDE
void BsonPrinter::closeDoc()
{}

HEADER_ONLY_INCLUDE
void BsonPrinter::openMap()
{}

HEADER_ONLY_INCLUDE
void BsonPrinter::closeMap()
{}

HEADER_ONLY_INCLUDE
void BsonPrinter::openArray(std::size_t /*size*/)
{}

HEADER_ONLY_INCLUDE
void BsonPrinter::closeArray()
{}

HEADER_ONLY_INCLUDE
void BsonPrinter::addKey(std::string const& /*key*/)
{}

HEADER_ONLY_INCLUDE void BsonPrinter::addValue(short /*value*/)                 {}
HEADER_ONLY_INCLUDE void BsonPrinter::addValue(int /*value*/)                   {}
HEADER_ONLY_INCLUDE void BsonPrinter::addValue(long /*value*/)                  {}
HEADER_ONLY_INCLUDE void BsonPrinter::addValue(long long /*value*/)             {}

HEADER_ONLY_INCLUDE void BsonPrinter::addValue(unsigned short /*value*/)        {}
HEADER_ONLY_INCLUDE void BsonPrinter::addValue(unsigned int /*value*/)          {}
HEADER_ONLY_INCLUDE void BsonPrinter::addValue(unsigned long /*value*/)         {}
HEADER_ONLY_INCLUDE void BsonPrinter::addValue(unsigned long long /*value*/)    {}

HEADER_ONLY_INCLUDE void BsonPrinter::addValue(float /*value*/)                 {}
HEADER_ONLY_INCLUDE void BsonPrinter::addValue(double /*value*/)                {}
HEADER_ONLY_INCLUDE void BsonPrinter::addValue(long double /*value*/)           {}

HEADER_ONLY_INCLUDE void BsonPrinter::addValue(bool /*value*/)                  {}

HEADER_ONLY_INCLUDE void BsonPrinter::addValue(std::string const& /*value*/)    {}

HEADER_ONLY_INCLUDE void BsonPrinter::addRawValue(std::string const& /*value*/) {}

HEADER_ONLY_INCLUDE void BsonPrinter::addNull()                                 {}
