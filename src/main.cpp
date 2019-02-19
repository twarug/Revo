#include <Revo/Utility/Functional.hpp>
#include <Revo/Graphics/PrimitiveType.hpp>
#include <Revo/Graphics/Image.hpp>
#include <Revo/Graphics/Texture.hpp>
#include <Revo/Graphics/Window.hpp>
#include <Revo/Graphics/VertexBuffer.hpp>
#include <Revo/Graphics/ShaderProgram.hpp>
#include <Revo/Graphics/Camera.hpp>
#include <Revo/Graphics/Transformable.hpp>
#include <Revo/Graphics/GfxContext.hpp>

#include <algorithm>
#include <fstream>
#include <memory>
#include <string>
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std::chrono_literals;

std::string timeStampToHReadble(const time_t rawtime)
{
    struct tm * dt;
    char buffer [30];
    dt = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%H:%M:%S %d/%m/%Y", dt);
    return std::string(buffer);
}

int main(int, char**)
{
    rv::Context context;
    if (!context.Initialize())
    {
        return -1;
    }

    rv::Window window;
    if (!window.Create({ 1280, 720 }, u8"Zażółć gęślą jaźń"))
    {
        return -1;
    }

    rv::GfxContext gfxContext;
    if (!gfxContext.Initialize(window))
    {
        return -1;
    }

    rv::ImGuiContext imguiContext;
    if (!imguiContext.Initialize(window, gfxContext))
    {
        return -1;
    }

    window.SetFramerateLimit(60u);

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
            else if (event.type == SDL_KEYDOWN)
            {
                auto const t = rv::SystemClock_t::from_time_t(static_cast<std::time_t>(event.key.timestamp)).time_since_epoch();

                std::cout << rv::GetReadableTime(t) << ' ' << (int)event.key.keysym.sym << '\n';
                std::cout << rv::GetReadableTime(t) << ' ' << (int)event.key.repeat << '\n';
            }
        }

        ImGui::ShowDemoWindow(nullptr);

        window.Clear();

        imguiContext.Render(window);

        window.Display();
    }

    return 0;
}
