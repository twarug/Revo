#include <Revo/System/EventManager.hpp>

namespace rv
{
    EventManager::EventManager()
        : m_keyboard {}
        , m_mouse {}
        , m_recentlyPressed {}
        , m_recentlyReleased {}
        , m_enteredCharacter {}
    {

    }

    void EventManager::FinishLogic()
    {
        if (m_recentlyPressed.IsValid())
        {
            switch(m_recentlyPressed.GetType())
            {
                case InputDeviceType::Keyboard:
                {
                    m_keyboard[m_recentlyPressed.GetCode()] = InputStatusType::Kept;
                }
                break;

                case InputDeviceType::Mouse:
                {
                    m_mouse[m_recentlyPressed.GetCode()] = InputStatusType::Kept;
                }
                break;

                case InputDeviceType::Pad:
                {
                    // TODO implement
                }
                break;
            }

            m_recentlyPressed = {};
        }

        if (m_recentlyReleased.IsValid())
        {
            switch(m_recentlyReleased.GetType())
            {
                case InputDeviceType::Keyboard:
                {
                    m_keyboard[m_recentlyReleased.GetCode()] = InputStatusType::Unkept;
                }
                break;

                case InputDeviceType::Mouse:
                {
                    m_mouse[m_recentlyReleased.GetCode()] = InputStatusType::Unkept;
                }
                break;

                case InputDeviceType::Pad:
                {
                    // TODO implement
                }
                break;
            }

            m_recentlyReleased = {};
        }

        m_enteredCharacter = 0;
    }

    // void EventManager::Press(const InputCode& code)
    // {
    //     switch(code.GetType())
    //     {
    //         case InputDeviceType::Keyboard: M_PressKey(code); break;
    //         case InputDeviceType::Mouse: M_PressButton(code); break;
    //     }
    // }
    //
    // void EventManager::Release(const InputCode& code)
    // {
    //     switch(code.GetType())
    //     {
    //         case InputDeviceType::Keyboard: M_ReleaseKey(code); break;
    //         case InputDeviceType::Mouse: M_ReleaseButton(code); break;
    //     }
    // }

    InputStatusType EventManager::GetStatus(const InputCode& code) const
    {
        switch(code.GetType())
        {
            case InputDeviceType::Keyboard:
            {
                return m_keyboard[code.GetCode()];
            }

            case InputDeviceType::Mouse:
            {
                return m_mouse[code.GetCode()];
            }

            case InputDeviceType::Pad:
            {
                // TODO implement
                return InputStatusType::Unkept;
            }

            default:
            {
                return InputStatusType::Unkept;
            }
        }
    }

    // bool EventManager::CheckStatus(const InputCode& code, InputStatusType status) const
    // {
    //     return GetStatus(code) == status;
    // }
    //
    // bool EventManager::IsUnkept(const InputCode& code) const
    // {
    //     return CheckStatus(code, InputStatusType::Unkept);
    // }
    //
    // bool EventManager::IsPressed(const InputCode& code) const
    // {
    //     return CheckStatus(code, InputStatusType::Pressed);
    // }
    //
    // bool EventManager::IsKept(const InputCode& code) const
    // {
    //     return CheckStatus(code, InputStatusType::Kept);
    // }
    //
    // bool EventManager::IsReleased(const InputCode& code) const
    // {
    //     return CheckStatus(code, InputStatusType::Released);
    // }

    InputCode EventManager::GetRecentlyPressed() const
    {
        return m_recentlyPressed;
    }

    InputCode EventManager::GetRecentlyReleased() const
    {
        return m_recentlyReleased;
    }

    bool EventManager::IsAnyPressed() const
    {
        return m_recentlyPressed.IsValid();
    }

    bool EventManager::IsAnyReleased() const
    {
        return m_recentlyReleased.IsValid();
    }

    uint32_t EventManager::GetEnteredCharacter() const
    {
        return m_enteredCharacter;
    }

    // void EventManager::M_PressKey(int id)
    // {
    //     if (m_keyboard[id] != InputStatusType::Kept)
    //     {
    //         m_keyboard[id] = InputStatusType::Pressed;
    //         m_recentlyPressed = static_cast<Keyboard::Code_e>(id);
    //     }
    // }
    //
    // void EventManager::M_ReleaseKey(int id)
    // {
    //     if (m_keyboard[id] != InputStatusType::Unkept)
    //     {
    //         m_keyboard[id] = InputStatusType::Released;
    //         m_recentlyReleased = static_cast<Keyboard::Code_e>(id);
    //     }
    // }
    //
    // void EventManager::M_PressButton(int id)
    // {
    //     if (m_mouse[id] != InputStatusType::Kept)
    //     {
    //         m_mouse[id] = InputStatusType::Pressed;
    //         m_recentlyPressed = static_cast<Mouse::Code_e>(id);
    //     }
    // }
    //
    // void EventManager::M_ReleaseButton(int id)
    // {
    //     if (m_mouse[id] != InputStatusType::Unkept)
    //     {
    //         m_mouse[id] = InputStatusType::Released;
    //         m_recentlyReleased = static_cast<Mouse::Code_e>(id);
    //     }
    // }
    //
    // void EventManager::M_MoveWheel(int which, int delta)
    // {
    //     if (which == Mouse::Wheel::VerticalWheel)
    //     {
    //         if (delta < 0)
    //         {
    //             m_scroll[Scroll::Up] = InputStatusType::Released;
    //             m_scroll[Scroll::Down] = InputStatusType::Pressed;
    //             m_recentlyPressed = Scroll::Down;
    //             m_recentlyReleased = Scroll::Up;
    //         }
    //         else
    //         {
    //             m_scroll[Scroll::Up] = InputStatusType::Pressed;
    //             m_scroll[Scroll::Down] = InputStatusType::Released;
    //             m_recentlyPressed = Scroll::Up;
    //             m_recentlyReleased = Scroll::Down;
    //         }
    //     }
    //     else if (which == Mouse::Wheel::HorizontalWheel)
    //     {
    //         if (delta < 0)
    //         {
    //             m_scroll[Scroll::Left] = InputStatusType::Released;
    //             m_scroll[Scroll::Right] = InputStatusType::Pressed;
    //             m_recentlyPressed = Scroll::Right;
    //             m_recentlyReleased = Scroll::Left;
    //         }
    //         else
    //         {
    //             m_scroll[Scroll::Left] = InputStatusType::Pressed;
    //             m_scroll[Scroll::Right] = InputStatusType::Released;
    //             m_recentlyPressed = Scroll::Left;
    //             m_recentlyReleased = Scroll::Right;
    //         }
    //     }
    // }
}
