#include "JsonParser.h"
#include "JsonLexemes.h"
#include "UnicodeIterator.h"
#include <map>
#include <cstdlib>
#include <cstring>

// enum class ParserToken {Error, MapStart, MapEnd, ArrayStart, ArrayEnd, Key, Value};
using namespace ThorsAnvil::Serialize;
using ParserToken = ParserInterface::ParserToken;

JsonParser::JsonParser(std::istream& stream)
    : ParserInterface(stream)
    , lexer(&stream)
    , currentEnd(Done)
    , currentState(Init)
    , started(false)
{}

ParserToken JsonParser::getNextToken()
{
    /* Handle States were we are not going to read any more */
    if (!started)
    {
        started = true;
        return ParserToken::DocStart;
    }
    if (currentState == Done)
    {
        currentState = Error;
        return ParserToken::DocEnd;
    }
    if (currentState == Error)
    {
        return ParserToken::Error;
    }

    // Convert Lexer tokens into smaller range 0-12
    static std::map<int, int>   tokenIndex  =
    {
        {0,                                     0},
        {'{',                                   1},
        {'}',                                   2},
        {'[',                                   3},
        {']',                                   4},
        {',',                                   5},
        {':',                                   6},
        {ThorsAnvil::Serialize::JSON_TRUE,      7},
        {ThorsAnvil::Serialize::JSON_FALSE,     8},
        {ThorsAnvil::Serialize::JSON_NULL,      9},
        {ThorsAnvil::Serialize::JSON_STRING,    10},
        {ThorsAnvil::Serialize::JSON_INTEGER,   11},
        {ThorsAnvil::Serialize::JSON_FLOAT,     12}
    };
    // State transition table;
    static State   stateTable[][13]   =
    {
        /* Token   ->   0,      1,      2,      3,      4,      5,      6,      7,      8,      9,      10,     11,     12 */
        /* Error */ {   Error,  Error,  Error,  Error,  Error,  Error,  Error,  Error,  Error,  Error,  Error,  Error,  Error   },
        /* Init  */ {   Error,  OpenM,  Error,  OpenA,  Error,  Error,  Error,  ValueD, ValueD, ValueD, ValueD, ValueD, ValueD  },
        /* OpenM */ {   Error,  Error,  CloseM, Error,  Error,  Error,  Error,  Error,  Error,  Error,  Key,    Error,  Error   },
        /* Key   */ {   Error,  Error,  Error,  Error,  Error,  Error,  Colon,  Error,  Error,  Error,  Error,  Error,  Error   },
        /* Colon */ {   Error,  OpenM,  Error,  OpenA,  Error,  Error,  Error,  ValueM, ValueM, ValueM, ValueM, ValueM, ValueM  },
        /* ValueM*/ {   Error,  Error,  CloseM, Error,  Error,  CommaM, Error,  Error,  Error,  Error,  Error,  Error,  Error   },
        /* CommaM*/ {   Error,  Error,  Error,  Error,  Error,  Error,  Error,  Error,  Error,  Error,  Key,    Error,  Error   },
        /* CloseM*/ {   Error,  Error,  Error,  Error,  Error,  Error,  Error,  Error,  Error,  Error,  Error,  Error,  Error   },
        /* OpenA */ {   Error,  OpenM,  Error,  OpenA,  CloseA, Error,  Error,  ValueA, ValueA, ValueA, ValueA, ValueA, ValueA  },
        /* ValueA*/ {   Error,  Error,  Error,  Error,  CloseA, CommaA, Error,  Error,  Error,  Error,  Error,  Error,  Error   },
        /* CommaA*/ {   Error,  OpenM,  Error,  OpenA,  Error,  Error,  Error,  ValueA, ValueA, ValueA, ValueA, ValueA, ValueA  },
        /* CloseA*/ {   Error,  Error,  Error,  Error,  Error,  Error,  Error,  Error,  Error,  Error,  Error,  Error,  Error   },
        /* ValueD*/ {   Error,  Error,  Error,  Error,  Error,  Error,  Error,  Error,  Error,  Error,  Error,  Error,  Error   },
        /* Done  */ {   Error,  Error,  Error,  Error,  Error,  Error,  Error,  Error,  Error,  Error,  Error,  Error,  Error   },
    };

    // Read the next token and update the state.
    int token   = lexer.yylex();
    int index   = tokenIndex[token];

    currentState    = stateTable[currentState][index];
    switch (currentState)
    {
        // These states should be impossible to get too
        case Init:      throw std::runtime_error("ThorsAnvil::Serialize::JsonParser: Got into Init State");
        case Done:      throw std::runtime_error("ThorsAnvil::Serialize::JsonParser: Got into Done State");
        // The states that we actually want to return
        case Error:     return ParserToken::Error;
        case Key:       return ParserToken::Key;
        case ValueM:    return ParserToken::Value;
        case ValueA:    return ParserToken::Value;
        case ValueD:    currentState = Done; return ParserToken::Value;
        // Punctuation.
        // Parse it but it is not the actual result
        // So try and get the next token.
        case Colon:     return getNextToken();
        case CommaM:    return getNextToken();
        case CommaA:    return getNextToken();
        // We are going into a containing object.

        // Push the state we want when the containing
        // object is complete then set the state we will
        // need if we open another container.
        case OpenM:
            parrentState.push_back(currentEnd);
            currentEnd  = ValueM;
            return ParserToken::MapStart;
        case OpenA:
            parrentState.push_back(currentEnd);
            currentEnd  = ValueA;
            return ParserToken::ArrayStart;

        // We are leaving the containing object.
        // Pop the state we previously saved.
        case CloseM:
            currentEnd  = currentState    = parrentState.back();
            parrentState.pop_back();
            return ParserToken::MapEnd;
        case CloseA:
            currentEnd  = currentState    = parrentState.back();
            parrentState.pop_back();
            return ParserToken::ArrayEnd;

        // Anything else just break.
        default:
            break;
    }
    // If we hit anything else there was a serious problem in the
    // parser itself.
    throw std::runtime_error("ThorsAnvil::Serialize::JsonParser: Reached an Unnamed State");
}

std::string JsonParser::getString()
{
    if (lexer.YYLeng() < 2 || lexer.YYText()[0] != '"' || lexer.YYText()[lexer.YYLeng()-1] != '"')
    {
        throw std::runtime_error("ThorsAnvil::Serialize::JsonParser: Not a String value");
    }
    // Remember to drop the quotes
    return std::string(make_UnicodeWrapperIterator(lexer.YYText() + 1),
                       make_UnicodeWrapperIterator(lexer.YYText() + lexer.YYLeng() - 1));
}

std::string JsonParser::getKey()
{
    return getString();
}

template<typename T>
inline T JsonParser::scan()
{
    char*   end;
    T value = scanValue<T>(lexer.YYText(), &end);
    if (lexer.YYText() + lexer.YYLeng() != end)
    {
        throw std::runtime_error("ThorsAnvil::Serialize::JsonParser: Not an integer");
    }
    return value;
}

void JsonParser::getValue(short& value)                         {value = scan<short>();}
void JsonParser::getValue(int& value)                           {value = scan<int>();}
void JsonParser::getValue(long& value)                          {value = scan<long>();}
void JsonParser::getValue(long long& value)                     {value = scan<long long>();}

void JsonParser::getValue(unsigned short& value)                {value = scan<unsigned short>();}
void JsonParser::getValue(unsigned int& value)                  {value = scan<unsigned int>();}
void JsonParser::getValue(unsigned long& value)                 {value = scan<unsigned long>();}
void JsonParser::getValue(unsigned long long& value)            {value = scan<unsigned long long>();}

void JsonParser::getValue(float& value)                         {value = scan<float>();}
void JsonParser::getValue(double& value)                        {value = scan<double>();}
void JsonParser::getValue(long double& value)                   {value = scan<long double>();}

void JsonParser::getValue(bool& value)
{
    if (lexer.YYLeng() == 4 && std::strncmp(lexer.YYText(), "true", 4) == 0)
    {
        value = true;
    }
    else if (lexer.YYLeng() == 5 && std::strncmp(lexer.YYText(), "false", 5) == 0)
    {
        value = false;
    }
    else
    {
        throw std::runtime_error("ThorsAnvil::Serialize::JsonParser: Not a bool");
    }
}

void JsonParser::getValue(std::string& value)
{
    value = getString();
}
