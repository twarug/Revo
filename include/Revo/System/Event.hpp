#pragma once

// Revo
#include <Revo/Config.hpp>

// C++
#include <cstdint>

namespace rv
{
    /// Types of events that can be dispatched
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

    /// Simple event class that holds event type and its data
    class Event
    {
    public:

        /// Default ctor that takes event type
        Event(EventType type = EventType::None);

        /// Defaulted copy-ctor
        Event(const Event&) = default;

        /// Defaulted copy-assign-op
        Event& operator = (const Event&) = default;

        /// Defaulted move-ctor
        Event(Event&&) noexcept = default;

        /// Defaulted move-assign-op
        Event& operator = (Event&&) noexcept = default;

        /// Defaulted destructor
        ~Event() = default;

        /// Returns type of currently stored event
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
