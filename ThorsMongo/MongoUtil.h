#ifndef THORSANVIL_DB_MONGO_MONGO_UTIL_H
#define THORSANVIL_DB_MONGO_MONGO_UTIL_H

#include "ThorsMongoConfig.h"

#include "ThorSerialize/Traits.h"
#include "ThorSerialize/MongoUtility.h"

#include <cstdint>
#include <string>

namespace ThorsAnvil::DB::Mongo
{

using MessageId     = std::uint32_t;
using ObjectID      = ThorsAnvil::Serialize::MongoUtility::ObjectID;
using UTCDateTime   = ThorsAnvil::Serialize::MongoUtility::UTCDateTime;

namespace Internal
{
    MessageId& getMessageId();
    MessageId getNextMessageId();
}


enum class OP_MsgFlag: std::uint32_t
{
    empty           = 0,
    checksumPresent = 1 << 0,               // The message ends with 4 bytes containing a CRC-32C [1] checksum. See Checksum for details.
    moreToCome      = 1 << 1,               // Another message will follow this one without further action from the receiver.
                                            // The receiver MUST NOT send another message until receiving one with moreToCome set to 0 as
                                            // sends may block, causing deadlock. Requests with the moreToCome bit set will not receive a reply.
                                            // Replies will only have this set in response to requests with the exhaustAllowed bit set.
    exhaustAllowed  = 1 << 16,              // The client is prepared for multiple replies to this request using the moreToCome bit.
                                            // The server will never produce replies with the moreToCome bit set unless the request has this bit set.
};

inline std::int32_t operator&(OP_MsgFlag lhs, OP_MsgFlag rhs)
{
    return static_cast<std::uint32_t>(lhs) & static_cast<std::uint32_t>(rhs);
}
inline OP_MsgFlag operator|(OP_MsgFlag lhs, OP_MsgFlag rhs)
{
    return static_cast<OP_MsgFlag>(static_cast<std::uint32_t>(lhs) | static_cast<std::uint32_t>(rhs));
}
inline OP_MsgFlag operator~(OP_MsgFlag value)
{
    return static_cast<OP_MsgFlag>( ~ static_cast<std::uint32_t>(value));
}
inline std::int32_t operator&=(OP_MsgFlag& lhs, OP_MsgFlag rhs)
{
    std::uint32_t   result = lhs & rhs;
    lhs = static_cast<OP_MsgFlag>(result);
    return result;
}

enum class OpCode : std::uint32_t
{
    OP_NOOP         = 0,
    OP_COMPRESSED   = 2012,                 // Handled specially (see MessageHandler.cpp)
    OP_MSG          = 2013,                 // Send a message using the format introduced in MongoDB 3.6.
};

enum class Compression : std::uint8_t
{
    None            = 0,
    Snappy          = 1,
    ZLib            = 2,
    ZStd            = 4
};
inline std::int8_t operator&(Compression lhs, Compression rhs)
{
    return static_cast<std::uint8_t>(lhs) & static_cast<std::uint8_t>(rhs);
}
inline Compression operator|(Compression lhs, Compression rhs)
{
    return static_cast<Compression>(static_cast<std::uint8_t>(lhs) | static_cast<std::uint8_t>(rhs));
}
inline Compression operator~(Compression value)
{
    return static_cast<Compression>( ~ static_cast<std::uint8_t>(value));
}
inline std::int8_t operator&=(Compression& lhs, Compression rhs)
{
    std::uint8_t   result = lhs & rhs;
    lhs = static_cast<Compression>(result);
    return result;
}

struct OpMsgHeader
{
    // Message Header.
    std::uint32_t       messageSize;
    std::uint32_t       messageId;
    std::uint32_t       messageResponseId;
    OpCode              opCode;
};

struct OpMsgBlock
{
    // Message Header.
    std::uint32_t       messageSize;
    std::uint32_t       messageId;
    std::uint32_t       messageResponseId;
    OpCode              opCode;
    // OP_MSG body
    OP_MsgFlag          flags;
    std::uint8_t        kind;
    // BSON Object
};

struct OpCompressedBlock
{
    // Message Header.
    std::uint32_t       messageSize;
    std::uint32_t       messageId;
    std::uint32_t       messageResponseId;
    OpCode              opCode;
    // OP_COMPRESSED Message Body
    OpCode              originalOpCode;
    std::uint32_t       uncompressedSize;
    Compression         compression;
    // Compressed Data
};

struct CmdReplyBase
{
    double                      ok              = 0.0;
    std::string                 errmsg;
    std::string                 codeName;
    int                         code            = 0;

    bool isOk()                     const   {return ok != 0.0;}
    std::string getHRErrorMessage() const   {return errmsg;}

    operator bool()                 const   {return isOk();}
    friend std::ostream& operator<<(std::ostream& str, CmdReplyBase const& data)    {return str << data.getHRErrorMessage();}
};


static constexpr std::uint32_t  kSizeUInt32                     = 4;
static constexpr std::uint32_t  kSizeOpMsgHeaderSize            = 16;
static constexpr std::uint32_t  kSizeOpMsgBlock                 = 21;
static constexpr std::uint32_t  kSizeOpCompressedBlock          = 25;
static constexpr std::uint32_t  kSizeOpCompressedMessage        = 9;
static constexpr std::uint32_t  kSizeSmallestPossibleMessage    = 26;

}

ThorsAnvil_MakeTrait(ThorsAnvil::DB::Mongo::CmdReplyBase,               ok, errmsg, codeName, code);


#endif
