#include <Revo/Context.hpp>

// C++
#include <cstdio>

namespace rv
{

    Context::~Context()
    {
        if (m_initialized)
        {
            glfwTerminate();

            m_initialized = false;
        }
    }

    bool Context::Create()
    {
        glfwSetErrorCallback([](int error, const char* description) {
            std::fprintf(stderr, "Error %d: %s\n", error, description); // TODO better logging
        });

        return m_initialized = glfwInit();
    }

}
