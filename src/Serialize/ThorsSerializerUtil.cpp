#include "SerializeConfig.h"
#include "ThorsSerializerUtil.h"
#include "ThorsIOUtil/Utility.h"
#include "Logging/loguru.hpp"
#include <string>

#pragma vera-pushoff
using namespace std::string_literals;
#pragma vera-pop

using namespace ThorsAnvil::Serialize;

std::string const ThorsAnvil::Serialize::defaultPolymorphicMarker = "__type"s;

HEADER_ONLY_INCLUDE
void ParserInterface::ignoreValue()
{
    if (config.parseStrictness != ParseType::Weak)
    {
        std::string message = ThorsAnvil::Utility::buildErrorMessage(
                                "ThorsAnvil::Serialize::ParserInterface",
                                "ignoreValue",
                                "In Strict parser mode not allowed to ignore values.");
        VLOG_F(2, "%s", message.c_str());
        throw std::runtime_error(message);
    }

    ignoreTheValue();
}

HEADER_ONLY_INCLUDE
void ParserInterface::ignoreTheMap()
{
    for (ParserToken token = getNextToken(); token != ParserToken::MapEnd; token = getNextToken())
    {
        ignoreDataValue();
        if (token != ParserToken::Key)
        {
            std::string message = ThorsAnvil::Utility::buildErrorMessage(
                                    "ThorsAnvil::Serialize::ParserInterface",
                                    "ignoreTheMap",
                                    "Invalid token found. (Expecting Key)");
            VLOG_F(2, "%s", message.c_str());
            throw std::runtime_error(message);
        }
        ignoreTheValue();
    }
}

HEADER_ONLY_INCLUDE
void ParserInterface::ignoreTheArray()
{
    ParserToken token = getNextToken();
    while (token != ParserToken::ArrayEnd)
    {
        switch (token)
        {
            case ParserToken::Error:
            {
                std::string message = ThorsAnvil::Utility::buildErrorMessage(
                                        "ThorsAnvil::Serialize::ParserInterface",
                                        "ignoreTheArray",
                                        "Invalid token found: Error");
                VLOG_F(2, "%s", message.c_str());
                throw std::runtime_error(message);
            }
            case ParserToken::Key:
            {
                std::string message = ThorsAnvil::Utility::buildErrorMessage(
                                        "ThorsAnvil::Serialize::ParserInterface",
                                        "ignoreTheArray",
                                        "Invalid token found: Key");
                VLOG_F(2, "%s", message.c_str());
                throw std::runtime_error(message);
            }
            case ParserToken::MapEnd:
            {
                std::string message = ThorsAnvil::Utility::buildErrorMessage(
                                        "ThorsAnvil::Serialize::ParserInterface",
                                        "ignoreTheArray",
                                        "Invalid token found: MapEnd");
                VLOG_F(2, "%s", message.c_str());
                throw std::runtime_error(message);
            }
            case ParserToken::Value:     ignoreDataValue(); break;
            case ParserToken::MapStart:  ignoreTheMap();    break;
            case ParserToken::ArrayStart:ignoreTheArray();  break;
            default:
            {
                std::string message = ThorsAnvil::Utility::buildErrorMessage(
                                        "ThorsAnvil::Serialize::ParserInterface",
                                        "ignoreTheArray",
                                        "Invalid token found: Unknown");
                VLOG_F(2, "%s", message.c_str());
                throw std::runtime_error(message);
            }
        }
        token = getNextToken();
    }
}

HEADER_ONLY_INCLUDE
void ParserInterface::ignoreTheValue()
{
    ParserToken token = getNextToken();
    switch (token)
    {
        case ParserToken::Error:
        {
            std::string message = ThorsAnvil::Utility::buildErrorMessage(
                                    "ThorsAnvil::Serialize::ParserInterface",
                                    "ignoreTheValue",
                                    "Invalid token found: Error");
            VLOG_F(2, "%s", message.c_str());
            throw std::runtime_error(message);
        }
        case ParserToken::Key:
        {
            std::string message = ThorsAnvil::Utility::buildErrorMessage(
                                    "ThorsAnvil::Serialize::ParserInterface",
                                    "ignoreTheValue",
                                    "Invalid token found: Key");
            VLOG_F(2, "%s", message.c_str());
            throw std::runtime_error(message);
        }
        case ParserToken::MapEnd:
        {
            std::string message = ThorsAnvil::Utility::buildErrorMessage(
                                    "ThorsAnvil::Serialize::ParserInterface",
                                    "ignoreTheValue",
                                    "Invalid token found: MapEnd");
            VLOG_F(2, "%s", message.c_str());
            throw std::runtime_error(message);
        }
        case ParserToken::ArrayEnd:
        {
            std::string message = ThorsAnvil::Utility::buildErrorMessage(
                                    "ThorsAnvil::Serialize::ParserInterface",
                                    "ignoreTheValue",
                                    "Invalid token found: ArrayEnd");
            VLOG_F(2, "%s", message.c_str());
            throw std::runtime_error(message);
        }
        case ParserToken::Value:     ignoreDataValue(); break;
        case ParserToken::MapStart:  ignoreTheMap();    break;
        case ParserToken::ArrayStart:ignoreTheArray();  break;
        default:
        {
            std::string message = ThorsAnvil::Utility::buildErrorMessage(
                                    "ThorsAnvil::Serialize::ParserInterface",
                                    "ignoreTheValue",
                                    "Invalid token found: Unknown");
            VLOG_F(2, "%s", message.c_str());
            throw std::runtime_error(message);
        }
    }
}
