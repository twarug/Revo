#pragma once

// Revo
#include <Revo/Config.hpp>

#if defined(RV_OPENGL)

// glad
#include <glad/glad.h>

#if defined(RV_DEBUG)
#   define RV_GFX_CALL(__f, ...) rv::impl::GfxCall(RV_HERE, #__f, __f, __VA_ARGS__)
#else
#   define RV_GFX_CALL(__f, ...) __f(__VA_ARGS__)
#endif

#endif
