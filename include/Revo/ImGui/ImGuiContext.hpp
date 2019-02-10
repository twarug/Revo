#pragma once

// ImGui
#include <imgui.h>
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

namespace rv
{
    // FWD
    class Window;

    ///
    class ImGuiContext
    {
    public:

        ///
        ImGuiContext() = default;

        ///
        ImGuiContext(const ImGuiContext&) = delete;

        ///
        ImGuiContext& operator = (const ImGuiContext&) = delete;

        ///
        ImGuiContext(ImGuiContext&&) = delete;

        ///
        ImGuiContext& operator = (ImGuiContext&&) = delete;

        ///
        ~ImGuiContext();

        ///
        bool Create(Window const& window);

        ///
        void NewFrame(Window const& window);

        ///
        void ProcessEvent(SDL_Event const& event); // TODO Make real event

        ///
        void Shutdown();

    private:

        bool m_initialized = false;
    };
}

#define RV_IMGUI_ID(__name) (__name "##" __FILE__ RV_XSTR(__LINE__))
