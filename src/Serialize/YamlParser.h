
#ifndef THORS_ANIVL_SERIALIZE_YAML_PARSER_H
#define THORS_ANIVL_SERIALIZE_YAML_PARSER_H

#include "../../config.h"
#ifdef HAVE_YAML

#include "Serialize.h"
#include <istream>
#include <yaml.h>

namespace ThorsAnvil
{
    namespace Serialize
    {

class YamlParser: public ParserInterface
{
    enum class State {Open, Map, Array};
    std::vector<std::pair<State, int>>  state;
    yaml_parser_t       parser;   
    yaml_event_t        event;
    bool                first;
    bool                error;

    std::string getString();
    void generateParsingException(std::function<bool ()> test, std::string const& msg);
    void generateParsingException(std::string const& msg);
    ParserToken parsingError();
    public:
        YamlParser(std::istream& input);
        virtual ~YamlParser();

        virtual ParserToken     getToken()              override;
        virtual std::string     getKey()                override;
        virtual void    getValue(bool& value)           override;
        virtual void    getValue(int& value)            override;
        virtual void    getValue(double& value)         override;
        virtual void    getValue(std::nullptr_t)        override;
        virtual void    getValue(std::string& value)    override;
};

    }
}

#endif
#endif

