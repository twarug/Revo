#pragma once

// Revo
#include <Revo/Math/Vector.hpp>

// C++
#include <vector>

namespace rv
{
    ///
    enum class ImgExtType : int32_t
    {
        BMP,
        HDR,
        JPG,
        PNG,
        TGA
    };

    ///
    class Image
    {
    public:

        using Byte_t  = uint8_t;
        using Bytes_t = std::vector<Byte_t>;

        ///
        Image();

        ///
        Image(Image const&) = default;

        ///
        Image& operator = (Image const&) = default;

        ///
        Image(Image&& rhs) noexcept;

        ///
        Image& operator = (Image&& rhs) noexcept;

        ///
        Image(Image const&&) = delete;

        ///
        Image& operator = (Image const&&) = delete;

        ///
        ~Image() = default;

        ///
        bool LoadFromFile(char const* filePath);

        ///
        bool SaveToFile(char const* filePath, ImgExtType extension, bool flipVertically = false) const;

        ///
        void FlipVertically();

        ///
        void FlipHorizontally();

        ///
        Byte_t* GetData();

        ///
        Byte_t const* GetData() const;

        ///
        Vec2u GetSize() const;

        ///
        size_t GetPixelsCount() const;

        ///
        uint32_t GetChannelsCount() const;

        ///
        bool IsEmpty() const;

    private:

        Bytes_t m_pixels;
        Vec2u m_size;
        uint32_t m_channels;
    };
}
