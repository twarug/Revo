#include <Revo/Image.hpp>
#include <Revo/Texture.hpp>
#include <Revo/Window.hpp>
#include <Revo/VertexBuffer.hpp>
#include <Revo/ShaderProgram.hpp>
#include <Revo/Camera.hpp>
#include <Revo/Transformable.hpp>
#include <m2/chrono/Conversion.hpp>

#include <algorithm>
#include <fstream>
#include <memory>
#include <string>
#include <iostream>

using namespace std::chrono_literals;

int main()
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

    av2D.SetTransform(glm::vec3{ 640, 360, 0 }, glm::vec3{ 320, 0, 0 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 1, 2, 1 });
    av3D.SetTransform(glm::vec3{ 1.0f, 0.5625f, 0 }, glm::vec3{ 0.5f, 0, 0 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 1, 2, 1 });
    av3Db.SetTransform(glm::vec3{ 0.0f, 0.0f, 0 }, glm::vec3{ 0.5f, 0.28125f, 0 }, glm::vec3{ 0, 0, 0 }, glm::vec3{ 2, 1, 1 });

    std::cout << "---------------------" << '\n';
    const auto m1 = av2D.GetTransform();
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            std::cout << m1[j][i] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "---------------------" << '\n';
    const auto m2 = av3D.GetTransform();
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            std::cout << m2[j][i] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << "---------------------" << '\n';

    rv::VertexBuffer fboVA{ vexPixFan2D, 4u, rv::PrimitiveType::TriangleFan };

    rv::Shader defaultVert;
    std::cout << defaultVert.LoadFromFile(rv::ShaderType::Vertex, "default.vert") << '\n';
    rv::Shader defaultFrag;
    std::cout << defaultFrag.LoadFromFile(rv::ShaderType::Fragment, "default.frag") << '\n';
    rv::Shader testFrag;
    std::cout << testFrag.LoadFromFile(rv::ShaderType::Fragment, "test.frag") << '\n';

    rv::ShaderProgram shaderProgram;
    std::cout << shaderProgram.LinkShaders(defaultVert, testFrag) << '\n';

    rv::Texture tex1;
    std::cout << tex1.LoadFromFile("map1.png") << '\n';
    rv::Texture tex2;
    std::cout << tex2.LoadFromFile("map2.png") << '\n';

    m2::chrono::Clock cl;

    rv::Camera camera2D{ rv::OrthographicProjection{} };
    rv::Camera camera3D{ rv::PerspectiveProjection{} };

    int width, height;
    glfwGetFramebufferSize(window.GetNativeHandle(), &width, &height);
    glViewport(0, 0, width, height);

    //

    glEnable(GL_BLEND);
    glBlendFuncSeparate(GL_ONE, GL_ONE_MINUS_SRC_ALPHA, GL_ONE_MINUS_DST_ALPHA, GL_ONE);
    glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);

    //

    while (window.IsOpen())
    {
        glfwSetWindowTitle(window.GetNativeHandle(), ("Framerate: " + std::to_string(window.GetFramerate())).data());

        auto event = window.PollEvent();

        ImGui::ShowDemoWindow(nullptr);

        shaderProgram.D_ShowShaderProgramEditor(nullptr);
        shaderProgram.SetUniform("time", m2::chrono::AsFSeconds(cl.GetElapsedDuration()));
        shaderProgram.SetUniform("resolution", glm::vec2{ width, height });

        av2D.D_ShowTransformableEditor(nullptr);
        av3D.D_ShowTransformableEditor(nullptr);
        av3Db.D_ShowTransformableEditor(nullptr);
        avCube.D_ShowTransformableEditor(nullptr);
        camera3D.D_ShowCameraEditor(nullptr);

        window.Clear({ 0.0f, 0.0f, 0.0f, 1.0f });

        tex1.Bind(0);

        glDisable(GL_DEPTH_TEST);
        window.Draw(av2D, { &shaderProgram, &camera2D });
        glEnable(GL_DEPTH_TEST);
        window.Draw(av3D, { &shaderProgram, &camera3D });
        window.Draw(av3Db, { &shaderProgram, &camera3D });
        window.Draw(avCube, { &shaderProgram, &camera3D });

        window.Display();
    }

    return 0;
}
