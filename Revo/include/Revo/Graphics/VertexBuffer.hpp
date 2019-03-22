#pragma once

// Revo
#include <Revo/Graphics/Backend.hpp>
#include <Revo/Graphics/Drawable.hpp>
#include <Revo/Graphics/PrimitiveType.hpp>
#include <Revo/Graphics/Vertex.hpp>

// C++
#include <vector>

namespace rv
{
    ///
    class VertexBuffer : public Drawable
    {
    public:

        using Vertices_t = std::vector<Vertex>;

        ///
        VertexBuffer() = delete;

        ///
        explicit VertexBuffer(PrimitiveType type = PrimitiveType::Triangles);

        ///
        explicit VertexBuffer(size_t size, PrimitiveType type = PrimitiveType::Triangles);

        ///
        VertexBuffer(size_t size, Vertex const& value, PrimitiveType type = PrimitiveType::Triangles);

        ///
        VertexBuffer(Vertex const* vertices, size_t size, PrimitiveType type = PrimitiveType::Triangles);

        ///
        VertexBuffer(Vertex const* begin, Vertex const* end, PrimitiveType type = PrimitiveType::Triangles);

        ///
        VertexBuffer(VertexBuffer const& rhs);

        ///
        VertexBuffer& operator = (VertexBuffer const& rhs);

        ///
        VertexBuffer(VertexBuffer&& rhs) noexcept;

        ///
        VertexBuffer& operator = (VertexBuffer&& rhs) noexcept;

        ///
        ~VertexBuffer();

        ///
        void Clear();

        ///
        VertexBuffer& Assign(size_t size, PrimitiveType type = PrimitiveType::Triangles);

        ///
        VertexBuffer& Assign(size_t size, Vertex const& value, PrimitiveType type = PrimitiveType::Triangles);

        ///
        VertexBuffer& Assign(Vertex const* vertices, size_t size, PrimitiveType type = PrimitiveType::Triangles);

        ///
        VertexBuffer& Assign(Vertex const* begin, Vertex const* end, PrimitiveType type = PrimitiveType::Triangles);

        ///
        void Resize(size_t size);

        ///
        void Resize(size_t size, Vertex const& value);

        ///
        void SetVertex(size_t index, Vertex const& vertex);

        ///
        Vertex& GetVertex(size_t index);

        ///
        Vertex const& GetVertex(size_t index) const;

        ///
        Vertex& operator [] (size_t index);

        ///
        Vertex const& operator [] (size_t index) const;

        ///
        void SetPrimitiveType(PrimitiveType type);

        ///
        PrimitiveType GetPrimitiveType() const;

        ///
        Vertex* GetData();

        ///
        Vertex const* GetData() const;

        ///
        size_t GetSize() const;

        ///
        size_t GetBytesCount() const;

        ///
        bool IsEmpty() const;

        ///
        bool IsValid() const;

        /// Returns { left, top, width, height } 2D bounds of vertices
        glm::vec4 GetBounds2D() const;

        ///
        void Bind() const;

        ///
        void Unbind() const;

        ///
        virtual void Draw() const override;

    private:

        ///
        void M_Init();

        ///
        void M_Destroy();

        Vertices_t m_vertices;
        PrimitiveType m_type;
        GLuint m_vao;
        GLuint m_vbo;
        mutable size_t m_lowerIndex;
        mutable size_t m_upperIndex;
        mutable bool m_needsUpdate;
        mutable bool m_needsReallocate;
    };
}
