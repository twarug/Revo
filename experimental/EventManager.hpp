#pragma once

// Revo
#include <Revo/System/Event.hpp>
#include <Revo/System/InputCode.hpp>

namespace rv
{
    ///
    enum class InputStatusType : int32_t
    {
        Unkept,
        Pressed,
        Kept,
        Released
    };

    ///
    class EventManager
    {
    public:

        ///
        EventManager();

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
        void ProcessEvent(const Event& event);

        ///
        void FinishLogic();

        ///
        void Press(Keyboard::CodeType code);

        ///
        void Press(Mouse::CodeType code);

        ///
        void Press(const InputCode& code);

        ///
        void Release(Keyboard::CodeType code);

        ///
        void Release(Mouse::CodeType code);

        ///
        void Release(const InputCode& code);

        ///
        InputStatusType GetStatus(Keyboard::CodeType code) const;

        ///
        InputStatusType GetStatus(Mouse::CodeType code) const;

        ///
        InputStatusType GetStatus(const InputCode& code) const;

        ///
        bool CheckStatus(Keyboard::CodeType code, InputStatusType status) const;

        ///
        bool CheckStatus(Mouse::CodeType code, InputStatusType status) const;

        ///
        bool CheckStatus(const InputCode& code, InputStatusType status) const;

        ///
        bool IsUnkept(Keyboard::CodeType code) const;

        ///
        bool IsUnkept(Mouse::CodeType code) const;

        ///
        bool IsUnkept(const InputCode& code) const;

        ///
        bool IsPressed(Keyboard::CodeType code) const;

        ///
        bool IsPressed(Mouse::CodeType code) const;

        ///
        bool IsPressed(const InputCode& code) const;

        ///
        bool IsKept(Keyboard::CodeType code) const;

        ///
        bool IsKept(Mouse::CodeType code) const;

        ///
        bool IsKept(const InputCode& code) const;

        ///
        bool IsReleased(Keyboard::CodeType code) const;

        ///
        bool IsReleased(Mouse::CodeType code) const;

        ///
        bool IsReleased(const InputCode& code) const;

        ///
        InputCode GetRecentlyPressed() const;

        ///
        InputCode GetRecentlyReleased() const;

        ///
        bool IsAnyPressed() const;

        ///
        bool IsAnyReleased() const;

        ///
        uint32_t GetEnteredCharacter() const;

    private:

        InputStatusType m_keyboard[Keyboard::Count] = {};
        InputStatusType m_mouse[Mouse::Count] = {};
        InputCode m_recentlyPressed;
        InputCode m_recentlyReleased;
        uint32_t m_enteredCharacter;
    };
}
