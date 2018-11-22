#include <Revo/Graphics/ImGuiContext.hpp>

// Revo
#include <Revo/Graphics/Window.hpp>

namespace rv
{
    ImGuiContext::~ImGuiContext()
    {
        if (m_initialized)
        {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplGlfw_Shutdown();

            ImGui::DestroyContext();

            m_initialized = false;
        }
    }

    bool ImGuiContext::Create(const Window& window)
    {
        return (m_initialized = ImGui::CreateContext() != nullptr) &&
            ImGui_ImplGlfw_InitForOpenGL(window.GetNativeHandle(), false) &&
            ImGui_ImplOpenGL3_Init();
    }
}
