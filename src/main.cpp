#include <Revo/Utility/Functional.hpp>
#include <Revo/Graphics/Context.hpp>
#include <Revo/Graphics/PrimitiveType.hpp>
#include <Revo/Graphics/Image.hpp>
#include <Revo/Graphics/Texture.hpp>
#include <Revo/Graphics/Window.hpp>
#include <Revo/Graphics/VertexBuffer.hpp>
#include <Revo/Graphics/ShaderProgram.hpp>
#include <Revo/Graphics/Camera.hpp>
#include <Revo/Graphics/Transformable.hpp>

#include <algorithm>
#include <fstream>
#include <memory>
#include <string>
#include <iostream>

using namespace std::chrono_literals;

int main(int, char**)
{
    rv::Context context;
    if (!context.Create())
    {
        // LOG
        return -1;
    }

    rv::Window window;
    if (!window.Create({ 1280, 720 }, u8"Zażółć gęślą jaźń", true))
    {
        // LOG
        return -1;
    }

    window.SetFramerateLimit(60u);

    rv::ImGuiContext imguiContext;
    if (!imguiContext.Create(window))
    {
        // LOG
        return -1;
    }

    while (window.IsOpen())
    {
        imguiContext.NewFrame(window);

        SDL_Event event;
        while (window.PollEvent(event))
        {
            imguiContext.ProcessEvent(event);

            if (event.type == SDL_QUIT)
            {
                window.Close();
            }
        }

        ImGui::ShowDemoWindow(nullptr);

        window.Clear();

        window.Display();
    }

    return 0;
}
