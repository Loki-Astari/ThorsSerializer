
#ifndef THORS_ANVIL_SERIALIZE_BINARY_PARSER_H
#define THORS_ANVIL_SERIALIZE_BINARY_PARSER_H

#include "../../config.h"
#ifdef NETWORK_BYTE_ORDER

#include "Serialize.h"
#include <istream>
#include <string>

namespace ThorsAnvil
{
    namespace Serialize
    {

template<typename T>
class BinaryParser: public ParserInterface
{
    enum State          {Error}

    bool                started;

    std::string getString();
    public:
        BinaryParser(std::istream& stream);
        virtual ParserToken getNextToken()              override;
        virtual std::string getKey()                    override;
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
#endif

