#pragma once

// Revo
#include <Revo/Graphics/Backend.hpp>
#include <Revo/Graphics/PrimitiveType.hpp>
#include <Revo/Graphics/Vertex.hpp>
#include <Revo/Graphics/Transformable.hpp>

// C++
#include <vector>

namespace rv
{
    // FWD
    class Camera;
    class RenderTexture;
    class ShaderProgram;
    class Window;

    ///
    class VertexBuffer : public Transformable
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
        Vec4f GetBounds2D() const;

        ///
        void Bind() const;

        ///
        void Unbind() const;

        ///
        void Render(Window const& window, ShaderProgram const& shaderProgram, Camera const& camera) const;

    private:

        ///
        void M_Init();

        ///
        void M_Destroy();

        ///
        void M_Render() const;

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
