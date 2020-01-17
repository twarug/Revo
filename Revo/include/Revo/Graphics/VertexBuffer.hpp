#pragma once

// Revo
#include <Revo/Graphics/PrimitiveType.hpp>
#include <Revo/Graphics/Vertex.hpp>
#include <Revo/Graphics/Camera.hpp>
#include <Revo/Graphics/Window.hpp>
#include <Revo/Graphics/ShaderProgram.hpp>
#include <Revo/Utility/OffsetOf.hpp>

// C++
#include <vector>

namespace rv
{
    ///
    template <typename T>
    class VertexBuffer
    {
    public:

        using Vertex_t   = T;
        using Vertices_t = std::vector<Vertex_t>;

        /// Deleted default constructor
        VertexBuffer() = delete;

        ///
        VertexBuffer(size_t count, Vertex_t const& vertex, PrimitiveType type = PrimitiveType::Triangles);

        ///
        VertexBuffer(Vertex_t const* begin, Vertex_t const* end, PrimitiveType type = PrimitiveType::Triangles);

        ///
        VertexBuffer(Vertex_t const* vertices, size_t count, PrimitiveType type = PrimitiveType::Triangles);

        ///
        VertexBuffer(VertexBuffer const& rhs);

        ///
        VertexBuffer& operator= (VertexBuffer const& rhs);

        ///
        VertexBuffer(VertexBuffer&& rhs) noexcept;

        ///
        VertexBuffer& operator= (VertexBuffer&& rhs) noexcept;

        /// Deleted const move-ctor to prevent move from const object
        VertexBuffer(VertexBuffer const&&) = delete;

        /// Deleted const move-assign-op to prevent move from const object
        VertexBuffer& operator= (VertexBuffer const&&) = delete;

        ///
        ~VertexBuffer();
  
        ///
        void Resize(size_t count, Vertex_t const& vertex);

        ///
        VertexBuffer& Assign(size_t count, Vertex_t const& vertex, PrimitiveType type = PrimitiveType::Triangles);

        ///
        VertexBuffer& Assign(Vertex_t const* begin, Vertex_t const* end, PrimitiveType type = PrimitiveType::Triangles);

        ///
        VertexBuffer& Assign(Vertex_t const* vertices, size_t count, PrimitiveType type = PrimitiveType::Triangles);

        ///
        VertexBuffer& Append(size_t count, Vertex_t const& vertex);

        ///
        VertexBuffer& Append(Vertex_t const* begin, Vertex_t const* end);

        ///
        VertexBuffer& Append(Vertex_t const* vertices, size_t count);

        ///
        Vertex_t& GetVertex(size_t index);

        ///
        Vertex_t const& GetVertex(size_t index) const;

        ///
        void SetVertex(size_t index, Vertex_t const& vertex);

        ///
        Vertex_t& operator[] (size_t index);

        ///
        Vertex_t const& operator[] (size_t index) const;

        ///
        PrimitiveType GetPrimitiveType() const;

        ///
        void SetPrimitiveType(PrimitiveType type);

        ///
        Vertex_t* GetData();

        ///
        Vertex_t const* GetData() const;

        ///
        size_t GetVerticesCount() const;

        ///
        size_t GetBytesCount() const;

        ///
        bool IsEmpty() const;

        ///
        bool IsValid() const;

        ///
        void Bind() const;

        ///
        void Render(Window const& window, ShaderProgram const& shaderProgram, Camera const& camera) const;

        ///
        void Render(Window const& window, ShaderProgram const& shaderProgram, Camera const& camera, Transform3D const& transform) const;

    private:

        static constexpr size_t minIndex = 0;
        static constexpr size_t maxIndex = static_cast<size_t>(-1);

        ///
        void M_Init();

        ///
        void M_Defaultize();

        ///
        void M_Update() const;

        ///
        void M_Destroy();

        Vertices_t m_vertices;
        mutable size_t m_lowerIndex;
        mutable size_t m_upperIndex;
        PrimitiveType m_type;
        uint32_t m_vao;
        uint32_t m_vbo;
        mutable bool m_needsUpdate;
        mutable bool m_needsReallocate;
    };

    template <typename T>
    VertexBuffer<T>::VertexBuffer(size_t count, Vertex_t const& vertex, PrimitiveType type)
        : m_vertices { count, vertex }
        , m_lowerIndex { maxIndex }
        , m_upperIndex { minIndex }
        , m_type { type }
        , m_vao { 0 }
        , m_vbo { 0 }
        , m_needsUpdate { true }
        , m_needsReallocate { true }
    {
        M_Init();
    }

    template <typename T>
    VertexBuffer<T>::VertexBuffer(Vertex_t const* begin, Vertex_t const* end, PrimitiveType type)
        : m_vertices { begin, end }
        , m_lowerIndex { maxIndex }
        , m_upperIndex { minIndex }
        , m_type { type }
        , m_vao { 0 }
        , m_vbo { 0 }
        , m_needsUpdate { true }
        , m_needsReallocate { true }
    {
        M_Init();
    }

    template <typename T>
    VertexBuffer<T>::VertexBuffer(Vertex_t const* vertices, size_t count, PrimitiveType type)
        : VertexBuffer { vertices, vertices + count, type }
    {
        
    }

    template <typename T>
    VertexBuffer<T>::VertexBuffer(VertexBuffer const& rhs)
        : VertexBuffer { rhs.m_vertices.begin(), rhs.m_vertices.end(), rhs.m_type }
    {

    }

    template <typename T>
    VertexBuffer<T>& VertexBuffer<T>::operator= (VertexBuffer const& rhs)
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

    template <typename T>
    VertexBuffer<T>::VertexBuffer(VertexBuffer&& rhs) noexcept
        : m_vertices { std::move(rhs.m_vertices) }
        , m_lowerIndex { rhs.m_lowerIndex }
        , m_upperIndex { rhs.m_upperIndex }
        , m_type { rhs.m_type }
        , m_vao { rhs.m_vao }
        , m_vbo { rhs.m_vbo }
        , m_needsUpdate { rhs.m_needsUpdate }
        , m_needsReallocate { rhs.m_needsReallocate }
    {
        rhs.M_Defaultize();
    }

    template <typename T>
    VertexBuffer<T>& VertexBuffer<T>::operator= (VertexBuffer&& rhs) noexcept
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

            rhs.M_Defaultize();
        }

        return *this;
    }

    template <typename T>
    VertexBuffer<T>::~VertexBuffer()
    {
        if (IsValid())
        {
            impl::DestroyVao(m_vao);
            impl::DestroyVbo(m_vbo);
        }
    }

    template <typename T>
    void VertexBuffer<T>::Resize(size_t count, Vertex_t const& vertex)
    {
        if (GetVerticesCount() != count)
        {
            m_lowerIndex = minIndex;
            m_upperIndex = count - 1;

            m_needsUpdate = true;
            m_needsReallocate = m_vertices.capacity() < count;

            m_vertices.resize(count, vertex);
        }
    }

    template <typename T>
    VertexBuffer<T>& VertexBuffer<T>::Assign(size_t count, Vertex_t const& vertex, PrimitiveType type)
    {
        if (count != 0)
        {
            m_lowerIndex = minIndex;
            m_upperIndex = count - 1;

            m_needsUpdate = true;
            m_needsReallocate = m_vertices.capacity() < count;

            m_vertices.assign(count, vertex);
            m_type = type;
        }

        return *this;
    }

    template <typename T>
    VertexBuffer<T>& VertexBuffer<T>::Assign(Vertex_t const* begin, Vertex_t const* end, PrimitiveType type)
    {
        auto const distance = end - begin;

        if (distance > 0)
        {
            m_lowerIndex = minIndex;
            m_upperIndex = distance - 1;

            m_needsUpdate = true;
            m_needsReallocate = m_vertices.capacity() < static_cast<size_t>(distance);

            m_vertices.assign(begin, end);
            m_type = type;
        }

        return *this;
    }

    template <typename T>
    VertexBuffer<T>& VertexBuffer<T>::Assign(Vertex_t const* vertices, size_t count, PrimitiveType type)
    {
        return Assign(vertices, vertices + count, type);
    }

    template <typename T>
    typename VertexBuffer<T>::Vertex_t& VertexBuffer<T>::GetVertex(size_t index)
    {
        m_lowerIndex = std::min(m_lowerIndex, index);
        m_upperIndex = std::max(m_upperIndex, index);

        m_needsUpdate = true;

        return m_vertices[index];
    }

    template <typename T>
    typename VertexBuffer<T>::Vertex_t const& VertexBuffer<T>::GetVertex(size_t index) const
    {
        return m_vertices[index];
    }

    template <typename T>
    void VertexBuffer<T>::SetVertex(size_t index, Vertex_t const& vertex)
    {
        GetVertex(index) = vertex;
    }

    template <typename T>
    typename VertexBuffer<T>::Vertex_t& VertexBuffer<T>::operator[] (size_t index)
    {
        return GetVertex(index);
    }

    template <typename T>
    typename VertexBuffer<T>::Vertex_t const& VertexBuffer<T>::operator[] (size_t index) const
    {
        return GetVertex(index);
    }

    template <typename T>
    PrimitiveType VertexBuffer<T>::GetPrimitiveType() const
    {
        return m_type;
    }

    template <typename T>
    void VertexBuffer<T>::SetPrimitiveType(PrimitiveType type)
    {
        m_type = type;
    }

    template <typename T>
    typename VertexBuffer<T>::Vertex_t* VertexBuffer<T>::GetData()
    {
        m_lowerIndex = minIndex;
        m_upperIndex = GetVerticesCount() - 1;

        m_needsUpdate = true;

        return m_vertices.empty() ? nullptr : m_vertices.data();
    }

    template <typename T>
    typename VertexBuffer<T>::Vertex_t const* VertexBuffer<T>::GetData() const
    {
        return m_vertices.empty() ? nullptr : m_vertices.data();
    }

    template <typename T>
    size_t VertexBuffer<T>::GetVerticesCount() const
    {
        return m_vertices.size();
    }

    template <typename T>
    size_t VertexBuffer<T>::GetBytesCount() const
    {
        return m_vertices.size() * sizeof(Vertex_t);
    }

    template <typename T>
    bool VertexBuffer<T>::IsEmpty() const
    {
        return m_vertices.empty();
    }

    template <typename T>
    bool VertexBuffer<T>::IsValid() const
    {
        return m_vao && m_vbo;
    }

    template <typename T>
    void VertexBuffer<T>::Bind() const
    {
        if (IsValid())
        {
            impl::BindVao(m_vao);
            impl::BindVbo(m_vbo);
        }
    }

    template <typename T>
    void VertexBuffer<T>::Render(Window const& window, ShaderProgram const& shaderProgram, Camera const& camera) const
    {
        if (!IsEmpty() && IsValid())
        {
            window.PrepareToRender(shaderProgram, camera);

            Bind();

            M_Update();

            impl::DrawArrays(impl::GetNativeHandle(m_type), 0, GetVerticesCount());
        }
    }

    template <typename T>
    void VertexBuffer<T>::Render(Window const& window, ShaderProgram const& shaderProgram, Camera const& camera, Transform3D const& transform) const
    {
        if (!IsEmpty() && IsValid())
        {
            window.PrepareToRender(shaderProgram, camera, transform);

            Bind();

            M_Update();

            impl::DrawArrays(impl::GetNativeHandle(m_type), 0, GetVerticesCount());
        }
    }

    template <typename T>
    void VertexBuffer<T>::M_Init()
    {
        impl::CreateVao(&m_vao);
        impl::CreateVbo(&m_vbo);

        Bind();

        impl::SetVertexAtrribPointer(m_vao, 0, decltype(Vertex_t::position)::length(), sizeof(Vertex_t), OffsetPtrOf(&Vertex_t::position));

        impl::SetVertexAtrribPointer(m_vao, 1, decltype(Vertex_t::color)::length(), sizeof(Vertex_t), OffsetPtrOf(&Vertex_t::color));

        impl::SetVertexAtrribPointer(m_vao, 2, decltype(Vertex_t::texCoord)::length(), sizeof(Vertex_t), OffsetPtrOf(&Vertex_t::texCoord));
    }

    template <typename T>
    void VertexBuffer<T>::M_Defaultize()
    {
        m_lowerIndex = maxIndex;
        m_upperIndex = minIndex;
        m_vao = 0;
        m_vbo = 0;
        m_needsUpdate = true;
        m_needsReallocate = true;
    }

    template <typename T>
    void VertexBuffer<T>::M_Destroy()
    {
        impl::DestroyVao(m_vao);
        impl::DestroyVbo(m_vbo);

        M_Defaultize();
    }
    
    template <typename T>
    void VertexBuffer<T>::M_Update() const
    {
        if (m_needsUpdate)
        {
            if (m_needsReallocate)
            {
                impl::CreateArrayBuffer(GetData(), GetBytesCount());

                m_needsReallocate = false;
            }
            else
            {
                auto const offset = sizeof(Vertex_t) * m_lowerIndex;
                auto const size = sizeof(Vertex_t) * (m_upperIndex - m_lowerIndex + 1);

                impl::UpdateArrayBuffer(GetData() + m_lowerIndex, offset, size);
            }

            m_lowerIndex = maxIndex;
            m_upperIndex = minIndex;

            m_needsUpdate = false;
        }
    }
}
