
#ifndef   THORS_ANVIL_BINARY_REP_BINARY_REP_H
#define   THORS_ANVIL_BINARY_REP_BINARY_REP_H

#include "BinaryFormat.h"
#include "IntBinRep.h"
#include "FltBinRep.h"

namespace ThorsAnvil
{
    namespace BinaryRep
    {

static_assert(sizeof(short)       * CHAR_BIT <= 16, "Binary interface assumes short       are not larger than 16 bits");
static_assert(sizeof(int)         * CHAR_BIT <= 32, "Binary interface assumes int         are not larger than 32 bits");
static_assert(sizeof(long)        * CHAR_BIT <= 64, "Binary interface assumes long        are not larger than 64 bits");
static_assert(sizeof(long long)   * CHAR_BIT <= 128,"Binary interface assumes long long   are not larger than 128 bits");

static_assert(sizeof(float)       * CHAR_BIT <= 32, "Binary interface assumes float       are not larger than 32  bits");
static_assert(sizeof(double)      * CHAR_BIT <= 64, "Binary interface assumes double      are not larger than 64  bits");
static_assert(sizeof(long double) * CHAR_BIT <= 128, "Binary interface assumes long double are not larger than 128 bits");

static_assert(static_cast<unsigned char>(true)  == '\x01',    "Binary interface assumes true has value of 1");
static_assert(static_cast<unsigned char>(false) == '\x00',    "Binary interface assumes false has value of 0");

    }
}

#endif

