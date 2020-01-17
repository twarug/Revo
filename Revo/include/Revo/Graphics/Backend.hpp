#pragma once

#if defined(RV_OPENGL)

// glad TEMPORARY
#include <glad/glad.h>

#endif

// Revo
#include <Revo/Config.hpp>

namespace rv
{
    namespace impl
    {
        ///
        void CreateVao(uint32_t* vao);

        ///
        void DestroyVao(uint32_t vao);

        ///
        void BindVao(uint32_t vao);

        ///
        void CreateVbo(uint32_t* vbo);

        ///
        void DestroyVbo(uint32_t vbo);

        ///
        void BindVbo(uint32_t vbo);

        ///
        void DrawArrays(int32_t type, size_t startIndex, size_t size);

        ///
        void CreateArrayBuffer(void const* data, size_t sizeInBytes);

        ///
        void UpdateArrayBuffer(void const* data, size_t offsetInBytes, size_t sizeInBytes);

        ///
        void SetVertexAtrribPointer(uint32_t vao, size_t index, size_t elemCount, size_t sizeInBytes, void const* offsetPtr);
    }
}
