#include "SerializeConfig.h"
#include "BsonManualLexer.h"
#include "JsonLexemes.h"
#include "UnicodeIterator.h"

#include <limits>
#include <cstring>

using namespace ThorsAnvil::Serialize;

HEADER_ONLY_INCLUDE
BsonManualLexer::BsonManualLexer(std::istream& str)
    : str(str)
    , lastNull(false)
{}

HEADER_ONLY_INCLUDE
int BsonManualLexer::yylex()
{
    char    next;
    str >> next;
    buffer.clear();
    lastNull = false;
    switch (next)
    {
        case '{':
        case '}':
        case '[':
        case ']':
        case ',':
        case ':':
        {
            return lastToken = next;
        }
        case 't':
        {
            readTrue();
            lastBool = true;
            return lastToken = ThorsAnvil::Serialize::JSON_TRUE;
        }
        case 'f':
        {
            readFalse();
            lastBool = false;
            return lastToken = ThorsAnvil::Serialize::JSON_FALSE;
        }
        case 'n':
        {
            readNull();
            lastNull = true;
            return lastToken = ThorsAnvil::Serialize::JSON_NULL;
        }
        case '"':
        {
            str.unget();
            return lastToken = ThorsAnvil::Serialize::JSON_STRING;
        }
        default:
        {
            return lastToken = readNumber(next)
                ? ThorsAnvil::Serialize::JSON_INTEGER
                : ThorsAnvil::Serialize::JSON_FLOAT;
        }
    }
}

HEADER_ONLY_INCLUDE
void BsonManualLexer::readTrue()
{
    checkFixed("true", 4);
}

HEADER_ONLY_INCLUDE
void BsonManualLexer::readFalse()
{
    checkFixed("false", 5);
}

HEADER_ONLY_INCLUDE
void BsonManualLexer::readNull()
{
    checkFixed("null", 4);
}

HEADER_ONLY_INCLUDE
void BsonManualLexer::ignoreRawValue()
{
    if (lastToken == ThorsAnvil::Serialize::JSON_STRING)
    {
        char last = str.get();  // Read the first Quote off the stream
        int next = str.get();
        while (next != EOF && !(next == '"' && last != '\\'))
        {
            last = next;
            next = str.get();
        }
        if (next == EOF)
        {
            error();
        }
    }
}

HEADER_ONLY_INCLUDE
std::string BsonManualLexer::getRawString()
{
    switch (lastToken)
    {
        case '{':   return "{";
        case '}':   return "}";
        case '[':   return "[";
        case ']':   return "]";
        case ',':   return ",";
        case ':':   return ":";
        case ThorsAnvil::Serialize::JSON_TRUE:  return "true";
        case ThorsAnvil::Serialize::JSON_FALSE: return "false";
        case ThorsAnvil::Serialize::JSON_NULL:  return "null";
        case ThorsAnvil::Serialize::JSON_INTEGER:
        case ThorsAnvil::Serialize::JSON_FLOAT:
        {
            return buffer;
        }
        case ThorsAnvil::Serialize::JSON_STRING:
        {
            std::string result;

            char last = str.get();  // Read the first Quote off the stream
            result.push_back(last);
            int next = str.get();
            while (next != EOF && !(next == '"' && last != '\\'))
            {
                if (next < 0x20)
                {
                    throw std::runtime_error("X");
                }
                result.push_back(next);
                last = next;
                next = str.get();
            }
            if (next == EOF)
            {
                error();
            }
            result.push_back('"');
            return result;
        }
        default:
        {
            throw std::runtime_error("Not Supported: Unexpected");
        }
    }
}

HEADER_ONLY_INCLUDE
std::string BsonManualLexer::getString()
{
    return std::string(make_UnicodeWrapperIterator(std::istreambuf_iterator<char>(str)), make_EndUnicodeWrapperIterator(std::istreambuf_iterator<char>(str)));
}

HEADER_ONLY_INCLUDE
bool BsonManualLexer::getLastBool() const
{
    if (lastToken == ThorsAnvil::Serialize::JSON_TRUE || lastToken == ThorsAnvil::Serialize::JSON_FALSE)
    {
        return lastBool;
    }
    else
    {
        throw std::runtime_error("ThorsAnvil::Serialize::BsonParser::getValue(): Not a bool");
    }
}

HEADER_ONLY_INCLUDE
bool BsonManualLexer::isLastNull() const
{
    return lastNull;
}

HEADER_ONLY_INCLUDE
char BsonManualLexer::readDigits(char next)
{
    if (!std::isdigit(next))
    {
        error();
    }
    while (std::isdigit(next))
    {
        buffer.push_back(next);
        next = str.get();
    }
    return next;
}
HEADER_ONLY_INCLUDE
bool BsonManualLexer::readNumber(int next)
{
    bool isInteger = true;

    buffer.clear();

    if (next == '-' || next == '+')
    {
        buffer.push_back(next);
        next = str.get();
        if (next == EOF)
        {   error();
        }
    }
    if (next == '0')
    {
        buffer.push_back(next);
        next = str.get();
    }
    else
    {
        next = readDigits(next);
    }
    if (next == '.')
    {
        isInteger   = false;
        buffer.push_back(next);
        next        = str.get();
        if (next == EOF)
        {   error();
        }
        next        = readDigits(next);
    }
    if (next == 'e' || next == 'E')
    {
        buffer.push_back(next);
        next = str.get();
        if (next == EOF)
        {   error();
        }
        if (next == '-' || next == '+')
        {
            buffer.push_back(next);
            next = str.get();
            if (next == EOF)
            {   error();
            }
        }
        next = readDigits(next);
    }
    if (next != EOF)
    {
        str.unget();
    }

    return isInteger;
}

HEADER_ONLY_INCLUDE
void BsonManualLexer::checkFixed(char const* check, std::size_t size)
{
    buffer.resize(size);
    buffer[0] = check[0];
    str.read(&buffer[1], size - 1);
    if (std::strncmp(&buffer[0], check, size) != 0)
    {
        error();
    }
}

HEADER_ONLY_INCLUDE
void BsonManualLexer::error()
{
    throw std::runtime_error("ThorsAnvil::Serialize::BsonLexer: Invalid Character in Lexer");
}
