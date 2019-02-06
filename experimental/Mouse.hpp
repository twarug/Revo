#pragma once

// Revo
#include <Revo/Config.hpp>

// GLFW
#include <GLFW/glfw3.h>

namespace rv
{
    struct Mouse
    {
        enum CodeType : int32_t
        {
            Button1,
            Button2,
            Button3,
            Button4,
            Button5,
            Button6,
            Button7,
            Button8,
            Count,
            Unknown = -1,
            Left = Button1,
            Right = Button2,
            Middle = Button3,
        };

        ///
        static int32_t GetInternalCode(CodeType value);
    };
}
