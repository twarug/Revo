#pragma once

// Revo
#include <Revo/System/Keyboard.hpp>
#include <Revo/System/Mouse.hpp>

namespace rv
{
    ///
    enum class InputDeviceType : int32_t
    {
        Keyboard = 0x00010000,
        Mouse    = 0x00020000,
        Pad      = 0x00030000
    };

    ///
    class InputCode
    {
    public:

        ///
        InputCode() = default;

        ///
        explicit InputCode(int32_t data);

        ///
        InputCode(Keyboard::CodeType code);

        ///
        InputCode(Mouse::CodeType code);

        ///
        InputCode(const InputCode&) = default;

        ///
        InputCode& operator = (const InputCode&) = default;

        ///
        InputCode(InputCode&&) = default;

        ///
        InputCode& operator = (InputCode&&) = default;

        ///
        ~InputCode() = default;

        ///
        InputDeviceType GetType() const;

        ///
        int32_t GetCode() const;

        ///
        int32_t GetData() const;

        ///
        bool IsValid() const;

    private:

        int32_t m_data = 0;
    };
}
