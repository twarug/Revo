#pragma once

// Revo
#include <Revo/Graphics/RenderTarget.hpp>
#include <Revo/ImGui/ImGuiContext.hpp>
#include <Revo/System/Clock.hpp>
#include <Revo/System/Context.hpp>
#include <Revo/System/Event.hpp>
#include <Revo/Math/Vector.hpp>

namespace rv
{
    ///
    class Window : public RenderTarget
    {
    public:

        using NativeHandle_t    = SDL_Window*;
        using GraphicsContext_t = SDL_GLContext;

        ///
        Window();

        ///
        Window(Window const&) = delete;

        ///
        Window& operator = (Window const&) = delete;

        ///
        Window(Window&&) = delete;

        ///
        Window& operator = (Window&&) = delete;

        ///
        ~Window();

        ///
        bool Create(Vec2u const& size, char const* name);

        ///
        void Show();

        ///
        void Hide();

        ///
        void Restore();

        ///
        void Close();

        ///
        bool PollEvent(Event& event);

        ///
        void SetFramerateLimit(uint32_t limit);

        ///
        uint32_t GetFramerateLimit() const;

        ///
        Duration_t GetDeltaDuration() const;

        ///
        float GetFramerate() const;

        ///
        void Bind() const;

        ///
        void Display();

        ///
        bool IsValid() const;

        ///
        bool IsOpen() const;

        ///
        NativeHandle_t GetNativeHandle() const;

        ///
        GraphicsContext_t GetGraphicsContext() const;

    private:

        ///
        void M_Destroy();

        ///
        void M_AdjustFramerate();

        NativeHandle_t m_window;
        GraphicsContext_t m_graphicsContext;
        Duration_t m_framerateLimit;
        Clock m_dtClock;
        bool m_isOpen;
    };
}
