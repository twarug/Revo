#pragma once

// Revo
#include <Revo/ImGui/ImGuiContext.hpp>
#include <Revo/System/Clock.hpp>
#include <Revo/System/Context.hpp>
#include <Revo/System/Event.hpp>
#include <Revo/Math/Vector.hpp>

namespace rv
{
    // FWD
    class Camera;
    class ShaderProgram;
    class Transform3D;

    ///
    class Window
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
        Vec2u GetSize() const;

        ///
        void Bind() const;

        ///
        void Clear(Vec4f const& color = { 0.0f, 0.0f, 0.0f, 0.0f });

        ///
        void PrepareToRender(ShaderProgram const& shaderProgram, Camera const& camera) const;

        ///
        void PrepareToRender(ShaderProgram const& shaderProgram, Camera const& camera, Transform3D const& transform) const;

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
        Vec2u m_size;
        Duration_t m_framerateLimit;
        Clock m_dtClock;
        bool m_isOpen;
    };
}
