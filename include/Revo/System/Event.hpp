#pragma once

// Revo
#include <Revo/Config.hpp>

// C++
#include <cstdint>

namespace rv
{

    ///
    enum class EventType : int32_t
    {
        None,
        Closed,
        WindowMoved,
        WindowResized,
        FramebufferResized,
        GainedFocus,
        LostFocus,
        CursorMoved,
        CursorEntered,
        CursorLeft,
        ScrollMoved,
        KeyStateChanged,
        MouseButtonStateChanged,
        TextEntered,
        FilesDropped
    };

    ///
    class Event
    {
    public:

        ///
        Event(EventType type = EventType::None);

        ///
        Event(const Event&) = default;

        ///
        Event& operator = (const Event&) = default;

        ///
        Event(Event&&) = default;

        ///
        Event& operator = (Event&&) = default;

        ///
        ~Event() = default;

        ///
        EventType GetType() const;

        struct WindowMovedEvent { int xpos; int ypos; };
        struct WindowResizedEvent { int width; int height; };
        struct FramebufferResizedEvent { int width; int height; };
        struct CursorMovedEvent { double xpos; double ypos; };
        struct ScrollMovedEvent { double xoffset; double yoffset; };
        struct KeyStateChangedEvent { int key; int scancode; int action; int mods; };
        struct MouseButtonStateChangedEvent { int button; int action; int mods; };
        struct TextEnteredEvent { unsigned int codepoint; int mods; };
        struct FilesDroppedEvent { int count; const char** paths; };

        union
        {
            WindowMovedEvent windowPosition;
            WindowResizedEvent windowSize;
            FramebufferResizedEvent framebufferSize;
            CursorMovedEvent cursorPosition;
            ScrollMovedEvent scrollDelta;
            KeyStateChangedEvent keyState;
            MouseButtonStateChangedEvent mouseButtonState;
            TextEnteredEvent enteredText;
            FilesDroppedEvent droppedFiles;
        };

    private:

        EventType m_type;
    };

}
