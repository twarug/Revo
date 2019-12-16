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

    const rv::Vertex vexPixFan2D[] = {
        { {    0/* + 100*/,   0/* + 100*/, 0 }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } },
        { { 1280/* + 100*/,   0/* + 100*/, 0 }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f } },
        { { 1280/* + 100*/, 720/* + 100*/, 0 }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f } },
        { {    0/* + 100*/, 720/* + 100*/, 0 }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f } },
    };

    const rv::Vertex vexPixFan3D[] = {
        { {    0/* + 100*/,   0/* + 100*/, 0 }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } },
        { { 1.0f/* + 100*/,   0/* + 100*/, 0 }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f } },
        { { 1.0f/* + 100*/, 0.5625f/* + 100*/, 0 }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f } },
        { {    0/* + 100*/, 0.5625f/* + 100*/, 0 }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f } },
    };

    const rv::Vertex vexCube[] = {
        { { -1.0f, -1.0f, -1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f } },
        { { -1.0f, -1.0f,  1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f } },
        { { -1.0f,  1.0f,  1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } },

        { {  1.0f,  1.0f, -1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f } },
        { { -1.0f, -1.0f, -1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f } },
        { { -1.0f,  1.0f, -1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } },

        { {  1.0f, -1.0f,  1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f } },
        { { -1.0f, -1.0f, -1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f } },
        { {  1.0f, -1.0f, -1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } },

        { {  1.0f,  1.0f, -1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f } },
        { {  1.0f, -1.0f, -1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f } },
        { { -1.0f, -1.0f, -1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } },

        { { -1.0f, -1.0f, -1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f } },
        { { -1.0f,  1.0f,  1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f } },
        { { -1.0f,  1.0f, -1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } },

        { {  1.0f, -1.0f,  1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f } },
        { { -1.0f, -1.0f,  1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f } },
        { { -1.0f, -1.0f, -1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } },

        { { -1.0f,  1.0f,  1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f } },
        { { -1.0f, -1.0f,  1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f } },
        { {  1.0f, -1.0f,  1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } },

        { {  1.0f,  1.0f,  1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f } },
        { {  1.0f, -1.0f, -1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f } },
        { {  1.0f,  1.0f, -1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } },

        { {  1.0f, -1.0f, -1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f } },
        { {  1.0f,  1.0f,  1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f } },
        { {  1.0f, -1.0f,  1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } },

        { {  1.0f,  1.0f,  1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f } },
        { {  1.0f,  1.0f, -1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f } },
        { { -1.0f,  1.0f, -1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } },

        { {  1.0f,  1.0f,  1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f } },
        { { -1.0f,  1.0f, -1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f } },
        { { -1.0f,  1.0f,  1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } },

        { {  1.0f,  1.0f,  1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f } },
        { { -1.0f,  1.0f,  1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 0.0f } },
        { {  1.0f, -1.0f,  1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 1.0f } },
    };

    rv::VertexBuffer av2D{ vexPixFan2D, 4u, rv::PrimitiveType::TriangleFan };
    rv::VertexBuffer av3D{ vexPixFan3D, 4u, rv::PrimitiveType::TriangleFan };
    rv::VertexBuffer av3Db{ vexPixFan3D, 4u, rv::PrimitiveType::TriangleFan };
    rv::VertexBuffer avCube{ vexCube, 36u, rv::PrimitiveType::Triangles };

    av2D.SetTransform(rv::Vec3f{ 640, 360, 0 }, rv::Vec3f{ 320, 0, 0 }, rv::Vec3f{ 0, 0, 0 }, rv::Vec3f{ 1, 2, 1 });
    av3D.SetTransform(rv::Vec3f{ 1.0f, 0.5625f, 0 }, rv::Vec3f{ 0.5f, 0, 0 }, rv::Vec3f{ 0, 0, 0 }, rv::Vec3f{ 1, 2, 1 });
    av3Db.SetTransform(rv::Vec3f{ 0, 0, 0 }, rv::Vec3f{ 0.5f, 0.28125f, 0 }, rv::Vec3f{ 0, 0, 0 }, rv::Vec3f{ 2, 1, 1 });
    avCube.SetTransform(rv::Vec3f{ 0, 0, -4 }, rv::Vec3f{ 0, 0, 0 }, rv::Vec3f{ 0.5f, 0.5f, 0 }, rv::Vec3f{ 1, 1, 1 });

    std::cout << std::boolalpha;

    rv::Shader defaultVert;
    std::cout << defaultVert.LoadFromFile(rv::ShaderType::Vertex, "default.vert") << ' ';
    rv::Shader defaultFrag;
    std::cout << defaultFrag.LoadFromFile(rv::ShaderType::Fragment, "default.frag") << ' ';
    rv::Shader testFrag;
    std::cout << testFrag.LoadFromFile(rv::ShaderType::Fragment, "test.frag") << ' ';

    rv::ShaderProgram shaderProgram;
    std::cout << shaderProgram.LinkShaders({ &defaultVert, &testFrag }) << ' ';

    rv::Texture tex1;
    std::cout << tex1.LoadFromFile("map1.png") << ' ';
    rv::Texture tex2;
    std::cout << tex2.LoadFromFile("map2.png") << ' ';

    rv::Clock cl;

    rv::Camera camera2D{ rv::OrthographicProjection{} };
    rv::Camera camera3D{ rv::PerspectiveProjection{} };

    //

    glEnable(GL_BLEND);
    RV_GFX_CALL(glBlendFuncSeparate, GL_ONE, GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_ONE);
    glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);

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

        // av2D.D_ShowTransformableEditor();
        // av3D.D_ShowTransformableEditor();
        // av3Db.D_ShowTransformableEditor();
        avCube.D_ShowTransformableEditor();
        // camera3D.D_ShowCameraEditor();

        window.Clear();

        tex1.Bind(0);

        // glDisable(GL_DEPTH_TEST);
        // av2D.Render(window, shaderProgram, camera2D);
        // glEnable(GL_DEPTH_TEST);
        // av3D.Render(window, shaderProgram, camera3D);
        // av3Db.Render(window, shaderProgram, camera3D);
        avCube.Render(window, shaderProgram, camera3D);

        imguiContext.Render(window);

        window.Display();
    }

    return 0;
}
