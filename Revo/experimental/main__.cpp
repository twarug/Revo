// #include <Revo/Utility/Functional.hpp>
// #include <Revo/Graphics/PrimitiveType.hpp>
// #include <Revo/Graphics/Image.hpp>
// #include <Revo/Graphics/Texture.hpp>
// #include <Revo/Graphics/Window.hpp>
// #include <Revo/Graphics/VertexBuffer.hpp>
// #include <Revo/Graphics/ShaderProgram.hpp>
// #include <Revo/Graphics/Camera.hpp>
// #include <Revo/Graphics/Transformable.hpp>
//
// #include <algorithm>
// #include <fstream>
// #include <memory>
// #include <string>
// #include <iostream>
// #include <iomanip>
// #include <ctime>
//
// using namespace std::chrono_literals;
//
// int main(int, char**)
// {
//     rv::Context context;
//     if (!context.Initialize())
//     {
//         return -1;
//     }
//
//     rv::Window window;
//     if (!window.Create({ 1280, 720 }, u8"Zażółć gęślą jaźń"))
//     {
//         return -1;
//     }
//
//     rv::ImGuiContext imguiContext;
//     if (!imguiContext.Initialize(window))
//     {
//         return -1;
//     }
//
//     window.SetFramerateLimit(60u);
//
//     while (window.IsOpen())
//     {
//         imguiContext.NewFrame(window);
//
//         rv::Event event;
//         while (window.PollEvent(event))
//         {
//             imguiContext.ProcessEvent(event);
//
//             if (event.GetType() == rv::EventType::AppClosed)
//             {
//                 window.Close();
//             }
//             else if (event.GetType() == rv::EventType::KeyPressed)
//             {
//                 auto const t = rv::SystemClock_t::from_time_t(static_cast<std::time_t>(event.sdlEvent.key.timestamp)).time_since_epoch();
//
//                 std::cout << rv::GetReadableTime(t) << ' ' << (int)event.sdlEvent.key.keysym.sym << '\n';
//                 std::cout << rv::GetReadableTime(t) << ' ' << (int)event.sdlEvent.key.repeat << '\n';
//             }
//         }
//
//         ImGui::ShowDemoWindow(nullptr);
//
//         window.Clear();
//
//         imguiContext.Render(window);
//
//         window.Display();
//     }
//
//     return 0;
// }
