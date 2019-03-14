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

    Transformable::Transformable(glm::vec3 const& position, glm::vec3 const& origin, glm::vec3 const& rotation, glm::vec3 const& scale)
        : m_position { position }
        , m_origin { origin }
        , m_rotation { rotation }
        , m_scale { scale }
        , m_transform {}
        , m_needsUpdate { true }
    {
        M_UpdateMatrix();
    }

    void Transformable::SetTransform(glm::vec3 const& position, glm::vec3 const& origin, glm::vec3 const& rotation, glm::vec3 const& scale)
    {
        m_position = position;
        m_origin = origin;
        m_rotation = rotation;
        m_scale = scale;

        m_needsUpdate = true;

        M_UpdateMatrix();
    }

    void Transformable::TranslatePosition(glm::vec3 const& offset)
    {
        m_position += offset;

        m_needsUpdate = true;
    }

    void Transformable::SetPosition(glm::vec3 const& position)
    {
        m_position = position;

        m_needsUpdate = true;
    }

    glm::vec3 const& Transformable::GetPosition() const
    {
        return m_position;
    }

    void Transformable::TranslateOrigin(glm::vec3 const& offset)
    {
        m_origin += offset;

        m_needsUpdate = true;
    }

    void Transformable::SetOrigin(glm::vec3 const& origin)
    {
        m_origin = origin;

        m_needsUpdate = true;
    }

    glm::vec3 const& Transformable::GetOrigin() const
    {
        return m_origin;
    }

    void Transformable::Rotate(glm::vec3 const& angle)
    {
        m_rotation += angle;

        m_needsUpdate = true;
    }

    void Transformable::SetRotation(glm::vec3 const& rotation)
    {
        m_rotation = rotation;

        m_needsUpdate = true;
    }

    glm::vec3 const& Transformable::GetRotation() const
    {
        return m_rotation;
    }

    void Transformable::Scale(glm::vec3 const& factor)
    {
        m_scale *= factor;

        m_needsUpdate = true;
    }

    void Transformable::SetScale(glm::vec3 const& scale)
    {
        m_scale = scale;

        m_needsUpdate = true;
    }

    glm::vec3 const& Transformable::GetScale() const
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
            m_transform.SetIdentity().Translate(m_position).Rotate(m_rotation).Scale(m_scale).Translate(-m_origin);

            m_needsUpdate = false;
        }
    }
}
