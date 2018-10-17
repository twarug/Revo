#pragma once

// SFML
#include <SFML/Window/Event.hpp>

// Revo
#include <Revo/io/InputCode.hpp>

namespace rv
{

namespace io
{

enum InputStatus_e { Unkept = 0x0, Pressed = 0x1, Kept = 0x2, Released = 0x3 };

class EventManager
{
public:

    ///
    EventManager() = default;

    ///
    EventManager(const EventManager&) = delete;

    ///
    EventManager& operator = (const EventManager&) = delete;

    ///
    EventManager(EventManager&&) = delete;

    ///
    EventManager& operator = (EventManager&&) = delete;

    ///
    ~EventManager() = default;

    ///
    void ProcessEvent(const sf::Event& event)
    {
        if (event.type == sf::Event::MouseMoved)
        {
            m_mousePosition.x = event.mouseMove.x;
            m_mousePosition.y = event.mouseMove.y;
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            M_PressKey(event.key.code);
        }
        else if (event.type == sf::Event::KeyReleased)
        {
            M_ReleaseKey(event.key.code);
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            M_PressButton(event.mouseButton.button);
        }
        else if (event.type == sf::Event::MouseButtonReleased)
        {
            M_ReleaseButton(event.mouseButton.button);
        }
        else if (event.type == sf::Event::MouseWheelScrolled)
        {
            M_MoveWheel(event.mouseWheelScroll.wheel, event.mouseWheelScroll.delta);
        }
        else if (event.type == sf::Event::TextEntered)
        {
            m_enteredCharacter = event.text.unicode;
        }
    }

    ///
    void FinishLogic()
    {
        if (m_recentlyPressed.IsValid())
        {
            switch(m_recentlyPressed.GetType())
            {
                case InputDevice_e::Keyboard: m_keyboard[m_recentlyPressed] = InputStatus_e::Kept; break;
                case InputDevice_e::Mouse: m_mouse[m_recentlyPressed] = InputStatus_e::Kept; break;
                case InputDevice_e::Scroll: m_scroll[m_recentlyPressed] = InputStatus_e::Kept; break;
            }

            m_recentlyPressed = InputCode{};
        }

        if (m_recentlyReleased.IsValid())
        {
            switch(m_recentlyReleased.GetType())
            {
                case InputDevice_e::Keyboard: m_keyboard[m_recentlyReleased] = InputStatus_e::Unkept; break;
                case InputDevice_e::Mouse: m_mouse[m_recentlyReleased] = InputStatus_e::Unkept; break;
                case InputDevice_e::Scroll: m_scroll[m_recentlyReleased] = InputStatus_e::Unkept; break;
            }

            m_recentlyReleased = InputCode{};
        }

        m_enteredCharacter = 0;
    }

    ///
    void Press(const InputCode& code)
    {
        switch(code.GetType())
        {
            case InputDevice_e::Keyboard: M_PressKey(code); break;
            case InputDevice_e::Mouse: M_PressButton(code); break;
            case InputDevice_e::Scroll: M_MoveWheel(code % 2, code - 2); break;
        }
    }

    ///
    void Release(const InputCode& code)
    {
        switch(code.GetType())
        {
            case InputDevice_e::Keyboard: M_ReleaseKey(code); break;
            case InputDevice_e::Mouse: M_ReleaseButton(code); break;
            case InputDevice_e::Scroll: M_MoveWheel(code % 2, code - 2); break;
        }
    }

    ///
    InputStatus_e GetStatus(const InputCode& code) const
    {
        switch(code.GetType())
        {
            case InputDevice_e::Keyboard: return m_keyboard[code];
            case InputDevice_e::Mouse: return m_mouse[code];
            case InputDevice_e::Scroll: return m_scroll[code];
        }

        return InputStatus_e::Unkept;
    }

    ///
    bool CheckStatus(const InputCode& code, InputStatus_e status) const
    {
        return GetStatus(code) == status;
    }

    ///
    bool IsUnkept(const InputCode& code) const
    {
        return CheckStatus(code, InputStatus_e::Unkept);
    }

    ///
    bool IsPressed(const InputCode& code) const
    {
        return CheckStatus(code, InputStatus_e::Pressed);
    }

    ///
    bool IsKept(const InputCode& code) const
    {
        return CheckStatus(code, InputStatus_e::Kept);
    }

    ///
    bool IsReleased(const InputCode& code) const
    {
        return CheckStatus(code, InputStatus_e::Released);
    }

    ///
    InputCode GetRecentlyPressed() const
    {
        return m_recentlyPressed;
    }

    ///
    InputCode GetRecentlyReleased() const
    {
        return m_recentlyReleased;
    }

    ///
    bool IsAnyPressed() const
    {
        return m_recentlyPressed.IsValid();
    }

    ///
    bool IsAnyReleased() const
    {
        return m_recentlyReleased.IsValid();
    }

    ///
    bool IsTextEntered() const
    {
        return m_enteredCharacter != 0;
    }

    ///
    uint32_t GetEnteredCharacter() const
    {
        return m_enteredCharacter;
    }

    ///
    sf::Vector2i GetMousePosition() const
    {
        return m_mousePosition;
    }

private:

    ///
    void M_PressKey(int id)
    {
        if (m_keyboard[id] != InputStatus_e::Kept)
        {
            m_keyboard[id] = InputStatus_e::Pressed;
            m_recentlyPressed = static_cast<Keyboard::Code_e>(id);
        }
    }

    ///
    void M_ReleaseKey(int id)
    {
        if (m_keyboard[id] != InputStatus_e::Unkept)
        {
            m_keyboard[id] = InputStatus_e::Released;
            m_recentlyReleased = static_cast<Keyboard::Code_e>(id);
        }
    }

    ///
    void M_PressButton(int id)
    {
        if (m_mouse[id] != InputStatus_e::Kept)
        {
            m_mouse[id] = InputStatus_e::Pressed;
            m_recentlyPressed = static_cast<Mouse::Code_e>(id);
        }
    }

    ///
    void M_ReleaseButton(int id)
    {
        if (m_mouse[id] != InputStatus_e::Unkept)
        {
            m_mouse[id] = InputStatus_e::Released;
            m_recentlyReleased = static_cast<Mouse::Code_e>(id);
        }
    }

    ///
    void M_MoveWheel(int which, int delta)
    {
        if (which == sf::Mouse::Wheel::VerticalWheel)
        {
            if (delta < 0)
            {
                m_scroll[Scroll::Up] = InputStatus_e::Released;
                m_scroll[Scroll::Down] = InputStatus_e::Pressed;
                m_recentlyPressed = Scroll::Down;
                m_recentlyReleased = Scroll::Up;
            }
            else
            {
                m_scroll[Scroll::Up] = InputStatus_e::Pressed;
                m_scroll[Scroll::Down] = InputStatus_e::Released;
                m_recentlyPressed = Scroll::Up;
                m_recentlyReleased = Scroll::Down;
            }
        }
        else if (which == sf::Mouse::Wheel::HorizontalWheel)
        {
            if (delta < 0)
            {
                m_scroll[Scroll::Left] = InputStatus_e::Released;
                m_scroll[Scroll::Right] = InputStatus_e::Pressed;
                m_recentlyPressed = Scroll::Right;
                m_recentlyReleased = Scroll::Left;
            }
            else
            {
                m_scroll[Scroll::Left] = InputStatus_e::Pressed;
                m_scroll[Scroll::Right] = InputStatus_e::Released;
                m_recentlyPressed = Scroll::Left;
                m_recentlyReleased = Scroll::Right;
            }
        }
    }

    InputStatus_e m_keyboard[Keyboard::Count];
    InputStatus_e m_mouse[Mouse::Count];
    InputStatus_e m_scroll[Scroll::Count];

    InputCode m_recentlyPressed;
    InputCode m_recentlyReleased;

    uint32_t m_enteredCharacter;

    sf::Vector2i m_mousePosition;

};

}

}
