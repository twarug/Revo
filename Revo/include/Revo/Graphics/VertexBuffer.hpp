#pragma once

// Revo
#include <Revo/Graphics/PrimitiveType.hpp>
#include <Revo/Graphics/Vertex.hpp>

// C++
#include <vector>

namespace rv
{
    // FWD
    class Camera;
    class RenderTexture;
    class ShaderProgram;
    class Transform;
    class Window;

    ///
    class VertexBuffer
    {
    public:

        using Vertex_t   = Vertex;
        using Vertices_t = std::vector<Vertex_t>;

        ///
        VertexBuffer() = delete;

        ///
        explicit VertexBuffer(PrimitiveType type = PrimitiveType::Triangles);

        ///
        explicit VertexBuffer(size_t size, PrimitiveType type = PrimitiveType::Triangles);

        ///
        VertexBuffer(size_t size, Vertex_t const& vertex, PrimitiveType type = PrimitiveType::Triangles);

        ///
        VertexBuffer(Vertex_t const* vertices, size_t size, PrimitiveType type = PrimitiveType::Triangles);

        ///
        VertexBuffer(Vertex_t const* begin, Vertex_t const* end, PrimitiveType type = PrimitiveType::Triangles);

        ///
        VertexBuffer(VertexBuffer const& rhs);

        ///
        VertexBuffer& operator = (VertexBuffer const& rhs);

        ///
        VertexBuffer(VertexBuffer&& rhs) noexcept;

        ///
        VertexBuffer& operator = (VertexBuffer&& rhs) noexcept;

        ///
        VertexBuffer(VertexBuffer const&&) = delete;

        ///
        VertexBuffer& operator = (VertexBuffer const&&) = delete;

        ///
        ~VertexBuffer();

        ///
        void Clear();

        ///
        VertexBuffer& Assign(size_t size, PrimitiveType type = PrimitiveType::Triangles);

        ///
        VertexBuffer& Assign(size_t size, Vertex_t const& vertex, PrimitiveType type = PrimitiveType::Triangles);

        ///
        VertexBuffer& Assign(Vertex_t const* vertices, size_t size, PrimitiveType type = PrimitiveType::Triangles);

        ///
        VertexBuffer& Assign(Vertex_t const* begin, Vertex_t const* end, PrimitiveType type = PrimitiveType::Triangles);

        ///
        void Resize(size_t size);

        ///
        void Resize(size_t size, Vertex_t const& vertex);

        ///
        void SetVertex(size_t index, Vertex_t const& vertex);

        ///
        Vertex_t& GetVertex(size_t index);

        ///
        Vertex_t const& GetVertex(size_t index) const;

        ///
        Vertex_t& operator [] (size_t index);

        ///
        Vertex_t const& operator [] (size_t index) const;

        ///
        void SetPrimitiveType(PrimitiveType type);

        ///
        PrimitiveType GetPrimitiveType() const;

        ///
        Vertex_t* GetData();

        ///
        Vertex_t const* GetData() const;

        ///
        size_t GetSize() const;

        ///
        size_t GetBytesCount() const;

        ///
        bool IsEmpty() const;

        ///
        bool IsValid() const;

        /// Returns { left, top, width, height } 2D bounds of vertices
        Vec4f GetBounds2D() const;

        ///
        void Bind() const;

        ///
        void Unbind() const;

        ///
        void Update() const;

        ///
        void Render(Window const& window, ShaderProgram const& shaderProgram, Camera const& camera, Transform const& transform) const;

    private:

        ///
        void M_Init();

        ///
        void M_Destroy();

        Vertices_t m_vertices;
        PrimitiveType m_type;
        uint32_t m_vao;
        uint32_t m_vbo;
        mutable size_t m_lowerIndex;
        mutable size_t m_upperIndex;
        mutable bool m_needsUpdate;
        mutable bool m_needsReallocate;
    };
}
