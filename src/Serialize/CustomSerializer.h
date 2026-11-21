#ifndef THORSANVIL_SERIALIZE_CUSTOM_SERIALIZER_H
#define THORSANVIL_SERIALIZE_CUSTOM_SERIALIZER_H

#include "Serialize.h"

namespace ThorsAnvil::Serialize
{

class CustomSerializer
{
    struct IdWriter
    {
        ThorsAnvil::Serialize::Serializer&          parent;
        ThorsAnvil::Serialize::PrinterInterface&    printer;
        template<typename T>
        void operator()(T const& val) const
        {
            using Base = std::remove_cvref_t<T>;
            using Traits = ThorsAnvil::Serialize::Traits<Base>;
            Base const& val1 =  std::any_cast<Base>(val);
            ThorsAnvil::Serialize::SerializerForBlock<Traits::type, Base> serializer(parent, printer, val1);
            serializer.printMembers();
        }
    };
    struct IdSizer
    {
        ThorsAnvil::Serialize::PrinterInterface&    printer;
        template<typename T>
        std::size_t operator()(T const& val) const
        {
            using Base = std::remove_cvref_t<T>;
            using Traits = ThorsAnvil::Serialize::Traits<Base>;
            return Traits::getPrintSize(printer, val, true);
        }
    };
    public:
        template<typename T>
        static std::size_t getPrintSize(ThorsAnvil::Serialize::PrinterInterface& printer, T const& object)
        {
            return std::visit(IdSizer{printer}, object);
        }
        template<typename T>
        static void writeCustom(ThorsAnvil::Serialize::Serializer& parent, ThorsAnvil::Serialize::PrinterInterface& printer, T const& object)
        {
            std::visit(IdWriter{parent, printer}, object);
        }
};

}

#endif
