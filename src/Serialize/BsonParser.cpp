#include "SerializeConfig.h"
#include "BsonParser.h"
#include "JsonLexemes.h"
#include "UnicodeIterator.h"
#include <map>
#include <cstdlib>
#include <cstring>
#include <boost/endian/conversion.hpp>

using namespace ThorsAnvil::Serialize;
using ParserToken = ParserInterface::ParserToken;

static constexpr ValueType intReadType[]    = {ValueType::Int32, ValueType::Int64};
static constexpr ValueType floatReadType[]  = {ValueType::Double64, ValueType::Double128};

HEADER_ONLY_INCLUDE
BsonParser::BsonParser(std::istream& stream, ParserConfig config)
    : ParserInterface(stream, config)
    , currentValue(ValueType::Obj)
{
    currentContainer.emplace_back(static_cast<BsonContainer>(config.parserInfo));
    nextToken = ParserToken::DocStart;
}

HEADER_ONLY_INCLUDE
ParserToken BsonParser::getNextToken()
{
    ParserToken result = nextToken;
    currentValue    = ValueType::Obj;
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
                    std::int32_t    size = readSize<4, std::int32_t>(true);
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
            nextToken = ParserToken::Error;
            break;
        }
        case ParserToken::MapStart:
        case ParserToken::ArrayStart:
        {
            std::int32_t    size = readSize<4, std::int32_t>(true);
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
            char    mark;
            input.read(&mark, 1);
            dataLeft.back() -= 1;
            if (mark != '\x00')
            {
                throw std::runtime_error("Bad Marker");
            }
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
            if (isEndOfContainer())
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
            readValue(true);
            break;
        }
        default:
            throw std::runtime_error("Bad State");
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
void BsonParser::readValue(bool useValue)
{
    switch (nextType)
    {
        case '\x01':    valueFloat64    = readFloat<8>(useValue);                   break;
        case '\x02':    valueString     = readString(useValue);                     break;
        case '\x05':    valueBinary     = readBinary(useValue);                     break;
        case '\x08':    valueBool       = readBool(useValue);                       break;
        case '\x0A':                      readNull(useValue);                       break;
        case '\x10':    valueInt32      = readInt<4, std::int32_t>(useValue);       break;
        case '\x12':    valueInt64      = readInt<8, std::int64_t>(useValue);       break;
#if 0
        case '\x13':    valueFloat128   = readFloat<16>(useValue);                  break;
#endif
        default:
            throw std::runtime_error("ThorsAnvil::Serialize::BsonParser::getNextToken: Un-known Value type");
    }
    if (isEndOfContainer())
    {
        // isEndOfContainer set the correct nextToken
        return;
    }
    nextToken = ParserToken::Key;
}

HEADER_ONLY_INCLUDE
bool BsonParser::isEndOfContainer()
{
    if (dataLeft.back() == 1)
    {
        switch (currentContainer.back())
        {
            case BsonContainer::Map:    nextToken = ParserToken::MapEnd;    break;
            case BsonContainer::Array:  nextToken = ParserToken::ArrayEnd;  break;
            case BsonContainer::Value:
            {
                nextToken = ParserToken::DocEnd;
                input.ignore();
                break;
            }
        }

        return true;
    }
    return false;
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
Int BsonParser::readSize(bool)
{
    Int docSize;
    input.read(reinterpret_cast<char*>(&docSize), sizeof(docSize));
    return boost::endian::little_to_native(docSize);
}

HEADER_ONLY_INCLUDE
template<std::size_t size, typename Int>
Int BsonParser::readInt(bool use)
{
    currentValue = intReadType[size/4 - 1];
    dataLeft.back() -= size;
    return readSize<size, Int>(use);
}

HEADER_ONLY_INCLUDE
template<std::size_t size>
IEEE_754::_2008::Binary<size * 8> BsonParser::readFloat(bool)
{
    currentValue = floatReadType[size/8 - 1];
    IEEE_754::_2008::Binary<size * 8> result;
    input.read(reinterpret_cast<char*>(&result), size);
    dataLeft.back() -= size;
    return result;
}

HEADER_ONLY_INCLUDE
bool BsonParser::readBool(bool)
{
    currentValue = ValueType::Bool;
    bool result;
    input.read(reinterpret_cast<char*>(&result) ,1);
    dataLeft.back() -= 1;
    return result;
}

HEADER_ONLY_INCLUDE
std::string BsonParser::readString(bool)
{
    currentValue = ValueType::String;
    std::int32_t size = readSize<4, std::int32_t>(true);
    dataLeft.back() -= 4;
    std::string     result(size, '\0');
    input.read(&result[0], size);
    dataLeft.back() -= size;
    result.resize(size - 1);
    return result;
}

HEADER_ONLY_INCLUDE
void BsonParser::readNull(bool)
{
    currentValue = ValueType::Null;
}

HEADER_ONLY_INCLUDE
std::string BsonParser::readBinary(bool)
{
    currentValue = ValueType::Binary;
    std::int32_t size = readSize<4, std::int32_t>(true);
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
Int BsonParser::returnIntValue()
{
    if (currentValue == ValueType::Int32)       {return valueInt32;}
    if (currentValue == ValueType::Int64)       {return valueInt64;}
    badType();
}

HEADER_ONLY_INCLUDE
template<std::size_t Size, typename Float>
Float BsonParser::returnFloatValue()
{
    if (currentValue == ValueType::Int32)       {return valueInt32;}
    if (currentValue == ValueType::Int64)       {return valueInt64;}
    if (currentValue == ValueType::Double64)    {return valueFloat64;}
#if 0
    if (currentValue == ValueType::Double128)   {return valueFloat128;}
#endif
    badType();
}

HEADER_ONLY_INCLUDE
std::string BsonParser::getRawValue()
{
    switch (currentValue)
    {
        case ValueType::Int32:          return std::to_string(valueInt32);
        case ValueType::Int64:          return std::to_string(valueInt64);
        case ValueType::Double64:       return std::to_string(valueFloat64);
#if 0
        case ValueType::Double128:      return std::to_string(valueFloat128);
#endif
        case ValueType::Bool:           return valueBool ? "true" : "false";
        case ValueType::String:         return std::string("\"") + valueString + "\"";
        case ValueType::Null:           return "null";
        case ValueType::Binary:         return valueBinary;
        default:
            throw std::runtime_error("Invalid Type from RAW");
    }
}
