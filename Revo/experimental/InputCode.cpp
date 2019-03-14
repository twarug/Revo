#include <Revo/System/InputCode.hpp>

namespace rv
{
    InputCode::InputCode(int32_t data)
        : m_data { data }
    {

    }

    InputCode::InputCode(Keyboard::CodeType code)
        : m_data { static_cast<int32_t>(InputDeviceType::Keyboard) | code }
    {

    }

    InputCode::InputCode(Mouse::CodeType code)
        : m_data { static_cast<int32_t>(InputDeviceType::Mouse) | code }
    {

    }

    InputDeviceType InputCode::GetType() const
    {
        return static_cast<InputDeviceType>(m_data & 0xFFFF0000);
    }

    int32_t InputCode::GetCode() const
    {
        return m_data & 0xFFFF;
    }

    int32_t InputCode::GetData() const
    {
        return m_data;
    }

    bool InputCode::IsValid() const
    {
        return m_data;
    }
}
