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
#include "GitUtility/ieee754_types.h"
#include <istream>
#include <string>
#include <vector>

namespace ThorsAnvil
{
    namespace Serialize
    {

enum class BsonContainer  {Map, Array};

class BsonParser: public ParserInterface
{
    enum ValueType {Int32, Int64, Double64, Double128, Bool, String, Null, Binary};

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

        virtual void    ignoreDataValue()                       override;

        virtual void    getValue(short int& value)              override;
        virtual void    getValue(int& value)                    override;
        virtual void    getValue(long int& value)               override;
        virtual void    getValue(long long int& value)          override;

        virtual void    getValue(unsigned short int& value)     override;
        virtual void    getValue(unsigned int& value)           override;
        virtual void    getValue(unsigned long int& value)      override;
        virtual void    getValue(unsigned long long int& value) override;

        virtual void    getValue(float& value)                  override;
        virtual void    getValue(double& value)                 override;
        virtual void    getValue(long double& value)            override;

        virtual void    getValue(bool& value)                   override;

        virtual void    getValue(std::string& value)            override;

        virtual bool    isValueNull()                           override;

        virtual std::string getRawValue()                       override;
    private:

        template<typename Int>
        Int returnIntValue();
        template<typename Float>
        Float returnFloatValue();

        void readKey();
        void readValue(bool useValue);

        template<std::size_t Size, typename Int>
        Int readInt(bool);

        template<std::size_t Size>
        IEEE_754::_2008::Binary<Size * 8> readFloat(bool);

        void readBool(bool);
        void readString(bool);
        void readNull(bool);
        void readBinary(bool);

        [[noreturn]]
        void badType();
};
    }
}

#if defined(HEADER_ONLY) && HEADER_ONLY == 1
#include "BsonParser.source"
#endif

#endif
