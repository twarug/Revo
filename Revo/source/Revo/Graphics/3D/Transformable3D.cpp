#include <Revo/Graphics/3D/Transformable3D.hpp>

// Revo
#include <Revo/ImGui/ImGuiContext.hpp>

// C++
#include <string>

// glm
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/type_ptr.hpp>

namespace rv
{
    Transformable3D::Transformable3D() noexcept
        : m_position { 0.0f, 0.0f, 0.0f }
        , m_origin { 0.0f, 0.0f, 0.0f }
        , m_rotation { 0.0f, 0.0f, 0.0f }
        , m_scale { 1.0f, 1.0f, 1.0f }
        , m_transform { 1.0f }
        , m_needsUpdate { false }
    {

    }

    Transformable3D::Transformable3D(Vec3f const& position, Vec3f const& origin, Vec3f const& rotation, Vec3f const& scale) noexcept
        : m_position { position }
        , m_origin { origin }
        , m_rotation { rotation }
        , m_scale { scale }
        , m_transform {}
        , m_needsUpdate { true }
    {
        M_UpdateTransform();
    }

    void Transformable3D::SetTransform(Vec3f const& position, Vec3f const& origin, Vec3f const& rotation, Vec3f const& scale) noexcept
    {
        m_position = position;
        m_origin = origin;
        m_rotation = rotation;
        m_scale = scale;

        m_needsUpdate = true;

        M_UpdateTransform();
    }

    void Transformable3D::TranslatePosition(Vec3f const& offset) noexcept
    {
        m_position += offset;

        m_needsUpdate = true;
    }

    void Transformable3D::SetPosition(Vec3f const& position)  noexcept
    {
        m_position = position;

        m_needsUpdate = true;
    }

    Vec3f const& Transformable3D::GetPosition() const noexcept
    {
        return m_position;
    }

    void Transformable3D::TranslateOrigin(Vec3f const& offset) noexcept
    {
        m_origin += offset;

        m_needsUpdate = true;
    }

    void Transformable3D::SetOrigin(Vec3f const& origin) noexcept
    {
        m_origin = origin;

        m_needsUpdate = true;
    }

    Vec3f const& Transformable3D::GetOrigin() const noexcept
    {
        return m_origin;
    }

    void Transformable3D::Rotate(Vec3f const& angle) noexcept
    {
        m_rotation += angle;

        m_needsUpdate = true;
    }

    void Transformable3D::SetRotation(Vec3f const& rotation) noexcept
    {
        m_rotation = rotation;

        m_needsUpdate = true;
    }

    Vec3f const& Transformable3D::GetRotation() const noexcept
    {
        return m_rotation;
    }

    void Transformable3D::Scale(Vec3f const& factor) noexcept
    {
        m_scale *= factor;

        m_needsUpdate = true;
    }

    void Transformable3D::SetScale(Vec3f const& scale) noexcept
    {
        m_scale = scale;

        m_needsUpdate = true;
    }

    Vec3f const& Transformable3D::GetScale() const noexcept
    {
        return m_scale;
    }

    Transform3D const& Transformable3D::GetTransform() const noexcept
    {
        M_UpdateTransform();

        return m_transform;
    }

    Transform3D Transformable3D::GetInverseTransform() const noexcept
    {
        M_UpdateTransform();

        return m_transform.Inversed();
    }

    #if defined(RV_DEBUG)

    void Transformable3D::D_ShowTransformableEditor(bool* open)
    {
        if (ImGui::Begin(("Transformable3D editor " + std::to_string((size_t)this)).data(), open))
        {
            if (ImGui::DragFloat3("position", glm::value_ptr(m_position), 0.01f) |
                ImGui::DragFloat3("origin", glm::value_ptr(m_origin), 0.01f) |
                ImGui::DragFloat3("rotation", glm::value_ptr(m_rotation), 0.01f) |
                ImGui::DragFloat3("scale", glm::value_ptr(m_scale), 0.01f))
            {
                m_needsUpdate = true;
            }
        }
        ImGui::End();
    }

    #endif

    void Transformable3D::M_UpdateTransform() const noexcept
    {
        if (m_needsUpdate)
        {
            m_transform
                .SetIdentity()
                .Translate(m_position)
                .Rotate(m_rotation)
                .Scale(m_scale)
                .Translate(-m_origin);

            m_needsUpdate = false;
        }
    }
}
