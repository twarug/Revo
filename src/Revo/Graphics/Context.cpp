#include <Revo/Graphics/Context.hpp>

// C++
#include <cstdio>

namespace rv
{
    Context::~Context()
    {
        if (m_initialized)
        {
            // glfwTerminate();
            SDL_Quit();

            m_initialized = false;
        }
    }

    bool Context::Create()
    {
        // glfwSetErrorCallback([](int error, const char* description) {
        //     // TODO better logging
        //     std::fprintf(stderr, "Error %d: %s\n", error, description);
        // });
        //
        // return m_initialized = glfwInit();

        return m_initialized = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) == 0;
    }
}
