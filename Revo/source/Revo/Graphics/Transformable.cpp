#include <Revo/Graphics/Transformable.hpp>

// Revo
#include <Revo/ImGui/ImGuiContext.hpp>

// C++
#include <string>

// glm
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/type_ptr.hpp>

namespace rv
{
    Transformable::Transformable()
        : m_position { 0.0f, 0.0f, 0.0f }
        , m_origin { 0.0f, 0.0f, 0.0f }
        , m_rotation { 0.0f, 0.0f, 0.0f }
        , m_scale { 1.0f, 1.0f, 1.0f }
        , m_transform { Transform::IdentityTag{} }
        , m_needsUpdate { false }
    {

    }

    Transformable::Transformable(Vec3f const& position, Vec3f const& origin, Vec3f const& rotation, Vec3f const& scale)
        : m_position { position }
        , m_origin { origin }
        , m_rotation { rotation }
        , m_scale { scale }
        , m_transform {}
        , m_needsUpdate { true }
    {
        M_UpdateMatrix();
    }

    void Transformable::SetTransform(Vec3f const& position, Vec3f const& origin, Vec3f const& rotation, Vec3f const& scale)
    {
        m_position = position;
        m_origin = origin;
        m_rotation = rotation;
        m_scale = scale;

        m_needsUpdate = true;

        M_UpdateMatrix();
    }

    void Transformable::TranslatePosition(Vec3f const& offset)
    {
        m_position += offset;

        m_needsUpdate = true;
    }

    void Transformable::SetPosition(Vec3f const& position)
    {
        m_position = position;

        m_needsUpdate = true;
    }

    Vec3f const& Transformable::GetPosition() const
    {
        return m_position;
    }

    void Transformable::TranslateOrigin(Vec3f const& offset)
    {
        m_origin += offset;

        m_needsUpdate = true;
    }

    void Transformable::SetOrigin(Vec3f const& origin)
    {
        m_origin = origin;

        m_needsUpdate = true;
    }

    Vec3f const& Transformable::GetOrigin() const
    {
        return m_origin;
    }

    void Transformable::Rotate(Vec3f const& angle)
    {
        m_rotation += angle;

        m_needsUpdate = true;
    }

    void Transformable::SetRotation(Vec3f const& rotation)
    {
        m_rotation = rotation;

        m_needsUpdate = true;
    }

    Vec3f const& Transformable::GetRotation() const
    {
        return m_rotation;
    }

    void Transformable::Scale(Vec3f const& factor)
    {
        m_scale *= factor;

        m_needsUpdate = true;
    }

    void Transformable::SetScale(Vec3f const& scale)
    {
        m_scale = scale;

        m_needsUpdate = true;
    }

    Vec3f const& Transformable::GetScale() const
    {
        return m_scale;
    }

    Transform Transformable::GetTransform() const
    {
        M_UpdateMatrix();

        return m_transform;
    }

    Transform Transformable::GetInverseTransform() const
    {
        M_UpdateMatrix();

        return m_transform.Inversed();
    }

    #if defined(RV_DEBUG)

    void Transformable::D_ShowTransformableEditor(bool* open)
    {
        if (ImGui::Begin(("Transformable editor " + std::to_string((size_t)this)).data(), open))
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

    void Transformable::M_UpdateMatrix() const
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
