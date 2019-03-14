#pragma once

// Revo
#include <Revo/Graphics/Backend.hpp>

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
        Texture(Texture const&) = delete;

        ///
        Texture& operator = (Texture const&) = delete;

        ///
        Texture(Texture&& rhs) noexcept;

        ///
        Texture& operator = (Texture&& rhs) noexcept;

        ///
        ~Texture();

        ///
        bool Create(glm::uvec2 const& size, void const* data = nullptr);

        ///
        bool LoadFromFile(char const* path);

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
