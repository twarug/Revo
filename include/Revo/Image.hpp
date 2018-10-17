#pragma once

// m2
#include <m2/Config.hpp>

// C++
#include <vector>

// glm
#include <glm/vec2.hpp>

namespace rv
{

class Image
{
public:

    using Byte_t         = uint8_t;
    using PixelsHolder_t = std::vector<Byte_t>;

    enum ExtensionType
    {
        PNG,
        BMP,
        TGA,
        JPG,
        HDR
    };

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
    bool SaveToFile(const char* path, ExtensionType extension) const;

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
