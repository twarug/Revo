#include <Revo/Graphics/Image.hpp>

// stb
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

namespace rv
{
    Image::Image()
        : m_pixels {}
        , m_size { 0, 0 }
        , m_channels { 0 }
    {

    }

    Image::Image(Image&& rhs) noexcept
        : m_pixels { std::move(rhs.m_pixels) }
        , m_size { rhs.m_size }
        , m_channels { rhs.m_channels }
    {
        rhs.m_size = { 0, 0 };
        rhs.m_channels = 0;
    }

    Image& Image::operator = (Image&& rhs) noexcept
    {
        if (this != &rhs)
        {
            m_pixels = std::move(rhs.m_pixels);
            m_size = rhs.m_size;
            m_channels = rhs.m_channels;

            rhs.m_size = { 0, 0 };
            rhs.m_channels = 0;
        }

        return *this;
    }

    bool Image::LoadFromFile(char const* path)
    {
        int w;
        int h;
        int bpp;

        Byte_t* ptr = stbi_load(path, &w, &h, &bpp, STBI_rgb_alpha);

        if (ptr)
        {
            m_size = { w, h };
            m_channels = bpp;

            m_pixels.assign(ptr, ptr + (m_size.x * m_size.y * 4));

            stbi_image_free(ptr);

            return true;
        }

        return false;
    }

    bool Image::SaveToFile(char const* path, ImgExtType extension, bool flipVertically) const
    {
        stbi_flip_vertically_on_write(flipVertically);

        if (!m_pixels.empty())
        {
            switch (extension)
            {
                case ImgExtType::PNG: return stbi_write_png(path, m_size.x, m_size.y, m_channels, m_pixels.data(), 0);
                case ImgExtType::BMP: return stbi_write_bmp(path, m_size.x, m_size.y, m_channels, m_pixels.data());
                case ImgExtType::TGA: return stbi_write_tga(path, m_size.x, m_size.y, m_channels, m_pixels.data());
                case ImgExtType::JPG: return stbi_write_jpg(path, m_size.x, m_size.y, m_channels, m_pixels.data(), 90);
                // TODO implement HDR when vendor of stb will fix crash
            }
        }

        return false;
    }

    void Image::FlipVertically()
    {
        if (!m_pixels.empty())
        {
            size_t const rowSize = m_size.x * 4;

            auto top    = m_pixels.begin();
            auto bottom = m_pixels.end() - rowSize;

            for (size_t y = 0; y < m_size.y / 2; ++y)
            {
                std::swap_ranges(top, top + rowSize, bottom);

                top += rowSize;
                bottom -= rowSize;
            }
        }
    }

    void Image::FlipHorizontally()
    {
        if (!m_pixels.empty())
        {
            size_t const rowSize = m_size.x * 4;

            for (size_t y = 0; y < m_size.y; ++y)
            {
                auto left  = m_pixels.begin() + y * rowSize;
                auto right = m_pixels.begin() + (y + 1) * rowSize - 4;

                for (size_t x = 0; x < m_size.x / 2; ++x)
                {
                    std::swap_ranges(left, left + 4, right);

                    left += 4;
                    right -= 4;
                }
            }
        }
    }

    Image::Byte_t* Image::GetData()
    {
        return m_pixels.data();
    }

    Image::Byte_t const* Image::GetData() const
    {
        return m_pixels.data();
    }

    Vec2u Image::GetSize() const
    {
        return m_size;
    }

    size_t Image::GetPixelsCount() const
    {
        return m_size.x * m_size.y;
    }

    size_t Image::GetChannelsCount() const
    {
        return m_channels;
    }

    bool Image::IsEmpty() const
    {
        return m_pixels.empty();
    }
}
