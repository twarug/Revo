#include <Revo/ImGui/ImGuiContext.hpp>

// Revo
#include <Revo/Graphics/Window.hpp>
#include <Revo/System/Event.hpp>

// ImGui
#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#include <ImGui/imgui_impl_sdl.h>
#include <ImGui/imgui_impl_opengl3.h>

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

    bool ImGuiContext::Initialize(Window const& window)
    {
        m_initialized = ImGui::CreateContext() != nullptr;

        return m_initialized &&
               ImGui_ImplOpenGL3_Init("#version 330") &&
               ImGui_ImplSDL2_InitForOpenGL(window.GetNativeHandle(), window.GetGraphicsContext());
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

    void ImGuiContext::NewFrame(Window const& window) const
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window.GetNativeHandle());
        ImGui::NewFrame();
    }

    void ImGuiContext::ProcessEvent(Event const& event) const
    {
        ImGui_ImplSDL2_ProcessEvent(&event.sdlEvent);
    }

    void ImGuiContext::Render(Window const& window) const
    {
        window.Bind();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}
