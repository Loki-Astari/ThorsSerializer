
#ifndef THORS_ANVIL_SERIALIZATION_JSON_PARSER_H
#define THORS_ANVIL_SERIALIZATION_JSON_PARSER_H

#include "Serialize.h"
#include "JsonLexer.h"
#include <string>

namespace ThorsAnvil
{
    namespace Serialization
    {

class JsonParser: public ParserInterface
{
    enum State          {Error, Init, OpenM, Key, Colon, ValueM, CommaM, CloseM, OpenA, ValueA, CommaA, CloseA, Done};
    class PrintState
    {
        JsonParser&     p;
        public:
            PrintState(JsonParser& p):p(p)
            {
                std::cout << "Get Token: ST currentState(" << p.currentState << ")  currentEnd(" << p.currentEnd << ")\n";
            }
            ~PrintState()
            {
                std::cout << "Get Token: EN currentState(" << p.currentState << ")  currentEnd(" << p.currentEnd << ")\n";
                std::copy(std::begin(p.parrentState), std::end(p.parrentState), std::ostream_iterator<State>(std::cout, "  "));
                std::cout << "\n\n";
            }
    };
    JsonLexerFlexLexer  lexer;
    std::vector<State>  parrentState;
    State               currentEnd;
    State               currentState;
    bool                started;
        std::string getString();
    public:
        JsonParser(std::istream& stream);
        virtual ParserToken getToken();
        virtual std::string getKey();
        virtual void    getValue(bool& value);
        virtual void    getValue(int& value);
        virtual void    getValue(double& value);
        virtual void    getValue(std::nullptr_t);
        virtual void    getValue(std::string& value);
};
    }
}

#endif

