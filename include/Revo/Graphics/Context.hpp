#pragma once

// Revo
#include <Revo/Graphics/OpenGL.hpp>

// GLFW
#include <GLFW/glfw3.h>

namespace rv
{
    ///
    class Context
    {
    public:

        ///
        Context() = default;

        ///
        Context(const Context&) = delete;

        ///
        Context& operator = (const Context&) = delete;

        ///
        Context(Context&&) = delete;

        ///
        Context& operator = (Context&&) = delete;

        ///
        ~Context();

        ///
        bool Create();

    private:

        bool m_initialized = false;
    };
}
