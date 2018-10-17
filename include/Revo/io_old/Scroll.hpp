#pragma once

// m2
#include <m2/Config.hpp>

namespace rv
{

namespace io
{

struct Scroll
{
    enum Code_e
    {
        Down  = 0,
        Right = 1,
        Up    = 2,
        Left  = 3,

        Count = 4
    };

};

}

}
