#pragma once

// Revo
#include <Revo/Config.hpp>

// ImGui
#include <imgui.h>

namespace rv
{
    // FWD
    struct Event;
    class Window;

    ///
    class ImGuiContext
    {
    public:

        ///
        ImGuiContext();

        ///
        ImGuiContext(ImGuiContext const&) = delete;

        ///
        ImGuiContext& operator = (ImGuiContext const&) = delete;

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
        void NewFrame(Window const& window) const;

        ///
        void ProcessEvent(Event const& event) const;

        ///
        void Render(Window const& window) const;

    private:

        bool m_initialized;
    };
}

#define RV_IMGUI_ID(__name) __name "##" RV_HERE
