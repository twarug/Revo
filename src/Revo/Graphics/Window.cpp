#include <Revo/Graphics/Window.hpp>

// // Revo
// #include <Revo/Graphics/Context.hpp>

// C++
#include <thread>

namespace rv
{
    Window::Window()
        : m_gfxContext { nullptr }
        , m_window { nullptr }
        , m_framerateLimit {}
        , m_clock {}
        , m_dtClock {}
        // , m_event {}
        , m_isOpen { false }
    {

    }

    Window::~Window()
    {
        M_Destroy();
    }

    bool Window::Create(const glm::uvec2& size, const char* name, bool makeContextCurrent)
    {
        M_Destroy();

        // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        // hints GLFW_RESIZABLE GLFW_VISIBLE GLFW_DECORATED GLFW_FOCUSED GLFW_AUTO_ICONIFY GLFW_FLOATING GLFW_MAXIMIZED
        // attrib GLFW_FOCUSED GLFW_ICONIFIED GLFW_MAXIMIZED GLFW_VISIBLE GLFW_RESIZABLE GLFW_DECORATED GLFW_FLOATING

        m_size = size;
        // m_window = glfwCreateWindow(m_size.x, m_size.y, name, nullptr, nullptr);
        m_window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_size.x, m_size.y, SDL_WINDOW_OPENGL);
        m_gfxContext = SDL_GL_CreateContext(m_window);

        if (m_window)
        {
            // glfwSetWindowUserPointer(m_window, this);

            if (makeContextCurrent)
            {
                // glfwMakeContextCurrent(m_window);
                SDL_GL_MakeCurrent(m_window, m_gfxContext);
            }

            static bool isGladLoaded = false;

            if (!isGladLoaded)
            {
                // gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
                gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

                if (gladLoadGL())
                {
            		isGladLoaded = true;
            	}
                else
                {
                    // TODO better logging
                    std::fprintf(stderr, "Failed to initialize GLAD\n");
                }
            }

            // M_RegisterCallbacks();

            m_framerateLimit = Duration_t::zero();

            m_clock.Restart();
            m_dtClock.Restart();

            m_isOpen = true;

            return true;
        }

        return false;
    }

    void Window::Show()
    {
        // glfwShowWindow(m_window);
        SDL_ShowWindow(m_window);
    }

    void Window::Hide()
    {
        // glfwHideWindow(m_window);
        SDL_HideWindow(m_window);
    }

    void Window::Restore()
    {
        // glfwRestoreWindow(m_window);
        SDL_RestoreWindow(m_window);
    }

    void Window::Iconify()
    {
        // glfwIconifyWindow(m_window);
    }

    void Window::Close()
    {
        // glfwSetWindowShouldClose(m_window, GLFW_TRUE);
        m_isOpen = false;
    }

    // Event Window::PollEvent()
    // {
    //     glfwPollEvents();
    //
    //     ImGui_ImplOpenGL3_NewFrame();
    //     ImGui_ImplGlfw_NewFrame();
    //     ImGui::NewFrame();
    //
    //     auto copy = m_event;
    //
    //     m_event = EventType::None;
    //
    //     return copy;
    // }

    bool Window::PollEvent(SDL_Event& event)
    {
        return SDL_PollEvent(&event) != 0;
    }

    void Window::SetFramerateLimit(uint32_t limit)
    {
        if (limit == 0)
        {
            m_framerateLimit = Duration_t::zero();
        }
        else
        {
            m_framerateLimit = AsDefaultDuration(std::chrono::duration<float>{ 1.0f / limit });
        }
    }

    uint32_t Window::GetFramerateLimit() const
    {
        if (m_framerateLimit == Duration_t::zero())
        {
            return 0;
        }

        return static_cast<uint32_t>(1.0f / AsFSeconds(m_framerateLimit));
    }

    Duration_t Window::GetDeltaDuration() const
    {
        return m_framerateLimit - m_dtClock.GetElapsedDuration();
    }

    float Window::GetFramerate() const
    {
        return 1.0f / AsFSeconds(GetDeltaDuration());
    }

    void Window::Bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void Window::Display()
    {
        Bind();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // glfwSwapBuffers(m_window);
        SDL_GL_SwapWindow(m_window);

        M_AdjustFramerate();
    }

    bool Window::IsValid() const
    {
        return m_window != nullptr;
    }

    bool Window::IsOpen() const
    {
        // return !glfwWindowShouldClose(m_window);
        return m_isOpen;
    }

    Window::GfxContext_t Window::GetGfxContext() const
    {
        return m_gfxContext;
    }

    Window::NativeHandle_t Window::GetNativeHandle() const
    {
        return m_window;
    }

    // Window* Window::M_This(NativeHandle_t window)
    // {
    //     return reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    // }

    void Window::M_Destroy()
    {
        if (m_window)
        {
            // glfwDestroyWindow(m_window);
            SDL_GL_DeleteContext(m_gfxContext);
            SDL_DestroyWindow(m_window);

            m_gfxContext = nullptr;
            m_window = nullptr;
        }
    }

    // void Window::M_RegisterCallbacks()
    // {
    //     glfwSetWindowCloseCallback(m_window, [](NativeHandle_t window) {
    //         M_This(window)->m_event = EventType::Closed;
    //     });
    //
    //     glfwSetWindowPosCallback(m_window, [](NativeHandle_t window, int xpos, int ypos) {
    //         M_This(window)->m_event = EventType::WindowMoved;
    //         M_This(window)->m_event.windowPosition = { xpos, ypos };
    //     });
    //
    //     glfwSetWindowSizeCallback(m_window, [](NativeHandle_t window, int width, int height) {
    //         M_This(window)->m_event = EventType::WindowResized;
    //         M_This(window)->m_event.windowSize = { width, height };
    //     });
    //
    //     glfwSetFramebufferSizeCallback(m_window, [](NativeHandle_t window, int width, int height) {
    //         M_This(window)->m_event = EventType::FramebufferResized;
    //         M_This(window)->m_event.framebufferSize = { width, height };
    //     });
    //
    //     glfwSetWindowFocusCallback(m_window, [](NativeHandle_t window, int focused) {
    //         M_This(window)->m_event = (focused == GLFW_TRUE) ? EventType::GainedFocus : EventType::LostFocus;
    //     });
    //
    //     glfwSetCursorPosCallback(m_window, [](NativeHandle_t window, double xpos, double ypos) {
    //         M_This(window)->m_event = EventType::CursorMoved;
    //         M_This(window)->m_event.cursorPosition = { xpos, ypos };
    //     });
    //
    //     glfwSetCursorEnterCallback(m_window, [](NativeHandle_t window, int entered) {
    //         M_This(window)->m_event = (entered == GLFW_TRUE) ? EventType::CursorEntered : EventType::CursorLeft;
    //     });
    //
    //     glfwSetScrollCallback(m_window, [](NativeHandle_t window, double xoffset, double yoffset) {
    //         M_This(window)->m_event = EventType::ScrollMoved;
    //         M_This(window)->m_event.scrollDelta = { xoffset, yoffset };
    //         ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
    //     });
    //
    //     glfwSetCharModsCallback(m_window, [](NativeHandle_t window, unsigned int codepoint, int mods) {
    //         M_This(window)->m_event = EventType::TextEntered;
    //         M_This(window)->m_event.enteredText = { codepoint, mods };
    //         ImGui_ImplGlfw_CharCallback(window, codepoint);
    //     });
    //
    //     // TODO better
    //     glfwSetDropCallback(m_window, [](NativeHandle_t window, int count, const char** paths) {
    //         static char** droppedFiles = nullptr;
    //         if (droppedFiles != nullptr) { delete[] droppedFiles; droppedFiles = nullptr; }
    //         droppedFiles = new char*[count]{};
    //         for (int i = 0; i < count; ++i)
    //         {
    //             droppedFiles[i] = new char[std::strlen(paths[i]) + 1u]{};
    //             std::strcpy(droppedFiles[i], paths[i]);
    //         }
    //
    //         M_This(window)->m_event = EventType::FilesDropped;
    //         M_This(window)->m_event.droppedFiles = { count, (const char**)droppedFiles };
    //     });
    //
    //     glfwSetKeyCallback(m_window, [](NativeHandle_t window, int key, int scancode, int action, int mods) {
    //         M_This(window)->m_event = EventType::KeyStateChanged;
    //         M_This(window)->m_event.keyState = { key, scancode, action, mods };
    //         ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);
    //     });
    //
    //     glfwSetMouseButtonCallback(m_window, [](NativeHandle_t window, int button, int action, int mods) {
    //         M_This(window)->m_event = EventType::MouseButtonStateChanged;
    //         M_This(window)->m_event.mouseButtonState = { button, action, mods };
    //         ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);
    //     });
    // }

    void Window::M_AdjustFramerate()
    {
        if (m_framerateLimit != Duration_t::zero())
        {
            std::this_thread::sleep_for(GetDeltaDuration());

            m_clock.Restart();
            m_dtClock.Restart();
        }
    }
}
