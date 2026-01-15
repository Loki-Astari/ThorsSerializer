#ifndef THORSANVIL_SERIALIZE_BSON_PRINTER_CONFIG_H
#define THORSANVIL_SERIALIZE_BSON_PRINTER_CONFIG_H

#include "SerializeConfig.h"
#include "MongoUtilityObjectId.h"

#include <functional>
#include <optional>

namespace ThorsAnvil::Serialize
{

enum class BsonContainer;
using IdStore   = std::optional<std::reference_wrapper<std::vector<MongoUtility::ObjectID>>>;

struct PrinterConfig;
struct BsonPrinterConfig
{
    PrinterConfig const&    config;
    BsonContainer           parserInfo;
    IdStore                 idStore;
    public:
        BsonPrinterConfig(PrinterConfig const& config, BsonContainer parserInfo, IdStore idStore);
};

struct ParserConfig;
struct BsonParserConfig
{
    ParserConfig const&     config;
    BsonContainer           parserInfo;

    public:
        BsonParserConfig(ParserConfig const& config, BsonContainer parserInfo);
};
}

#endif
