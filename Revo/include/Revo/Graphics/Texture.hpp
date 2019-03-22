#pragma once

// Revo
#include <Revo/Graphics/Backend.hpp>
#include <Revo/Utility/Vector.hpp>

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
        bool Create(Vec2u const& size, void const* data = nullptr);

        ///
        bool LoadFromFile(char const* path);

        ///
        Vec2u GetSize() const;

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
        Vec2u m_size;
    };

}
