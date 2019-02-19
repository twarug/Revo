#pragma once

// Revo
#include <Revo/Graphics/GfxContext.hpp>

// glm
#include <glm/vec2.hpp>

namespace rv
{

    ///
    class Texture
    {
    public:

        using NativeHandle_t = GLuint;

        ///
        Texture();

        ///
        Texture(const Texture&) = delete;

        ///
        Texture& operator = (const Texture&) = delete;

        ///
        Texture(Texture&& rhs) noexcept;

        ///
        Texture& operator = (Texture&& rhs) noexcept;

        ///
        ~Texture();

        ///
        bool Create(const glm::uvec2& size, const void* data = nullptr);

        ///
        bool LoadFromFile(const char* path);

        ///
        glm::uvec2 GetSize() const;

        ///
        bool IsValid() const;

        ///
        NativeHandle_t GetNativeHandle() const;

        ///
        void Bind(size_t slot);

        ///
        void Unbind();

    private:

        ///
        void M_Destroy();

        NativeHandle_t m_texture;
        glm::uvec2 m_size;
    };

}
