#pragma once

// Revo
#include <Revo/System/Context.hpp>

// glad
#include <glad/glad.h>

namespace rv
{
    // FWD
    class Window;

    ///
    class GfxContext
    {
    public:

        using NativeHandle_t = SDL_GLContext;

        ///
        GfxContext();

        ///
        GfxContext(const GfxContext&) = delete;

        ///
        GfxContext& operator = (const GfxContext&) = delete;

        ///
        GfxContext(GfxContext&&) = delete;

        ///
        GfxContext& operator = (GfxContext&&) = delete;

        ///
        ~GfxContext();

        ///
        bool Initialize(Window const& window);

        ///
        void Shutdown();

        ///
        NativeHandle_t GetNativeHandle() const;

    private:

        bool m_initialized;
        NativeHandle_t m_handle;
    };
}
