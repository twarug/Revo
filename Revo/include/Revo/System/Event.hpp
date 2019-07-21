#pragma once

// Revo
#include <Revo/System/Clock.hpp>
#include <Revo/System/Context.hpp> // TODO get rid off it

// C++
#include <cstdint>

namespace rv
{
    /// Types of events that can be dispatched
    enum class EventType : int32_t
    {
        None,

        WindowShown, // SDL_WINDOWEVENT_SHOWN
        WindowHidden, // SDL_WINDOWEVENT_HIDDEN
        WindowExposed, // SDL_WINDOWEVENT_EXPOSED
        WindowMoved, // SDL_WINDOWEVENT_MOVED
        WindowResized, // SDL_WINDOWEVENT_RESIZED
        WindowSizeChanged, // SDL_WINDOWEVENT_SIZE_CHANGED
        WindowMinimized, // SDL_WINDOWEVENT_MINIMIZED
        WindowMaximized, // SDL_WINDOWEVENT_MAXIMIZED
        WindowRestored, // SDL_WINDOWEVENT_RESTORED
        WindowMouseEntered, // SDL_WINDOWEVENT_ENTER
        WindowMouseLeft, // SDL_WINDOWEVENT_LEAVE
        WindowFocusGained, // SDL_WINDOWEVENT_FOCUS_GAINED
        WindowFocusLost, // SDL_WINDOWEVENT_FOCUS_LOST
        WindowClosed, // SDL_WINDOWEVENT_CLOSE
        WindowFocusOffered, // SDL_WINDOWEVENT_TAKE_FOCUS

        KeyPressed, // SDL_KEYDOWN
        KeyReleased, // SDL_KEYUP

        TextEntered, // SDL_TEXTINPUT

        MouseMoved, // SDL_MOUSEMOTION
        MosueButtonPressed, // SDL_MOUSEBUTTONDOWN
        MosueButtonReleased, // SDL_MOUSEBUTTONUP
        MouseScrollMoved, // SDL_MOUSEWHEEL

        AppClosed, // SDL_QUIT

        FileDropped, // SDL_DROPFILE
    };

    /// Simple trivial event class that holds event type and its data
    struct Event
    {
        EventType type;
        uint32_t timestamp;

        union
        {

        };

        SDL_Event sdlEvent; // TODO get rid off it
    };
}
