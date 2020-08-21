#include "SerializeConfig.h"
#include "BsonParser.h"
#include "JsonLexemes.h"
#include "UnicodeIterator.h"
#include "ThorsIOUtil/Utility.h"
#include <map>
#include <cstdlib>
#include <cstring>

using namespace ThorsAnvil::Serialize;
using ParserToken = ParserInterface::ParserToken;

HEADER_ONLY_INCLUDE
BsonParser::BsonParser(std::istream& stream, ParserConfig config)
    : ParserInterface(stream, config)
    , nextToken(ParserToken::DocStart)
    , nextType('\x00')
    , skipOverValue(false)
{
    currentContainer.emplace_back(static_cast<BsonContainer>(config.parserInfo));
}

HEADER_ONLY_INCLUDE
ParserToken BsonParser::getNextToken()
{
    if (skipOverValue)
    {
        skipOverValue = false;
        if (!isEndOfContainer(0))
        {
            nextType  = '\x00';
            nextToken = ParserToken::Key;
        }
    }

    ParserToken result = nextToken;
    switch (nextToken)
    {
        case ParserToken::DocStart:
        {
            switch (currentContainer.back())
            {
                case BsonContainer::Map:    nextToken = ParserToken::MapStart;  break;
                case BsonContainer::Array:  nextToken = ParserToken::ArrayStart;break;
                case BsonContainer::Value:
                {
                    nextToken = ParserToken::Key;
                    currentContainer.emplace_back(BsonContainer::Value);
                    std::int32_t    size = readSize<4, std::int32_t>();
                    dataSize.emplace_back(size);
                    dataLeft.emplace_back(size);
                    dataLeft.back() -= 4;
                    break;
                }
            }
            break;
        }
        case ParserToken::DocEnd:
        {
            if (currentContainer.back() == BsonContainer::Value)
            {
                readEndOfContainer();
            }
            nextToken = ParserToken::Error;
            break;
        }
        case ParserToken::MapStart:
        case ParserToken::ArrayStart:
        {
            std::int32_t    size = readSize<4, std::int32_t>();
            dataSize.emplace_back(size);
            dataLeft.emplace_back(size);
            dataLeft.back() -= 4;
            if (dataLeft.back() == 1)
            {
                nextToken = currentContainer.back() == BsonContainer::Map ? ParserToken::MapEnd: ParserToken::ArrayEnd;
                break;
            }
            nextToken = ParserToken::Key;
            break;
        }
        case ParserToken::MapEnd:
        case ParserToken::ArrayEnd:
        {
            readEndOfContainer();
            currentContainer.pop_back();
            dataLeft.pop_back();
            if (currentContainer.empty())
            {
                dataSize.pop_back();
                nextToken = ParserToken::DocEnd;
                break;
            }
            dataLeft.back() -= dataSize.back();
            dataSize.pop_back();
            if (isEndOfContainer(0))
            {
                // isEndOfContainer set the correct nextToken
                break;
            }
            nextToken = ParserToken::Key;
            break;
        }
        case ParserToken::Key:
        {
            readKey();
            nextToken = ParserToken::Value;
            BsonContainer   currentContainerType = currentContainer.back();
            if (nextType == '\x03')
            {
                currentContainer.push_back(BsonContainer::Map);
                nextToken = ParserToken::MapStart;
            }
            else if (nextType == '\x04')
            {
                currentContainer.push_back(BsonContainer::Array);
                nextToken = ParserToken::ArrayStart;
            }
            if (currentContainerType == BsonContainer::Array || currentContainerType == BsonContainer::Value)
            {
                return getNextToken();;
            }
            break;
            // Array and Value fall through to read the value we
            // Want to extract next.
        }
        case ParserToken::Value:
        {
            skipOverValue = true;
            break;
        }
        default:

            throw std::runtime_error(
                        ThorsAnvil::Utility::buildErrorMessage("ThorsAnvil::Serialize::BsonParser", "getNextToken",
                                                               "Invalid state reached in switch")
                                    );
    }
#if 0
    switch (result)
    {
        case ParserToken::Error: std::cerr << "Error";
        case ParserToken::DocStart:  std::cerr << "DocStart";    break;
        case ParserToken::DocEnd:    std::cerr << "DocEnd";      break;
        case ParserToken::MapStart:  std::cerr << "MapStart";    break;
        case ParserToken::MapEnd:    std::cerr << "MapEnd";      break;
        case ParserToken::ArrayStart:std::cerr << "ArrayStart";  break;
        case ParserToken::ArrayEnd:  std::cerr << "ArrayEnd";    break;
        case ParserToken::Key:       std::cerr << "Key";         break;
        case ParserToken::Value:     std::cerr << "Value";       break;
    }
    std::cerr << "\n";
#endif
    return result;
}

HEADER_ONLY_INCLUDE
void BsonParser::ignoreDataValue()
{
    if (skipOverValue == false)
    {
        return;
    }
    std::size_t size;
    switch (nextType)
    {
        case '\x01':    input.ignore(8);    dataLeft.back() -= 8;   break;
        case '\x13':    input.ignore(16);   dataLeft.back() -= 16;  break;
        case '\x10':    input.ignore(4);    dataLeft.back() -= 4;   break;
        case '\x12':    input.ignore(8);    dataLeft.back() -= 8;   break;
        case '\x08':    input.ignore(1);    dataLeft.back() -= 1;   break;
        case '\x0A':                                                break;
        case '\x02':    size = readSize<4, std::int32_t>();input.ignore(size);      dataLeft.back() -= (size + 4);  break;
        case '\x05':    size = readSize<4, std::int32_t>();input.ignore(size + 1);  dataLeft.back() -= (size + 5);  break;
        default:
            throw std::runtime_error(
                        ThorsAnvil::Utility::buildErrorMessage("ThorsAnvil::Serialize::BsonParser", "ignoreDataValue",
                                                                "trying to ignore a non value")
                                    );
    }
}

HEADER_ONLY_INCLUDE
bool BsonParser::isEndOfContainer(std::size_t excess)
{
    if (dataLeft.back() - excess  == 1)
    {
        switch (currentContainer.back())
        {
            case BsonContainer::Map:    nextToken = ParserToken::MapEnd;    break;
            case BsonContainer::Array:  nextToken = ParserToken::ArrayEnd;  break;
            case BsonContainer::Value:
            {
                nextToken = ParserToken::DocEnd;
                break;
            }
        }

        return true;
    }
    return false;
}

HEADER_ONLY_INCLUDE
void BsonParser::readEndOfContainer()
{
    char    mark;
    input.read(&mark, 1);
    dataLeft.back() -= 1;
    if (mark != '\x00')
    {
        throw std::runtime_error(
                ThorsAnvil::Utility::buildErrorMessage("ThorsAnvil::Serialize::BsonParser", "readEndOfContainer",
                                                      "End of container marker should be '\\x00' but is >", static_cast<int>(mark), "<")
                                );
    }
}

HEADER_ONLY_INCLUDE
void BsonParser::readKey()
{
    input.read(&nextType, 1);
    std::getline(input, nextKey, '\0');
    dataLeft.back() -= (1 + nextKey.size() + 1);
}

HEADER_ONLY_INCLUDE
template<std::size_t size, typename Int>
Int BsonParser::readSize()
{
    return readLE<size, Int>();
}

HEADER_ONLY_INCLUDE
template<std::size_t size, typename Int>
Int BsonParser::readInt()
{
    dataLeft.back() -= size;
    return readLE<size, Int>();
}

HEADER_ONLY_INCLUDE
template<std::size_t size>
IEEE_754::_2008::Binary<size * 8> BsonParser::readFloat()
{
    IEEE_754::_2008::Binary<size * 8> result;
    input.read(reinterpret_cast<char*>(&result), size);
    dataLeft.back() -= size;
    return result;
}

HEADER_ONLY_INCLUDE
bool BsonParser::readBool()
{
    bool result;
    input.read(reinterpret_cast<char*>(&result) ,1);
    dataLeft.back() -= 1;
    return result;
}

HEADER_ONLY_INCLUDE
std::size_t BsonParser::peekSize()
{
    std::int32_t size;

    std::streampos pos = input.tellg();
    input.read(reinterpret_cast<char*>(&size), 4);
    input.seekg(pos);

    return boost::endian::little_to_native(size);
}

HEADER_ONLY_INCLUDE
std::string BsonParser::readString()
{
    std::int32_t size = readSize<4, std::int32_t>();
    dataLeft.back() -= 4;
    std::string     result(size, '\0');
    input.read(&result[0], size);
    dataLeft.back() -= size;
    result.resize(size - 1);
    return result;
}

HEADER_ONLY_INCLUDE
void BsonParser::readNull()
{}

HEADER_ONLY_INCLUDE
std::string BsonParser::readBinary()
{
    std::int32_t size = readSize<4, std::int32_t>();
    dataLeft.back() -= 4;
    char subType;
    input.read(reinterpret_cast<char*>(&subType), 1);
    dataLeft.back() -= 1;
    std::string result(size, '\0');
    input.read(&result[0], size);
    dataLeft.back() -= size;
    return result;
}

HEADER_ONLY_INCLUDE
std::string BsonParser::getKey()
{
    return nextKey;
}

HEADER_ONLY_INCLUDE
template<std::size_t Size, typename Int>
Int BsonParser::getIntValue()
{
    if (nextType == '\x10')     {return readInt<4, std::int32_t>();}
    if (nextType == '\x12')     {return readInt<8, std::int64_t>();}
    badType();
}

HEADER_ONLY_INCLUDE
template<std::size_t Size, typename Float>
Float BsonParser::getFloatValue()
{
    if (nextType == '\x10')     {return readInt<4, std::int32_t>();}
    if (nextType == '\x12')     {return readInt<8, std::int64_t>();}
    if (nextType == '\x01')     {return readFloat<8>();}
#if 0
    if (nextType == '\x13')     {return readFloat<16>();}
#endif
    badType();
}

HEADER_ONLY_INCLUDE
std::string BsonParser::getRawValue()
{
    switch (nextType)
    {
        case '\x10':            return std::to_string(readInt<4, std::int32_t>());
        case '\x12':            return std::to_string(readInt<8, std::int64_t>());
        case '\x01':            return std::to_string(readFloat<8>());
#if 0
        case '\x13':            return std::to_string(readFloat<16>());
#endif
        case '\x08':            return readBool() ? "true" : "false";
        case '\x0A':            readNull(); return "null";
        case '\x02':
        {
#pragma vera-pushoff
            using namespace std::string_literals;
#pragma vera-pop
            return "\""s + readString() + "\"";
        }
        case '\x05':         return readBinary();
        default:
            throw std::runtime_error(
                        ThorsAnvil::Utility::buildErrorMessage("ThorsAnvil::Serialize::BsonParser", "getRawValue",
                                    "Could not convert the data into raw output for some reason")
                                    );
    }
}
