#include <Revo/Graphics/Window.hpp>

// Revo
#include <Revo/Graphics/Backend.hpp>

// C++
#include <thread>

namespace rv
{
    Window::Window()
        : m_window { nullptr }
        , m_graphicsContext { nullptr }
        , m_framerateLimit {}
        , m_dtClock {}
        , m_isOpen { false }
    {

    }

    Window::~Window()
    {
        M_Destroy();
    }

    bool Window::Create(glm::uvec2 const& size, char const* name)
    {
        static bool isGladLoaded = false;

        M_Destroy();

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
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

        switch (implEvent.type)
        {
            case SDL_WINDOWEVENT_SHOWN:
            {
                event = Event{ EventType::WindowShown };
            }
            break;

            case SDL_WINDOWEVENT_HIDDEN:
            {
                event = Event{ EventType::WindowHidden };
            }
            break;

            case SDL_WINDOWEVENT_EXPOSED:
            {
                event = Event{ EventType::WindowExposed };
            }
            break;

            case SDL_WINDOWEVENT_MOVED:
            {
                event = Event{ EventType::WindowMoved };
            }
            break;

            case SDL_WINDOWEVENT_RESIZED:
            {
                event = Event{ EventType::WindowResized };
            }
            break;

            case SDL_WINDOWEVENT_SIZE_CHANGED:
            {
                event = Event{ EventType::WindowSizeChanged };
            }
            break;

            case SDL_WINDOWEVENT_MINIMIZED:
            {
                event = Event{ EventType::WindowMinimized };
            }
            break;

            case SDL_WINDOWEVENT_MAXIMIZED:
            {
                event = Event{ EventType::WindowMaximized };
            }
            break;

            case SDL_WINDOWEVENT_RESTORED:
            {
                event = Event{ EventType::WindowRestored };
            }
            break;

            case SDL_WINDOWEVENT_ENTER:
            {
                event = Event{ EventType::WindowMouseEntered };
            }
            break;

            case SDL_WINDOWEVENT_LEAVE:
            {
                event = Event{ EventType::WindowMouseLeft };
            }
            break;

            case SDL_WINDOWEVENT_FOCUS_GAINED:
            {
                event = Event{ EventType::WindowFocusGained };
            }
            break;

            case SDL_WINDOWEVENT_FOCUS_LOST:
            {
                event = Event{ EventType::WindowFocusLost };
            }
            break;

            case SDL_WINDOWEVENT_CLOSE:
            {
                event = Event{ EventType::WindowClosed };
            }
            break;

            case SDL_WINDOWEVENT_TAKE_FOCUS:
            {
                event = Event{ EventType::WindowFocusOffered };
            }
            break;

            case SDL_KEYDOWN:
            {
                event = Event{ EventType::KeyPressed };
            }
            break;

            case SDL_KEYUP:
            {
                event = Event{ EventType::KeyReleased };
            }
            break;

            case SDL_TEXTINPUT:
            {
                event = Event{ EventType::TextEntered };
            }
            break;

            case SDL_MOUSEMOTION:
            {
                event = Event{ EventType::MouseMoved };
            }
            break;

            case SDL_MOUSEBUTTONDOWN:
            {
                event = Event{ EventType::MosueButtonPressed };
            }
            break;

            case SDL_MOUSEBUTTONUP:
            {
                event = Event{ EventType::MosueButtonReleased };
            }
            break;

            case SDL_MOUSEWHEEL:
            {
                event = Event{ EventType::MouseScrollMoved };
            }
            break;

            case SDL_QUIT:
            {
                event = Event{ EventType::AppClosed };
            }
            break;

            case SDL_DROPFILE:
            {
                event = Event{ EventType::FileDropped };
            }
            break;

            default: break;
        }

        return isPolled;
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

    void Window::Bind() const
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
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
