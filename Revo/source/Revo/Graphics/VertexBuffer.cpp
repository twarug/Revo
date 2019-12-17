#include <Revo/Graphics/VertexBuffer.hpp>

// Revo
#include <Revo/Graphics/Camera.hpp>
#include <Revo/Graphics/Window.hpp>
#include <Revo/Graphics/ShaderProgram.hpp>
#include <Revo/Utility/OffsetOf.hpp>

namespace rv
{
    inline constexpr size_t minIndex = 0;
    inline constexpr size_t maxIndex = static_cast<size_t>(-1);

    VertexBuffer::VertexBuffer(PrimitiveType type)
        : m_vertices {}
        , m_lowerIndex { maxIndex }
        , m_upperIndex { minIndex }
        , m_type { type }
        , m_vao { 0 }
        , m_vbo { 0 }
        , m_needsUpdate { false }
        , m_needsReallocate { false }
    {
        M_Init();
    }

    VertexBuffer::VertexBuffer(size_t size, PrimitiveType type)
        : m_vertices { size, Vertex_t{} }
        , m_lowerIndex { maxIndex }
        , m_upperIndex { minIndex }
        , m_type { type }
        , m_vao { 0 }
        , m_vbo { 0 }
        , m_needsUpdate { false }
        , m_needsReallocate { false }
    {
        M_Init();
    }

    VertexBuffer::VertexBuffer(size_t size, Vertex_t const& vertex, PrimitiveType type)
        : m_vertices { size, vertex }
        , m_lowerIndex { maxIndex }
        , m_upperIndex { minIndex }
        , m_type { type }
        , m_vao { 0 }
        , m_vbo { 0 }
        , m_needsUpdate { false }
        , m_needsReallocate { false }
    {
        M_Init();
    }

    VertexBuffer::VertexBuffer(Vertex_t const* vertices, size_t size, PrimitiveType type)
        : m_vertices { vertices, vertices + size }
        , m_lowerIndex { maxIndex }
        , m_upperIndex { minIndex }
        , m_type { type }
        , m_vao { 0 }
        , m_vbo { 0 }
        , m_needsUpdate { false }
        , m_needsReallocate { false }
    {
        M_Init();
    }

    VertexBuffer::VertexBuffer(Vertex_t const* begin, Vertex_t const* end, PrimitiveType type)
        : m_vertices { begin, end }
        , m_lowerIndex { maxIndex }
        , m_upperIndex { minIndex }
        , m_type { type }
        , m_vao { 0 }
        , m_vbo { 0 }
        , m_needsUpdate { false }
        , m_needsReallocate { false }
    {
        M_Init();
    }

    VertexBuffer::VertexBuffer(VertexBuffer const& rhs)
        : VertexBuffer { rhs.m_vertices.data(), rhs.m_vertices.size(), rhs.m_type }
    {

    }

    VertexBuffer& VertexBuffer::operator = (VertexBuffer const& rhs)
    {
        if (this != &rhs)
        {
            M_Destroy();

            m_vertices = rhs.m_vertices;
            m_type = rhs.m_type;

            M_Init();
        }

        return *this;
    }

    VertexBuffer::VertexBuffer(VertexBuffer&& rhs) noexcept
        : m_vertices { std::move(rhs.m_vertices) }
        , m_lowerIndex { rhs.m_lowerIndex }
        , m_upperIndex { rhs.m_upperIndex }
        , m_type { rhs.m_type }
        , m_vao { rhs.m_vao }
        , m_vbo { rhs.m_vbo }
        , m_needsUpdate { rhs.m_needsUpdate }
        , m_needsReallocate { rhs.m_needsReallocate }
    {
        rhs.m_vao = 0;
        rhs.m_vbo = 0;
        rhs.m_lowerIndex = maxIndex;
        rhs.m_upperIndex = minIndex;
        rhs.m_needsUpdate = false;
        rhs.m_needsReallocate = false;
    }

    VertexBuffer& VertexBuffer::operator = (VertexBuffer&& rhs) noexcept
    {
        if (this != &rhs)
        {
            M_Destroy();

            m_vertices = std::move(rhs.m_vertices);
            m_lowerIndex = rhs.m_lowerIndex;
            m_upperIndex = rhs.m_upperIndex;
            m_type = rhs.m_type;
            m_vao = rhs.m_vao;
            m_vbo = rhs.m_vbo;
            m_needsUpdate = rhs.m_needsUpdate;
            m_needsReallocate = rhs.m_needsReallocate;

            rhs.m_lowerIndex = maxIndex;
            rhs.m_upperIndex = minIndex;
            rhs.m_vao = 0;
            rhs.m_vbo = 0;
            rhs.m_needsReallocate = false;
            rhs.m_needsUpdate = false;
        }

        return *this;
    }

    VertexBuffer::~VertexBuffer()
    {
        M_Destroy();
    }

    void VertexBuffer::Clear()
    {
        m_vertices.clear();
    }

    VertexBuffer& VertexBuffer::Assign(size_t size, PrimitiveType type)
    {
        if (size != 0)
        {
            m_needsUpdate = true;
            m_needsReallocate = m_vertices.capacity() < size;

            m_lowerIndex = minIndex;
            m_upperIndex = size - 1;

            m_vertices.assign(size, Vertex_t{});
            m_type = type;
        }

        return *this;
    }

    VertexBuffer& VertexBuffer::Assign(size_t size, Vertex_t const& vertex, PrimitiveType type)
    {
        if (size != 0)
        {
            m_needsUpdate = true;
            m_needsReallocate = m_vertices.capacity() < size;

            m_lowerIndex = minIndex;
            m_upperIndex = size - 1;

            m_vertices.assign(size, vertex);
            m_type = type;
        }

        return *this;
    }

    VertexBuffer& VertexBuffer::Assign(Vertex_t const* vertices, size_t size, PrimitiveType type)
    {
        if (size != 0)
        {
            m_needsUpdate = true;
            m_needsReallocate = m_vertices.capacity() < size;

            m_lowerIndex = minIndex;
            m_upperIndex = size - 1;

            m_vertices.assign(vertices, vertices + size);
            m_type = type;
        }

        return *this;
    }

    VertexBuffer& VertexBuffer::Assign(Vertex_t const* begin, Vertex_t const* end, PrimitiveType type)
    {
        auto const distance = end - begin;

        if (distance > 0)
        {
            m_needsUpdate = true;
            m_needsReallocate = m_vertices.capacity() < static_cast<size_t>(distance);

            m_lowerIndex = minIndex;
            m_upperIndex = distance - 1;

            m_vertices.assign(begin, end);
            m_type = type;
        }

        return *this;
    }

    void VertexBuffer::Resize(size_t size)
    {
        if (m_vertices.size() != size)
        {
            m_needsUpdate = true;
            m_needsReallocate = m_vertices.capacity() < size;

            m_lowerIndex = minIndex;
            m_upperIndex = size - 1;

            m_vertices.resize(size);
        }
    }

    void VertexBuffer::Resize(size_t size, Vertex_t const& vertex)
    {
        if (m_vertices.size() != size)
        {
            m_needsUpdate = true;
            m_needsReallocate = m_vertices.capacity() < size;

            m_lowerIndex = minIndex;
            m_upperIndex = size - 1;

            m_vertices.resize(size, vertex);
        }
    }

    void VertexBuffer::SetVertex(size_t index, Vertex_t const& vertex)
    {
        m_vertices[index] = vertex;

        m_lowerIndex = std::min(m_lowerIndex, index);
        m_upperIndex = std::max(m_upperIndex, index);

        m_needsUpdate = true;
    }

    VertexBuffer::Vertex_t &VertexBuffer::GetVertex(size_t index)
    {
        m_lowerIndex = std::min(m_lowerIndex, index);
        m_upperIndex = std::max(m_upperIndex, index);

        m_needsUpdate = true;

        return m_vertices[index];
    }

    VertexBuffer::Vertex_t const &VertexBuffer::GetVertex(size_t index) const
    {
        return m_vertices[index];
    }

    VertexBuffer::Vertex_t &VertexBuffer::operator[](size_t index)
    {
        return GetVertex(index);
    }

    VertexBuffer::Vertex_t const &VertexBuffer::operator[](size_t index) const
    {
        return GetVertex(index);
    }

    void VertexBuffer::SetPrimitiveType(PrimitiveType type)
    {
        m_type = type;
    }

    PrimitiveType VertexBuffer::GetPrimitiveType() const
    {
        return m_type;
    }

    VertexBuffer::Vertex_t *VertexBuffer::GetData()
    {
        m_needsUpdate = true;

        m_lowerIndex = minIndex;
        m_upperIndex = m_vertices.size() - 1;

        return m_vertices.empty() ? nullptr : m_vertices.data();
    }

    VertexBuffer::Vertex_t const *VertexBuffer::GetData() const
    {
        return m_vertices.empty() ? nullptr : m_vertices.data();
    }

    size_t VertexBuffer::GetSize() const
    {
        return m_vertices.size();
    }

    size_t VertexBuffer::GetBytesCount() const
    {
        return m_vertices.size() * sizeof(Vertex_t);
    }

    bool VertexBuffer::IsEmpty() const
    {
        return m_vertices.empty();
    }

    bool VertexBuffer::IsValid() const
    {
        return m_vao && m_vbo;
    }

    Vec4f VertexBuffer::GetBounds2D() const
    {
        if (!m_vertices.empty())
        {
            auto left   = m_vertices[0].position.x;
            auto top    = m_vertices[0].position.y;
            auto right  = m_vertices[0].position.x;
            auto bottom = m_vertices[0].position.y;

            for (size_t i = 1; i < m_vertices.size(); ++i)
            {
                auto const pos = m_vertices[i].position;

                if (pos.x < left)
                {
                    left = pos.x;
                }
                else if (pos.x > right)
                {
                    right = pos.x;
                }

                if (pos.y < top)
                {
                    top = pos.y;
                }
                else if (pos.y > bottom)
                {
                    bottom = pos.y;
                }
            }

            return { left, top, right - left, bottom - top };
        }
        else
        {
            return { 0.0f, 0.0f, 0.0f, 0.0f };
        }
    }

    void VertexBuffer::Bind() const
    {
        if (m_vao && m_vbo)
        {
            glBindVertexArray(m_vao);
            glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        }
    }

    void VertexBuffer::Unbind() const
    {
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void VertexBuffer::Update() const
    {
        if (m_needsUpdate)
        {
            if (m_needsReallocate)
            {
                glBufferData(GL_ARRAY_BUFFER, GetBytesCount(), GetData(), GL_DYNAMIC_DRAW);

                m_needsReallocate = false;
            }
            else
            {
                GLintptr const offset = sizeof(Vertex_t) * m_lowerIndex;
                GLsizeiptr const size = sizeof(Vertex_t) * (m_upperIndex - m_lowerIndex + 1);

                glBufferSubData(GL_ARRAY_BUFFER, offset, size, GetData() + m_lowerIndex);
            }

            m_lowerIndex = maxIndex;
            m_upperIndex = minIndex;

            m_needsUpdate = false;
        }
    }

    void VertexBuffer::Render(Window const& window, ShaderProgram const& shaderProgram, Camera const& camera, Transform const& transform) const
    {
        if (!m_vertices.empty() && m_vao && m_vbo)
        {
            window.PrepareToRender(shaderProgram, camera, transform);

            Bind();

            Update();

            glDrawArrays(impl::GetNativeHandle(m_type), 0, m_vertices.size());

            Unbind();
        }
    }

    void VertexBuffer::M_Init()
    {
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);

        Bind();

        glBufferData(GL_ARRAY_BUFFER, GetBytesCount(), std::as_const(*this).GetData(), GL_DYNAMIC_DRAW);

        // TODO do only once
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, decltype(Vertex_t::position)::length(), GL_FLOAT, GL_FALSE, sizeof(Vertex_t), OffsetPtrOf(&Vertex_t::position));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, decltype(Vertex_t::color)::length(), GL_FLOAT, GL_FALSE, sizeof(Vertex_t), OffsetPtrOf(&Vertex_t::color));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, decltype(Vertex_t::texCoord)::length(), GL_FLOAT, GL_FALSE, sizeof(Vertex_t), OffsetPtrOf(&Vertex_t::texCoord));

        Unbind();
    }

    void VertexBuffer::M_Destroy()
    {
        Clear();

        glDeleteVertexArrays(1, &m_vao);
        glDeleteBuffers(1, &m_vbo);

        m_lowerIndex = maxIndex;
        m_upperIndex = minIndex;

        m_needsUpdate = false;
        m_needsReallocate = false;
    }
}
