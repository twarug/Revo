#pragma once

// Revo
#include <Revo/Graphics/RenderTarget.hpp>
#include <Revo/ImGui/ImGuiContext.hpp>
#include <Revo/System/Clock.hpp>
#include <Revo/System/Context.hpp>
#include <Revo/System/Event.hpp>

// glm
#include <glm/vec2.hpp>

namespace rv
{
    ///
    class Window : public RenderTarget
    {
    public:

        using NativeHandle_t = SDL_Window*;

        ///
        Window();

        ///
        Window(const Window&) = delete;

        ///
        Window& operator = (const Window&) = delete;

        ///
        Window(Window&&) = delete;

        ///
        Window& operator = (Window&&) = delete;

        ///
        ~Window();

        ///
        bool Create(const glm::uvec2& size, const char* name);

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
        bool PollEvent(SDL_Event& event); // TODO Make real event

        ///
        void SetFramerateLimit(uint32_t limit);

        ///
        uint32_t GetFramerateLimit() const;

        ///
        Duration_t GetDeltaDuration() const;

        ///
        float GetFramerate() const;

        ///
        virtual void Bind() const override;

        ///
        void Display();

        ///
        bool IsValid() const;

        ///
        bool IsOpen() const;

        ///
        NativeHandle_t GetNativeHandle() const;

    private:

        ///
        void M_Destroy();

        ///
        void M_AdjustFramerate();

        NativeHandle_t m_window;
        Duration_t m_framerateLimit;
        Clock m_clock;
        Clock m_dtClock;
        bool m_isOpen;
    };
}
