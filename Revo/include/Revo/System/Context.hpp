#pragma once

// Revo
#include <Revo/Core.hpp>

// SDL2
#include <SDL2/SDL.h>

namespace rv
{
    /// Context class to handle backend library initialization
    class Context
    {
    public:

        /// Default ctor
        Context();

        /// Deleted copy-ctor
        Context(Context const&) = delete;

        /// Deleted copy-assign-op
        Context& operator = (Context const&) = delete;

        /// Deleted move-ctor
        Context(Context&&) = delete;

        /// Deleted move-assign-op
        Context& operator = (Context&&) = delete;

        /// Calls Shutdown() upon destruction
        ~Context();

        /// Initializes backend library
        bool Initialize();

        /// Shutdowns backend library
        void Shutdown();

    private:

        bool m_initialized;
    };
}
