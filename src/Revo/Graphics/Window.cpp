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
                event.m_type = EventType::WindowShown;
            }
            break;

            case SDL_WINDOWEVENT_HIDDEN:
            {
                event.m_type = EventType::WindowHidden;
            }
            break;

            case SDL_WINDOWEVENT_EXPOSED:
            {
                event.m_type = EventType::WindowExposed;
            }
            break;

            case SDL_WINDOWEVENT_MOVED:
            {
                event.m_type = EventType::WindowMoved;
            }
            break;

            case SDL_WINDOWEVENT_RESIZED:
            {
                event.m_type = EventType::WindowResized;
            }
            break;

            case SDL_WINDOWEVENT_SIZE_CHANGED:
            {
                event.m_type = EventType::WindowSizeChanged;
            }
            break;

            case SDL_WINDOWEVENT_MINIMIZED:
            {
                event.m_type = EventType::WindowMinimized;
            }
            break;

            case SDL_WINDOWEVENT_MAXIMIZED:
            {
                event.m_type = EventType::WindowMaximized;
            }
            break;

            case SDL_WINDOWEVENT_RESTORED:
            {
                event.m_type = EventType::WindowRestored;
            }
            break;

            case SDL_WINDOWEVENT_ENTER:
            {
                event.m_type = EventType::WindowMouseEntered;
            }
            break;

            case SDL_WINDOWEVENT_LEAVE:
            {
                event.m_type = EventType::WindowMouseLeft;
            }
            break;

            case SDL_WINDOWEVENT_FOCUS_GAINED:
            {
                event.m_type = EventType::WindowFocusGained;
            }
            break;

            case SDL_WINDOWEVENT_FOCUS_LOST:
            {
                event.m_type = EventType::WindowFocusLost;
            }
            break;

            case SDL_WINDOWEVENT_CLOSE:
            {
                event.m_type = EventType::WindowClosed;
            }
            break;

            case SDL_WINDOWEVENT_TAKE_FOCUS:
            {
                event.m_type = EventType::WindowFocusOffered;
            }
            break;

            case SDL_KEYDOWN:
            {
                event.m_type = EventType::KeyPressed;
            }
            break;

            case SDL_KEYUP:
            {
                event.m_type = EventType::KeyReleased;
            }
            break;

            case SDL_TEXTINPUT:
            {
                event.m_type = EventType::TextEntered;
            }
            break;

            case SDL_MOUSEMOTION:
            {
                event.m_type = EventType::MouseMoved;
            }
            break;

            case SDL_MOUSEBUTTONDOWN:
            {
                event.m_type = EventType::MosueButtonPressed;
            }
            break;

            case SDL_MOUSEBUTTONUP:
            {
                event.m_type = EventType::MosueButtonReleased;
            }
            break;

            case SDL_MOUSEWHEEL:
            {
                event.m_type = EventType::MouseScrollMoved;
            }
            break;

            case SDL_QUIT:
            {
                event.m_type = EventType::AppClosed;
            }
            break;

            case SDL_DROPFILE:
            {
                event.m_type = EventType::FileDropped;
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
