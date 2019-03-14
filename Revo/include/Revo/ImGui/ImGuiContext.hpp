#pragma once

// Revo
#include <Revo/Config.hpp>

// ImGui
#include <imgui.h>

namespace rv
{
    // FWD
    class RenderTarget;
    class Window;
    class Event;

    ///
    class ImGuiContext
    {
    public:

        ///
        ImGuiContext();

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
        bool Initialize(Window const& window);

        ///
        void Shutdown();

        ///
        void NewFrame(Window const& window);

        ///
        void ProcessEvent(Event const& event);

        ///
        void Render(RenderTarget const& renderTarget);

    private:

        bool m_initialized;
    };
}

#define RV_IMGUI_ID(__name) (__name "##" RV_HERE)
