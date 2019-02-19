#include <Revo/Graphics/GfxContext.hpp>

// Revo
#include <Revo/Graphics/Window.hpp>

// C++
#include <cstdio>

namespace rv
{
    GfxContext::GfxContext()
        : m_initialized { false }
        , m_handle { nullptr }
    {

    }

    GfxContext::~GfxContext()
    {
        Shutdown();
    }

    bool GfxContext::Initialize(Window const& window)
    {
        m_handle = SDL_GL_CreateContext(window.GetNativeHandle());

        if (m_handle == nullptr)
        {
            return false;
        }

        gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

        if (gladLoadGL())
        {
            m_initialized = true;
        }
        else
        {
            // TODO better logging
            std::fprintf(stderr, "Failed to initialize GLAD\n");

            return false;
        }

        return true;
    }

    void GfxContext::Shutdown()
    {
        SDL_GL_DeleteContext(m_handle);

        m_initialized = false;
        m_handle = nullptr;
    }

    GfxContext::NativeHandle_t GfxContext::GetNativeHandle() const
    {
        return m_handle;
    }
}
