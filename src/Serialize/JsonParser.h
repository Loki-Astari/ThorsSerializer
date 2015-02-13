
#ifndef THORS_ANVIL_SERIALIZE_JSON_PARSER_H
#define THORS_ANVIL_SERIALIZE_JSON_PARSER_H

#include "Serialize.h"
#include "JsonLexer.h"
#include <istream>
#include <string>
#include <vector>

namespace ThorsAnvil
{
    namespace Serialize
    {

class JsonParser: public ParserInterface
{
    enum State          {Error, Init, OpenM, Key, Colon, ValueM, CommaM, CloseM, OpenA, ValueA, CommaA, CloseA, Done};

    JsonLexerFlexLexer  lexer;
    std::vector<State>  parrentState;
    State               currentEnd;
    State               currentState;
    bool                started;

    std::string getString();
    public:
        JsonParser(std::istream& stream);
        virtual ParserToken getToken()      override;
        virtual std::string getKey()        override;
        virtual void    getValue(bool& value)           override;
        virtual void    getValue(int& value)            override;
        virtual void    getValue(double& value)         override;
        virtual void    getValue(std::nullptr_t)        override;
        virtual void    getValue(char*& value)          override;
        virtual void    getValue(std::string& value)    override;
};
    }
}

#endif

