#include <Revo/ImGui/ImGuiContext.hpp>

// Revo
#include <Revo/Graphics/Window.hpp>

namespace rv
{
    ImGuiContext::~ImGuiContext()
    {
        Shutdown();
    }

    bool ImGuiContext::Create(const Window& window)
    {
        m_initialized = ImGui::CreateContext() != nullptr;

        return m_initialized &&
               ImGui_ImplOpenGL3_Init("#version 330") &&
               ImGui_ImplSDL2_InitForOpenGL(window.GetNativeHandle(), window.GetGfxContext());
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
}
