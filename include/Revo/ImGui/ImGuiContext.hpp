#pragma once

// Revo
#include <Revo/Graphics/GfxContext.hpp>

// ImGui
#include <imgui.h>

namespace rv
{
    // FWD
    class RenderTarget;
    class Window;
    class GfxContext;

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
        bool Initialize(Window const& window, GfxContext const& gfxContext);

        ///
        void Shutdown();

        ///
        void NewFrame(Window const& window);

        ///
        void ProcessEvent(SDL_Event const& event); // TODO make real event

        ///
        void Render(RenderTarget const& renderTarget);

    private:

        bool m_initialized;
    };
}

#define RV_IMGUI_ID(__name) (__name "##" __FILE__ RV_XSTR(__LINE__))
