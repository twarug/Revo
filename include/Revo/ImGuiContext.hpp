#pragma once

// Revo
#include <Revo/Context.hpp>

// ImGui
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

namespace rv
{

// fwd decl
class Window;

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
    bool Create(const Window& window);

private:

    bool m_initialized = false;

};

}

#define M2_STRID(__name) __name "##" __FILE__ M2_XSTR(__LINE__)
