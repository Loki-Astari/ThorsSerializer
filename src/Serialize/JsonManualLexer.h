#ifndef THORS_ANVIL_SERIALIZER_JSON_MANUAL_LEXER_H
#define THORS_ANVIL_SERIALIZER_JSON_MANUAL_LEXER_H

#include "Serialize.h"
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
    bool                lastBool;
    bool                lastNull;
    public:
        JsonManualLexer(std::istream& str);
        int yylex();

        void        ignoreRawValue();
        std::string getRawString();
        std::string getString();
        bool        getLastBool() const;
        bool        isLastNull() const;
        template<typename T>
        T scan() const;
    private:
        void readTrue();
        void readFalse();
        void readNull();
        bool readNumber(int next);

        void checkFixed(char const* check, std::size_t size);
        char readDigits(char next);
        void error();
};

template<typename T>
inline T JsonManualLexer::scan() const
{
    char*   end;
    T value = scanValue<T>(&buffer[0], &end);
    if (buffer.size() == 0 || &buffer[0] + buffer.size() != end)
    {
        throw std::runtime_error("ThorsAnvil::Serialize::JsonParser: Not an integer");
    }
    return value;
}
    }
}

#endif
