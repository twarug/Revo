#include <Revo/Debug/GfxCall.hpp>
#include <Revo/Graphics/PrimitiveType.hpp>
#include <Revo/Graphics/Image.hpp>
#include <Revo/Graphics/Texture.hpp>
#include <Revo/Graphics/Window.hpp>
#include <Revo/Graphics/VertexBuffer.hpp>
#include <Revo/Graphics/ShaderProgram.hpp>
#include <Revo/Graphics/Camera.hpp>
#include <Revo/Graphics/Transformable.hpp>
#include <Revo/System/Event.hpp>

#include <iostream>

int main(int, char**)
{
    rv::Context context;
    if (!context.Initialize())
    {
        return -1;
    }

    rv::Window window;
    if (!window.Create({ 1280, 720 }, "Zażółć gęślą jaźń"))
    {
        return -1;
    }

    rv::ImGuiContext imguiContext;
    if (!imguiContext.Initialize(window))
    {
        return -1;
    }

    window.SetFramerateLimit(60);

    //

    rv::Vec4f white = { 1.0f, 1.0f, 1.0f, 1.0f };

    rv::Vertex const vexCube[] = {
        { { -1,  1,  1 }, white, { 0, 0 } }, // front
        { {  1,  1,  1 }, white, { 1, 0 } },
        { { -1, -1,  1 }, white, { 0, 1 } },
        { { -1, -1,  1 }, white, { 0, 1 } },
        { {  1,  1,  1 }, white, { 1, 0 } },
        { {  1, -1,  1 }, white, { 1, 1 } },

        { {  1,  1,  1 }, white, { 0, 0 } }, // right
        { {  1,  1, -1 }, white, { 1, 0 } },
        { {  1, -1,  1 }, white, { 0, 1 } },
        { {  1, -1,  1 }, white, { 0, 1 } },
        { {  1,  1, -1 }, white, { 1, 0 } },
        { {  1, -1, -1 }, white, { 1, 1 } },

        { {  1,  1, -1 }, white, { 0, 0 } }, // back
        { { -1,  1, -1 }, white, { 1, 0 } },
        { {  1, -1, -1 }, white, { 0, 1 } },
        { {  1, -1, -1 }, white, { 0, 1 } },
        { { -1,  1, -1 }, white, { 1, 0 } },
        { { -1, -1, -1 }, white, { 1, 1 } },

        { { -1,  1, -1 }, white, { 0, 0 } }, // left
        { { -1,  1,  1 }, white, { 1, 0 } },
        { { -1, -1, -1 }, white, { 0, 1 } },
        { { -1, -1, -1 }, white, { 0, 1 } },
        { { -1,  1,  1 }, white, { 1, 0 } },
        { { -1, -1,  1 }, white, { 1, 1 } },

        { { -1,  1, -1 }, white, { 0, 0 } }, // top
        { {  1,  1, -1 }, white, { 1, 0 } },
        { { -1,  1,  1 }, white, { 0, 1 } },
        { { -1,  1,  1 }, white, { 0, 1 } },
        { {  1,  1, -1 }, white, { 1, 0 } },
        { {  1,  1,  1 }, white, { 1, 1 } },

        { {  1, -1, -1 }, white, { 0, 0 } }, // bottom
        { { -1, -1, -1 }, white, { 1, 0 } },
        { {  1, -1,  1 }, white, { 0, 1 } },
        { {  1, -1,  1 }, white, { 0, 1 } },
        { { -1, -1, -1 }, white, { 1, 0 } },
        { { -1, -1,  1 }, white, { 1, 1 } },
    };

    rv::VertexBuffer avCube{ vexCube, std::size(vexCube), rv::PrimitiveType::Triangles };
    rv::Transformable trCube{ rv::Vec3f{ 0.0f, 0.0f, -4.0f }, rv::Vec3f{ 0.0f, 0.0f, 0.0f }, rv::Vec3f{ 0.0f, 0.0f, 0.0f }, rv::Vec3f{ 1.0f, 1.0f, 1.0f } };

    std::cout << std::boolalpha;

    rv::Shader defaultVert;
    std::cout << defaultVert.LoadFromFile(rv::ShaderType::Vertex, "default.vert") << ' ';
    rv::Shader defaultFrag;
    std::cout << defaultFrag.LoadFromFile(rv::ShaderType::Fragment, "default.frag") << ' ';
    rv::Shader testFrag;
    std::cout << testFrag.LoadFromFile(rv::ShaderType::Fragment, "test.frag") << ' ';

    rv::ShaderProgram shaderProgram;
    std::cout << shaderProgram.LinkShaders({ &defaultVert, &testFrag }) << ' ';

    rv::Texture tex;
    std::cout << tex.LoadFromFile("tex.png") << ' ';

    rv::Clock cl;

    rv::Camera camera3D{ rv::PerspectiveProjection{} };

    //

    RV_GFX_CALL(glEnable, GL_BLEND);
    RV_GFX_CALL(glBlendFuncSeparate, GL_ONE, GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_ONE);
    RV_GFX_CALL(glBlendEquationSeparate, GL_FUNC_ADD, GL_FUNC_ADD);

    RV_GFX_CALL(glEnable, GL_CULL_FACE);
    RV_GFX_CALL(glCullFace, GL_FRONT);
    RV_GFX_CALL(glFrontFace, GL_CCW);

    //

    while (window.IsOpen())
    {
        imguiContext.NewFrame(window);

        rv::Event event;
        while (window.PollEvent(event))
        {
            imguiContext.ProcessEvent(event);

            if (event.type == rv::EventType::AppClosed)
            {
                window.Close();
            }
        }

        ImGui::ShowDemoWindow(nullptr);

        shaderProgram.UseProgram();
        shaderProgram.D_ShowShaderProgramEditor();
        shaderProgram.SetUniform("time", rv::AsFSeconds(cl.GetElapsedDuration()));
        shaderProgram.SetUniform("resolution", window.GetSize());

        window.Clear();

        trCube.D_ShowTransformableEditor();

        tex.Bind(0);
        avCube.Render(window, shaderProgram, camera3D, trCube.GetTransform());

        imguiContext.Render(window);

        window.Display();
    }

    return 0;
}
