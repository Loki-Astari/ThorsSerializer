#ifndef THORSANVIL_SERIALIZE_FORMAT_H
#define THORSANVIL_SERIALIZE_FORMAT_H

#if __cplusplus >= 202302L

#include <format>
#include <string>
#include <sstream>

#include "ThorSerialize/JsonThor.h"
#include "ThorSerialize/BsonThor.h"
#include "ThorSerialize/YamlThor.h"

namespace TA
{
    template<typename T>
    struct Ser
    {
        T const& value;
        Ser(T const& value)
            : value(value)
        {}
        Ser(Ser const&)         = default;
        Ser(Ser&&)              = default;
    };
};

template<typename T>
struct /*vera-disable*/ std::formatter<TA::Ser<T>>
{
    enum Format {Json, Bson, Yaml};
    Format                              form = Json;
    ThorsAnvil::Serialize::OutputType   type = ThorsAnvil::Serialize::OutputType::Stream;
    std::size_t                         size = 0;

    constexpr bool isDigit(char val)
    {
        return val >= '0' && val <= '9';
    }
    constexpr auto parse(std::format_parse_context& ctx)
    {
        auto loop = ctx.begin();
        if (*loop != '}') {
            switch (*loop)
            {
                case 'J':   form = Json; ++loop;    break;
                case 'B':   form = Bson; ++loop;    break;
                case 'Y':   form = Yaml; ++loop;    break;
                default:
            }
        }
        if (*loop != '}') {
            switch (*loop)
            {
                case '-':   type = ThorsAnvil::Serialize::OutputType::Stream;   ++loop; break;
                case '*':   type = ThorsAnvil::Serialize::OutputType::Config;   ++loop; break;
                default:
            }
        }
        for (;isDigit(*loop); ++loop) {
            size = size * 10 + (*loop - '0');
        }
        return loop;
    }

    auto format(const TA::Ser<T>& obj, std::format_context& ctx) const
    {
        ThorsAnvil::Serialize::PrinterConfig config{type, size};

        std::stringstream ser;
        switch (form)
        {
            case Json:  ser << ThorsAnvil::Serialize::jsonExporter(obj.value, config);break;
            case Bson:  ser << ThorsAnvil::Serialize::bsonExporter(obj.value, config);break;
            case Yaml:  ser << ThorsAnvil::Serialize::yamlExporter(obj.value, config);break;
        }

        std::string const& out = ser.str();
        return std::copy(std::begin(out), std::end(out), ctx.out());
    }
};

#endif

#endif
