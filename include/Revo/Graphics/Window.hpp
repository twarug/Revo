#pragma once

// Revo
#include <Revo/System/Clock.hpp>
#include <Revo/Graphics/ImGuiContext.hpp>
#include <Revo/System/Event.hpp>
#include <Revo/Graphics/RenderTarget.hpp>

// glm
#include <glm/vec2.hpp>

namespace rv
{
    ///
    class Window : public RenderTarget
    {
    public:

        using NativeHandle_t = GLFWwindow*;

        ///
        Window() = default;

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
        Event PollEvent();

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
        NativeHandle_t GetNativeHandle() const;

    private:

        ///
        static Window* M_This(NativeHandle_t window);

        ///
        void M_Destroy();

        ///
        void M_RegisterCallbacks();

        ///
        void M_AdjustFramerate();

        NativeHandle_t m_window = nullptr;
        Event m_event;
        Duration_t m_framerateLimit;
        Clock m_clock;
        Clock m_dtClock;
    };
}