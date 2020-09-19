#ifndef THORS_ANVIL_SERIALIZE_IMPORTER_H
#define THORS_ANVIL_SERIALIZE_IMPORTER_H
/*
 * The Importer simply wrap an object of type T so that when de-serialized
 * it creates an object of type DeSerializer and calls it appropriately.
 */

#include "Serialize.h"

namespace ThorsAnvil
{
    namespace Serialize
    {

template<typename Format, typename T>
class Importer
{
    using ParserConfig = ParserInterface::ParserConfig;
    T&              value;
    ParserConfig    config;
    public:
        Importer(T& value, ParserConfig config = ParserConfig{})
            : value(value)
            , config(config)
        {}
        friend std::istream& operator>>(std::istream& stream, Importer const& data)
        {
            try
            {
                typename Format::Parser     parser(stream, data.config);
                DeSerializer                deSerializer(parser);

                deSerializer.parse(data.value);
            }
            catch (std::exception const& e)
            {
                std::string message = ThorsAnvil::Utility::buildErrorMessage(
                                            "ThorsAnvil::Serialize::Exporter",
                                            "operator>>",
                                            "Caught Exception: ", e.what());
                VLOG_F(2, "%s", message.c_str());
                stream.setstate(std::ios::failbit);
                if (!data.config.catchExceptions)
                {
                    std::string message = ThorsAnvil::Utility::buildErrorMessage(
                                            "ThorsAnvil::Serialize::Exporter",
                                            "operator<<",
                                            "Rethrowing Exception");
                    VLOG_F(2, "%s", message.c_str());
                    throw;
                }
            }
            catch (...)
            {
                std::string message = ThorsAnvil::Utility::buildErrorMessage(
                                            "ThorsAnvil::Serialize::Exporter",
                                            "operator<<",
                                            "Caught Exception: UNKNOWN");
                VLOG_F(2, "%s", message.c_str());
                stream.setstate(std::ios::failbit);
                if (!data.config.catchExceptions)
                {
                    std::string message = ThorsAnvil::Utility::buildErrorMessage(
                                            "ThorsAnvil::Serialize::Exporter",
                                            "operator<<",
                                            "Rethrowing Exception: UNKNOWN");
                    VLOG_F(2, "%s", message.c_str());
                    throw;
                }
            }
            return stream;
        }
};

template<typename Format, typename T>
Importer<Format, T> Import(T const& value, ParserInterface::ParserConfig config = ParserInterface::ParserConfig{})
{
    return Importer<Format, T>(value, config);
}


    }
}

#endif
