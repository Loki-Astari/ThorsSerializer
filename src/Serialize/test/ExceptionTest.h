#include "Traits.h"
#include <iostream>

class ThrowablePrint
{
    bool doThrow;
    public:
        int val;
        ThrowablePrint(bool doThrow, int val)
            : doThrow(doThrow)
            , val(val)
        {}
        friend std::ostream& operator<<(std::ostream& str, ThrowablePrint const& val)
        {
            if (val.doThrow)
            {
                throw std::runtime_error("Test Throw");
            }
            return str << val.val;
        }
        friend std::istream& operator>>(std::istream& str, ThrowablePrint& val)
        {
            if (val.doThrow)
            {
                throw std::runtime_error("Test Throw");
            }
            return str >> val.val;
        }
};

ThorsAnvil_MakeTraitCustom(ThrowablePrint);


