#pragma once

// Revo
#include <Revo/Config.hpp>

// GLFW
#include <GLFW/glfw3.h>

namespace rv
{
    ///
    struct Keyboard
    {
        ///
        enum CodeType : int32_t
        {
            A,
            B,
            C,
            D,
            E,
            F,
            G,
            H,
            I,
            J,
            K,
            L,
            M,
            N,
            O,
            P,
            Q,
            R,
            S,
            T,
            U,
            V,
            W,
            X,
            Y,
            Z,
            Num0,
            Num1,
            Num2,
            Num3,
            Num4,
            Num5,
            Num6,
            Num7,
            Num8,
            Num9,
            LControl,
            LShift,
            LAlt,
            LSystem,
            RControl,
            RShift,
            RAlt,
            RSystem,
            LBracket,
            RBracket,
            Escape,
            Tilde,
            Tab,
            Space,
            Comma,
            Period,
            Slash,
            Semicolon,
            Quote,
            Backslash,
            Dash,
            Equal,
            Backspace,
            Return,
            Menu,
            Insert,
            Delete,
            Home,
            End,
            PageUp,
            PageDown,
            PrintScreen,
            Pause,
            Left,
            Right,
            Up,
            Down,
            KpNum0,
            KpNum1,
            KpNum2,
            KpNum3,
            KpNum4,
            KpNum5,
            KpNum6,
            KpNum7,
            KpNum8,
            KpNum9,
            KpDecimal,
            KpAdd,
            KpSubtract,
            KpMultiply,
            KpDivide,
            KpEqual,
            KpEnter,
            F1,
            F2,
            F3,
            F4,
            F5,
            F6,
            F7,
            F8,
            F9,
            F10,
            F11,
            F12,
            F13,
            F14,
            F15,
            F16,
            F17,
            F18,
            F19,
            F20,
            F21,
            F22,
            F23,
            F24,
            F25,
            Count,
            Unknown = -1
        };

        /// Returns implementation defined value of code
        static int32_t GetKeyInternal(CodeType code);

        /// Returns code of implementation defined value
        static CodeType GetKeyFromInternal(int32_t internal);

        /// Returns C-string name of key from code
        static const char* GetKeyName(CodeType code);

        /// Returns C-string name of key from internal
        static const char* GetKeyName(int32_t internal);
    };
}
