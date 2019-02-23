#include "JsonManualLexer.h"
#include "JsonLexemes.h"
#include "UnicodeIterator.h"

#include <limits>
#include <cstring>

using namespace ThorsAnvil::Serialize;

JsonManualLexer::JsonManualLexer(std::istream& str)
    : str(str)
    , lastNull(false)
{}

int JsonManualLexer::yylex()
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

void JsonManualLexer::readTrue()
{
    checkFixed("true", 4);
}

void JsonManualLexer::readFalse()
{
    checkFixed("false", 5);
}

void JsonManualLexer::readNull()
{
    checkFixed("null", 4);
}

void JsonManualLexer::ignoreRawValue()
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

std::string JsonManualLexer::getRawString()
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

std::string JsonManualLexer::getString()
{
    return std::string(make_UnicodeWrapperIterator(std::istreambuf_iterator<char>(str)), make_EndUnicodeWrapperIterator(std::istreambuf_iterator<char>(str)));
}

bool JsonManualLexer::getLastBool() const
{
    if (lastToken == ThorsAnvil::Serialize::JSON_TRUE || lastToken == ThorsAnvil::Serialize::JSON_FALSE)
    {
        return lastBool;
    }
    else
    {
        throw std::runtime_error("ThorsAnvil::Serialize::JsonParser::getValue(): Not a bool");
    }
}

bool JsonManualLexer::isLastNull() const
{
    return lastNull;
}

char JsonManualLexer::readDigits(char next)
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
bool JsonManualLexer::readNumber(int next)
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

void JsonManualLexer::checkFixed(char const* check, std::size_t size)
{
    buffer.resize(size);
    buffer[0] = check[0];
    str.read(&buffer[1], size - 1);
    if (std::strncmp(&buffer[0], check, size) != 0)
    {
        error();
    }
}

void JsonManualLexer::error()
{
    throw std::runtime_error("ThorsAnvil::Serialize::JsonLexer: Invalid Character in Lexer");
}
