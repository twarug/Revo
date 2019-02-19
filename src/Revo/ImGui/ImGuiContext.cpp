#include <Revo/ImGui/ImGuiContext.hpp>

// Revo
#include <Revo/Graphics/Window.hpp>

// ImGui
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <imgui_impl_sdl.h>
#include <imgui_impl_opengl3.h>

namespace rv
{
    ImGuiContext::ImGuiContext()
        : m_initialized { false }
    {

    }

    ImGuiContext::~ImGuiContext()
    {
        Shutdown();
    }

    bool ImGuiContext::Initialize(const Window& window, GfxContext const& gfxContext)
    {
        m_initialized = ImGui::CreateContext() != nullptr;

        return m_initialized &&
               ImGui_ImplOpenGL3_Init("#version 330") &&
               ImGui_ImplSDL2_InitForOpenGL(window.GetNativeHandle(), gfxContext.GetNativeHandle());
    }

    void ImGuiContext::Shutdown()
    {
        if (m_initialized)
        {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplSDL2_Shutdown();
            ImGui::DestroyContext();

            m_initialized = false;
        }
    }

    void ImGuiContext::NewFrame(Window const& window)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window.GetNativeHandle());
        ImGui::NewFrame();
    }

    void ImGuiContext::ProcessEvent(SDL_Event const& event)
    {
        ImGui_ImplSDL2_ProcessEvent(&event);
    }

    void ImGuiContext::Render(RenderTarget const& renderTarget)
    {
        renderTarget.Bind();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}
