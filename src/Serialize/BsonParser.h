#ifndef THORS_ANVIL_SERIALIZE_BSON_PARSER_H
#define THORS_ANVIL_SERIALIZE_BSON_PARSER_H
/*
 * BsonParser<T>
 *      This is used in conjunction with BsonPrinter<T>
 *
 *      Together these provide an implementation of:
 *          the ParserInterface for type T
 *          and PrinterInterface for type T
 *
 *      These Interfaces are used by Serializer and DeSerializer (see Serialize.h)
 *
 *      It uses ThorsAnvil::Serialize::Traits<T> to know what objects to pull from the stream.
 *      For arrays order is important.
 *      For Objects the order of elements is not important. It looks up the key in the Traits<T>
 *      information to understand which member is being de-serialized but unspecified elements
 *      will not cause an error.
 */

#include "Serialize.h"
#include "BsonUtil.h"
#include "ThorsIOUtil/Utility.h"
#include <GitUtility/ieee754_types.h>
#include <istream>
#include <string>
#include <vector>

namespace ThorsAnvil
{
    namespace Serialize
    {

class BsonParser: public ParserInterface
{
    std::vector<BsonContainer>  currentContainer;
    std::vector<std::size_t>    dataLeft;
    std::vector<std::size_t>    dataSize;
    ParserToken                 nextToken;
    std::string                 nextKey;
    char                        nextType;

    ValueType                       currentValue;
    // All these should be in a union or something like that.
    std::int32_t                    valueInt32;
    std::int64_t                    valueInt64;
    IEEE_754::_2008::Binary<64>     valueFloat64;
#if 0
    ieee128 not supported consistently
    IEEE_754::_2008::Binary<128>    valueFloat128;
#endif
    bool                            valueBool;
    std::string                     valueString;
    std::string                     valueBinary;

    public:
        BsonParser(std::istream& stream, ParserConfig config = ParserConfig{});
        virtual ParserToken getNextToken()                      override;
        virtual std::string getKey()                            override;

        virtual void    ignoreDataValue()                       override    {}

        virtual void    getValue(short int& value)              override    {value = returnIntValue<MaxTemplate<4, sizeof(short int)>::value, short int>();}
        virtual void    getValue(int& value)                    override    {value = returnIntValue<sizeof(int), int>();}
        virtual void    getValue(long int& value)               override    {value = returnIntValue<sizeof(long int), long int>();}
        virtual void    getValue(long long int& value)          override    {value = returnIntValue<sizeof(long long int), long long int>();}

        virtual void    getValue(unsigned short int& value)     override    {value = returnIntValue<MaxTemplate<4, sizeof(unsigned short int)>::value, unsigned short int>();}
        virtual void    getValue(unsigned int& value)           override    {value = returnIntValue<sizeof(unsigned int), unsigned int>();}
        virtual void    getValue(unsigned long int& value)      override    {value = returnIntValue<sizeof(unsigned long int), unsigned long int>();}
        virtual void    getValue(unsigned long long int& value) override    {value = returnIntValue<sizeof(unsigned long long int), unsigned long long int>();}

        virtual void    getValue(float& value)                  override    {value = returnFloatValue<8, float>();}
        virtual void    getValue(double& value)                 override    {value = returnFloatValue<8, double>();}
        virtual void    getValue(long double& value)            override    {value = returnFloatValue<8, long double>();}

        virtual void    getValue(bool& value)                   override    {if (currentValue != ValueType::Bool)      {badType();}value = valueBool;}

        virtual void    getValue(std::string& value)            override    {if (currentValue != ValueType::String)    {badType();}value = valueString;}

        virtual bool    isValueNull()                           override    {return (currentValue == ValueType::Null);}

        virtual std::string getRawValue()                       override;

    private:
        bool isEndOfContainer();

        template<std::size_t size, typename Int>
        Int readSize(bool);

        template<std::size_t Size, typename Int>
        Int returnIntValue();
        template<std::size_t Size, typename Float>
        Float returnFloatValue();

        void readKey();
        void readValue(bool useValue);

        template<std::size_t Size, typename Int>
        Int readInt(bool);

        template<std::size_t Size>
        IEEE_754::_2008::Binary<Size * 8> readFloat(bool);

        bool readBool(bool);
        std::string readString(bool);
        void readNull(bool);
        std::string readBinary(bool);

        [[noreturn]]
        void badType()                                      {throw std::runtime_error(
                                                                    ThorsAnvil::Utility::buildErrorMessage("ThorsAnvil::Serialize::BsonParser", "badType"
                                                                                                          "Trying to read a type that we can can't convert.")
                                                                                                          );
                                                            }
};
    }
}

#if defined(HEADER_ONLY) && HEADER_ONLY == 1
#include "BsonParser.source"
#endif

#endif
