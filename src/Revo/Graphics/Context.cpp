#include <Revo/Graphics/Context.hpp>

namespace rv
{
    Context::~Context()
    {
        if (m_initialized)
        {
            SDL_Quit();

            m_initialized = false;
        }
    }

    bool Context::Create()
    {
        m_initialized = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) == 0;

        return m_initialized;
    }
}
