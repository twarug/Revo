#pragma once

// Revo
#include <Revo/Config.hpp>

// C++
#include <vector>

// glm
#include <glm/vec2.hpp>

namespace rv
{
    ///
    enum class ImgExtType : int32_t
    {
        PNG,
        BMP,
        TGA,
        JPG,
        HDR
    };

    ///
    class Image
    {
    public:

        using Byte_t         = uint8_t;
        using PixelsHolder_t = std::vector<Byte_t>;

        ///
        Image() = default;

        ///
        Image(const Image&) = default;

        ///
        Image& operator = (const Image&) = default;

        ///
        Image(Image&&) = default;

        ///
        Image& operator = (Image&&) = default;

        ///
        ~Image() = default;

        ///
        bool LoadFromFile(const char* path);

        ///
        bool SaveToFile(const char* path, ImgExtType extension, bool flipVertically = false) const;

        ///
        void FlipVertically();

        ///
        void FlipHorizontally();

        ///
        Byte_t* GetData();

        ///
        const Byte_t* GetData() const;

        ///
        glm::uvec2 GetSize() const;

        ///
        size_t GetPixelsCount() const;

        ///
        size_t GetChannelsCount() const;

        ///
        bool IsEmpty() const;

    private:

        PixelsHolder_t m_pixels;
        glm::uvec2 m_size;
        size_t m_channels;
    };
}
