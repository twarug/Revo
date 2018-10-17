#pragma once

// Revo
#include <Revo/io/Keyboard.hpp>
#include <Revo/io/Mouse.hpp>
#include <Revo/io/Scroll.hpp>

namespace rv
{

namespace io
{

enum InputDevice_e { Keyboard = 0x10000, Mouse = 0x20000, Scroll = 0x30000 };

class InputCode
{
public:

    ///
    constexpr InputCode()
        : m_data{ 0 }
    {
        
    }

    ///
    constexpr InputCode(const InputCode&) = default;

    ///
    InputCode& operator = (const InputCode&) = default;

    ///
    constexpr InputCode(InputCode&&) = default;

    ///
    InputCode& operator = (InputCode&&) = default;

    ///
    ~InputCode() = default;

    ///
    constexpr InputCode(Keyboard::Code_e code)
        : m_data{ InputDevice_e::Keyboard | code }
    {

    }

    ///
    constexpr InputCode(Mouse::Code_e code)
        : m_data{ InputDevice_e::Mouse | code }
    {

    }

    ///
    constexpr InputCode(Scroll::Code_e code)
        : m_data{ InputDevice_e::Scroll | code }
    {

    }

    ///
    explicit constexpr InputCode(int data)
        : m_data{ data }
    {

    }

    ///
    constexpr InputDevice_e GetType() const
    {
        return static_cast<InputDevice_e>(m_data & 0xFF0000);
    }

    ///
    constexpr int GetID() const
    {
        return m_data & 0xFFFF;
    }

    ///
    constexpr operator int () const
    {
        return GetID();
    }

    ///
    constexpr int GetData() const
    {
        return m_data;
    }

    ///
    constexpr bool IsValid() const
    {
        return GetData() != 0;
    }

private:

    int m_data;

};

}

}
