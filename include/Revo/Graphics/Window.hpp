#pragma once

// Revo
#include <Revo/Graphics/Context.hpp>
#include <Revo/Graphics/RenderTarget.hpp>
#include <Revo/ImGui/ImGuiContext.hpp>
#include <Revo/System/Clock.hpp>
#include <Revo/System/Event.hpp>

// glm
#include <glm/vec2.hpp>

namespace rv
{
    ///
    class Window : public RenderTarget
    {
    public:

        // using NativeHandle_t = GLFWwindow*;
        using NativeHandle_t = SDL_Window*;
        using GfxContext_t   = SDL_GLContext;

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
        bool Create(const glm::uvec2& size, const char* name, bool makeContextCurrent);

        ///
        void Show();

        ///
        void Hide();

        ///
        void Restore();

        ///
        void Iconify();

        ///
        void Close();

        ///
        // Event PollEvent();
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
        virtual void Bind() override;

        ///
        void Display();

        ///
        bool IsValid() const;

        ///
        bool IsOpen() const;

        ///
        GfxContext_t GetGfxContext() const;

        ///
        NativeHandle_t GetNativeHandle() const;

    private:

        ///
        // static Window* M_This(NativeHandle_t window);

        ///
        void M_Destroy();

        ///
        // void M_RegisterCallbacks();

        ///
        void M_AdjustFramerate();

        GfxContext_t m_gfxContext;
        NativeHandle_t m_window;
        Duration_t m_framerateLimit;
        Clock m_clock;
        Clock m_dtClock;
        // Event m_event;
        bool m_isOpen;
    };
}
