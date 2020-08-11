#include "SerializeConfig.h"
#include "BsonParser.h"
#include "JsonLexemes.h"
#include "UnicodeIterator.h"
#include <map>
#include <cstdlib>
#include <cstring>

using namespace ThorsAnvil::Serialize;
using ParserToken = ParserInterface::ParserToken;

// enum class ParserToken {Error, DocStart, DocEnd, MapStart, MapEnd, ArrayStart, ArrayEnd, Key, Value};

HEADER_ONLY_INCLUDE
BsonParser::BsonParser(std::istream& stream, ParserConfig config)
    : ParserInterface(stream, config)
{
    currentContainer.emplace_back(static_cast<BsonContainer>(config.parserInfo));
    nextToken = ParserToken::DocStart;
}

HEADER_ONLY_INCLUDE
void BsonParser::readKey()
{
    input.read(&nextType, 1);
    std::getline(input, nextKey, '\0');
    dataLeft.back() -= (1 + nextKey.size() + 1);
}

#if 0
    enum ValueType {Double64, String, Binary, Bool, Null, Int32, Int64};
    ValueType                   currentValue;
    double                      valueDouble;
    std::string                 valueString;
    std::string                 valueBinary;
    bool                        valueBool;
    std::int32_t                valueInt32;
    std::int64_t                valueInt64;
#endif

HEADER_ONLY_INCLUDE
template<std::size_t size, typename Int>
Int BsonParser::readInt(bool)
{
    //currentValue = Int32;
    //currentValue = Int64;
    Int x = 0;
    return x;
}

HEADER_ONLY_INCLUDE
template<std::size_t size>
IEEE_754::_2008::Binary<size * 8> BsonParser::readFloat(bool)
{
    IEEE_754::_2008::Binary<size * 8> result;
    input.read(reinterpret_cast<char*>(&result), size);

    if constexpr (size == 8)
    {
        currentValue = Double64;
    }
    else if constexpr (size == 16)
    {
        currentValue = Double128;
    }
    return result;
}

HEADER_ONLY_INCLUDE
void BsonParser::readBool(bool)
{
    currentValue = Bool;
}

HEADER_ONLY_INCLUDE
void BsonParser::readString(bool)
{
    currentValue = String;
}

HEADER_ONLY_INCLUDE
void BsonParser::readNull(bool)
{
    currentValue = Null;
}

HEADER_ONLY_INCLUDE
void BsonParser::readBinary(bool)
{
    currentValue = Binary;
}

HEADER_ONLY_INCLUDE
ParserToken BsonParser::getNextToken()
{
    ParserToken result = nextToken;
    switch (nextToken)
    {
        case ParserToken::DocStart:
        {
            nextToken = currentContainer.back() == BsonContainer::Map ? ParserToken::MapStart : ParserToken::ArrayStart;
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
            std::int32_t    size = readInt<4, std::int32_t>(true);
            dataLeft.emplace_back(size);
            dataSize.emplace_back(size);
            if (dataLeft.back() == 0)
            {
                nextToken = currentContainer.back() == BsonContainer::Map ? ParserToken::MapEnd: ParserToken::ArrayEnd;
                break;
            }
            readKey();
            nextToken = ParserToken::Key;
            break;
        }
        case ParserToken::MapEnd:
        case ParserToken::ArrayEnd:
        {
            char    mark;
            input.read(&mark, 1);
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
            if (dataLeft.back() == 0)
            {
                nextToken = currentContainer.back() == BsonContainer::Map ? ParserToken::MapEnd: ParserToken::ArrayEnd;
                break;
            }
            readKey();
            nextToken = ParserToken::Key;
            break;
        }
        case ParserToken::Key:
        {
            nextToken = ParserToken::Value;
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
            if (currentContainer.back() == BsonContainer::Array)
            {
                return getNextToken();
            }
            break;
        }
        case ParserToken::Value:
        {
            readValue(true);
            break;
        }
        default:
            throw std::runtime_error("Bad State");
    }

    return result;
}

HEADER_ONLY_INCLUDE
void BsonParser::readValue(bool useValue)
{
    switch (nextType)
    {
        case '\x01':    valueFloat64 = readFloat<8>(useValue);     break;
        case '\x02':    readString(useValue);       break;
        case '\x05':    readBinary(useValue);       break;
        case '\x08':    readBool(useValue);         break;
        case '\x0A':    readNull(useValue);         break;
        case '\x10':    valueInt32 = readInt<4, std::int32_t>(useValue);       break;
        case '\x12':    valueInt64 = readInt<8, std::int64_t>(useValue);       break;
#if 0
        case '\x13':    valueFloat128 = readFloat<16>(useValue);    break;
#endif
        default:
            throw std::runtime_error("ThorsAnvil::Serialize::BsonParser::getNextToken: Un-known Value type");
    }
    if (dataLeft.back() == 0)
    {
        nextToken = currentContainer.back() == BsonContainer::Map ? ParserToken::MapEnd: ParserToken::ArrayEnd;
        return;
    }
    readKey();
    nextToken = ParserToken::Key;
}

HEADER_ONLY_INCLUDE
void BsonParser::ignoreDataValue()
{
    readValue(false);
}

HEADER_ONLY_INCLUDE
std::string BsonParser::getKey()
{
    return nextKey;
}

HEADER_ONLY_INCLUDE
template<typename Int>
Int BsonParser::returnIntValue()
{
    if (currentValue == Int32) {return valueInt32;}
    if (currentValue == Int64) {return valueInt64;}
    badType();
}

HEADER_ONLY_INCLUDE
template<typename Float>
Float BsonParser::returnFloatValue()
{
    if (currentValue == Double64)   {return valueFloat64;}
#if 0
    if (currentValue == Double128)  {return valueFloat128;}
#endif
    badType();
}

HEADER_ONLY_INCLUDE
void BsonParser::badType()
{
    throw std::runtime_error("Invalid Type in Bson");
}

HEADER_ONLY_INCLUDE void BsonParser::getValue(short int& value)                     {value = returnIntValue<short int>();}
HEADER_ONLY_INCLUDE void BsonParser::getValue(int& value)                           {value = returnIntValue<int>();}
HEADER_ONLY_INCLUDE void BsonParser::getValue(long int& value)                      {value = returnIntValue<long int>();}
HEADER_ONLY_INCLUDE void BsonParser::getValue(long long int& value)                 {value = returnIntValue<long long int>();}

HEADER_ONLY_INCLUDE void BsonParser::getValue(unsigned short int& value)            {value = returnIntValue<unsigned short int>();}
HEADER_ONLY_INCLUDE void BsonParser::getValue(unsigned int& value)                  {value = returnIntValue<unsigned int>();}
HEADER_ONLY_INCLUDE void BsonParser::getValue(unsigned long int& value)             {value = returnIntValue<unsigned long int>();}
HEADER_ONLY_INCLUDE void BsonParser::getValue(unsigned long long int& value)        {value = returnIntValue<unsigned long long int>();}

HEADER_ONLY_INCLUDE void BsonParser::getValue(float& value)                         {value = returnFloatValue<float>();}
HEADER_ONLY_INCLUDE void BsonParser::getValue(double& value)                        {value = returnFloatValue<double>();}
HEADER_ONLY_INCLUDE void BsonParser::getValue(long double& value)                   {value = returnFloatValue<long double>();}

HEADER_ONLY_INCLUDE void BsonParser::getValue(bool& value)                          {if (currentValue == Bool)      {value = valueBool;}    badType();}
HEADER_ONLY_INCLUDE void BsonParser::getValue(std::string& value)                   {if (currentValue == String)    {value = valueString;}  badType();}

HEADER_ONLY_INCLUDE bool BsonParser::isValueNull()                                  {return (currentValue == Null);}

HEADER_ONLY_INCLUDE std::string BsonParser::getRawValue()                           {if (currentValue == Binary)    {return valueBinary;}   badType();}
