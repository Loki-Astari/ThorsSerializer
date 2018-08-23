#include "JsonManualLexer.h"
#include "JsonLexemes.h"

#include <limits>
#include <cstring>

using namespace ThorsAnvil::Serialize;

JsonManualLexer::JsonManualLexer(std::istream& str)
    : str(str)
{}

int JsonManualLexer::yylex()
{
    char    next;
    str >> next;
    switch (next)
    {
        case '{':
        case '}':
        case '[':
        case ']':
        case ',':
        case ':':
        {
            return next;
        }
        case 't':
        {
            readTrue();
            return ThorsAnvil::Serialize::JSON_TRUE;
        }
        case 'f':
        {
            readFalse();
            return ThorsAnvil::Serialize::JSON_FALSE;
        }
        case 'n':
        {
            readNull();
            return ThorsAnvil::Serialize::JSON_NULL;
        }
        case '"':
        {
            readString();
            return ThorsAnvil::Serialize::JSON_STRING;
        }
        default:
        {
            return readNumber(next)
                ? ThorsAnvil::Serialize::JSON_INTEGER
                : ThorsAnvil::Serialize::JSON_FLOAT;
        }
    }
};

char const* JsonManualLexer::yyText()
{
    return &buffer[0];
}

int JsonManualLexer::yyLeng()
{
    return buffer.size();
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

void JsonManualLexer::readString()
{
    buffer.clear();
    buffer.push_back('"');

    char last = ' ';
    int next = str.get();;
    while (next != EOF && !(next == '"' && last != '\\'))
    {
        if (next < 0x20)
        {
            error();
        }
        buffer.push_back(next);
        last = next;
        next = str.get();
    }
    if (next == EOF)
    {
        error();
    }
    buffer.push_back('"');
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

#if 0
DIGIT           [0-9]
DIGIT1          [1-9]
INTNUM          {DIGIT1}{DIGIT}*
FRACT           "."{DIGIT}+
FLOAT           ({INTNUM}|0){FRACT}?
EXP             [eE][+-]?{DIGIT}+
NUMBER          -?{FLOAT}{EXP}?

UNICODE         \\u[A-Fa-f0-9]{4}
ESCAPECHAR      \\["\\/bfnrt]
CHAR            [^"\\\b\n\f\r\t]|{ESCAPECHAR}|{UNICODE}
STRING          \"{CHAR}*\"

VALUE_STRING    {STRING}
VALUE_INTEGER   {INTNUM}
VALUE_FLOAT     {NUMBER}

#endif
