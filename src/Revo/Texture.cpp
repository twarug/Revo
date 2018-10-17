#include <Revo/Texture.hpp>

// Revo
#include <Revo/Image.hpp>

namespace rv
{

Texture::Texture()
    : m_texture { 0 }
    , m_size { 0u, 0u }
{

}

Texture::Texture(Texture&& rhs) noexcept
    : m_texture { rhs.m_texture }
{
    rhs.m_texture = 0;
}

Texture& Texture::operator = (Texture&& rhs) noexcept
{
    if (this != &rhs)
    {
        M_Destroy();

        m_texture = rhs.m_texture;
        rhs.m_texture = 0;
    }

    return *this;
}

Texture::~Texture()
{
    M_Destroy();
}

bool Texture::Create(const glm::uvec2& size, const void* data)
{
    M_Destroy();

    glGenTextures(1, &m_texture);

    Bind(0);

    // TODO have fun with parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    Unbind();

    m_size = size;

    return true;
}

bool Texture::LoadFromFile(const char* path)
{
    Image img;

    if (img.LoadFromFile(path))
    {
        return Create(img.GetSize(), img.GetData());
    }

    return false;
}

glm::uvec2 Texture::GetSize() const
{
    return m_size;
}

bool Texture::IsValid() const
{
    return m_texture;
}

Texture::NativeHandle_t Texture::GetNativeHandle() const
{
    return m_texture;
}

void Texture::M_Destroy()
{
    if (m_texture)
    {
        glDeleteTextures(1, &m_texture);
    }
}

void Texture::Bind(size_t slot)
{
    if (m_texture)
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_texture);
    }
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

}
