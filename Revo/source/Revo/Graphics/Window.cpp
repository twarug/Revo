#include <Revo/Graphics/Window.hpp>

// Revo
#include <Revo/Graphics/Camera.hpp>
#include <Revo/Graphics/ShaderProgram.hpp>
#include <Revo/Graphics/Transform.hpp>
#include <Revo/Debug/GfxCall.hpp>

// C++
#include <thread>

namespace rv
{
    Window::Window()
        : m_window { nullptr }
        , m_graphicsContext { nullptr }
        , m_size {}
        , m_framerateLimit {}
        , m_dtClock {}
        , m_isOpen { false }
    {

    }

    Window::~Window()
    {
        M_Destroy();
    }

    bool Window::Create(Vec2u const& size, char const* name)
    {
        static bool isGladLoaded = false;

        M_Destroy();

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        m_size = size;
        m_window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_size.x, m_size.y, SDL_WINDOW_OPENGL);

        if (m_window)
        {
            m_graphicsContext = SDL_GL_CreateContext(m_window);

            if (m_graphicsContext)
            {
                gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

                if (!isGladLoaded)
                {
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
            }

            RV_GFX_CALL(glViewport, 0, 0, m_size.x, m_size.y);

            m_framerateLimit = Duration_t::zero();

            m_dtClock.Restart();

            m_isOpen = true;

            return true;
        }

        return false;
    }

    void Window::Show()
    {
        SDL_ShowWindow(m_window);
    }

    void Window::Hide()
    {
        SDL_HideWindow(m_window);
    }

    void Window::Restore()
    {
        SDL_RestoreWindow(m_window);
    }

    void Window::Close()
    {
        m_isOpen = false;
    }

    bool Window::PollEvent(Event& event)
    {
        SDL_Event& implEvent = event.sdlEvent;

        bool const isPolled = SDL_PollEvent(&implEvent) != 0;

        if (isPolled)
        {
            switch (implEvent.type)
            {
                case SDL_WINDOWEVENT_SHOWN:
                {
                    event.type = EventType::WindowShown;
                }
                break;

                case SDL_WINDOWEVENT_HIDDEN:
                {
                    event.type = EventType::WindowHidden;
                }
                break;

                case SDL_WINDOWEVENT_EXPOSED:
                {
                    event.type = EventType::WindowExposed;
                }
                break;

                case SDL_WINDOWEVENT_MOVED:
                {
                    event.type = EventType::WindowMoved;
                }
                break;

                case SDL_WINDOWEVENT_RESIZED:
                {
                    event.type = EventType::WindowResized;
                }
                break;

                case SDL_WINDOWEVENT_SIZE_CHANGED:
                {
                    event.type = EventType::WindowSizeChanged;
                }
                break;

                case SDL_WINDOWEVENT_MINIMIZED:
                {
                    event.type = EventType::WindowMinimized;
                }
                break;

                case SDL_WINDOWEVENT_MAXIMIZED:
                {
                    event.type = EventType::WindowMaximized;
                }
                break;

                case SDL_WINDOWEVENT_RESTORED:
                {
                    event.type = EventType::WindowRestored;
                }
                break;

                case SDL_WINDOWEVENT_ENTER:
                {
                    event.type = EventType::WindowMouseEntered;
                }
                break;

                case SDL_WINDOWEVENT_LEAVE:
                {
                    event.type = EventType::WindowMouseLeft;
                }
                break;

                case SDL_WINDOWEVENT_FOCUS_GAINED:
                {
                    event.type = EventType::WindowFocusGained;
                }
                break;

                case SDL_WINDOWEVENT_FOCUS_LOST:
                {
                    event.type = EventType::WindowFocusLost;
                }
                break;

                case SDL_WINDOWEVENT_CLOSE:
                {
                    event.type = EventType::WindowClosed;
                }
                break;

                case SDL_WINDOWEVENT_TAKE_FOCUS:
                {
                    event.type = EventType::WindowFocusOffered;
                }
                break;

                case SDL_KEYDOWN:
                {
                    event.type = EventType::KeyPressed;
                }
                break;

                case SDL_KEYUP:
                {
                    event.type = EventType::KeyReleased;
                }
                break;

                case SDL_TEXTINPUT:
                {
                    event.type = EventType::TextEntered;
                }
                break;

                case SDL_MOUSEMOTION:
                {
                    event.type = EventType::MouseMoved;
                }
                break;

                case SDL_MOUSEBUTTONDOWN:
                {
                    event.type = EventType::MosueButtonPressed;
                }
                break;

                case SDL_MOUSEBUTTONUP:
                {
                    event.type = EventType::MosueButtonReleased;
                }
                break;

                case SDL_MOUSEWHEEL:
                {
                    event.type = EventType::MouseScrollMoved;
                }
                break;

                case SDL_QUIT:
                {
                    event.type = EventType::AppClosed;
                }
                break;

                case SDL_DROPFILE:
                {
                    event.type = EventType::FileDropped;
                }
                break;

                default: break;
            }

            return true;
        }
        else
        {
            return false;
        }
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

    Vec2u Window::GetSize() const
    {
        return m_size;
    }

    void Window::Bind() const
    {
        RV_GFX_CALL(glBindFramebuffer, GL_FRAMEBUFFER, 0);
    }

    void Window::Clear(Vec4f const& color)
    {
        Bind();

        RV_GFX_CALL(glClearColor, color.x, color.y, color.z, color.w);
        RV_GFX_CALL(glClear, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Window::PrepareToRender(ShaderProgram const& shaderProgram, Camera const& camera) const
    {
        Bind();

        Mat4x4f mvp = Mat4x4f{ 1.0f };
        mvp *= camera.GetProjectionMatrix(m_size);
        mvp *= camera.GetViewMatrix();

        shaderProgram.UseProgram();
        shaderProgram.SetUniform("mvp", mvp);
    }

    void Window::PrepareToRender(ShaderProgram const& shaderProgram, Camera const& camera, Transform const& transform) const
    {
        Bind();

        Mat4x4f mvp = Mat4x4f{ 1.0f };
        mvp *= camera.GetProjectionMatrix(m_size);
        mvp *= camera.GetViewMatrix();
        mvp *= transform.GetMatrix();

        shaderProgram.UseProgram();
        shaderProgram.SetUniform("mvp", mvp);
    }

    void Window::Display()
    {
        Bind();

        SDL_GL_SwapWindow(m_window);

        M_AdjustFramerate();
    }

    bool Window::IsValid() const
    {
        return m_window != nullptr;
    }

    bool Window::IsOpen() const
    {
        return m_isOpen;
    }

    Window::NativeHandle_t Window::GetNativeHandle() const
    {
        return m_window;
    }

    Window::GraphicsContext_t Window::GetGraphicsContext() const
    {
        return m_graphicsContext;
    }

    void Window::M_Destroy()
    {
        if (m_window)
        {
            SDL_DestroyWindow(m_window);
            SDL_GL_DeleteContext(m_graphicsContext);

            m_window = nullptr;
            m_graphicsContext = nullptr;
        }
    }

    void Window::M_AdjustFramerate()
    {
        if (m_framerateLimit != Duration_t::zero())
        {
            std::this_thread::sleep_for(GetDeltaDuration());

            m_dtClock.Restart();
        }
    }
}
