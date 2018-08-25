#ifndef THORS_ANVIL_SERIALIZER_JSON_MANUAL_LEXER_H
#define THORS_ANVIL_SERIALIZER_JSON_MANUAL_LEXER_H

#include <istream>

namespace ThorsAnvil
{
    namespace Serialize
    {

class JsonManualLexer
{
    std::istream&       str;
    std::string         buffer;
    int                 lastToken;
    public:
        JsonManualLexer(std::istream& str);
        int yylex();

        char const* yyText();
        int         yyLeng();
        std::string getRawString();
        std::string getString();
    private:
        void readTrue();
        void readFalse();
        void readNull();
        bool readNumber(int next);

        void checkFixed(char const* check, std::size_t size);
        char readDigits(char next);
        void error();
};

    }
}

#endif
