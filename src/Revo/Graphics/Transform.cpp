#include <Revo/Graphics/Transform.hpp>

// glm
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

namespace rv
{
    Transform::Transform(ZeroTag)
        : m_matrix {}
    {

    }

    Transform::Transform(IdentityTag)
        : m_matrix { 1.0f }
    {

    }

    Transform::Transform(const glm::mat4& matrix)
        : m_matrix { matrix }
    {

    }

    Transform& Transform::SetZero()
    {
        m_matrix = glm::mat4{};

        return *this;
    }

    Transform& Transform::SetIdentity()
    {
        m_matrix = glm::mat4{ 1.0f };

        return *this;
    }

    Transform& Transform::Translate(const glm::vec3& offset)
    {
        m_matrix = glm::translate(m_matrix, offset);

        return *this;
    }

    Transform& Transform::Rotate(const glm::vec3& angle)
    {
        // TODO remove possible gimbal lock
        m_matrix = glm::rotate(m_matrix, angle.x, { 1.0f, 0.0f, 0.0f });
        m_matrix = glm::rotate(m_matrix, angle.y, { 0.0f, 1.0f, 0.0f });
        m_matrix = glm::rotate(m_matrix, angle.z, { 0.0f, 0.0f, 1.0f });

        return *this;
    }

    Transform& Transform::Scale(const glm::vec3& factor)
    {
        m_matrix = glm::scale(m_matrix, factor);

        return *this;
    }

    Transform& Transform::Inverse()
    {
        m_matrix = glm::inverse(m_matrix);

        return *this;
    }

    Transform& Transform::Combine(const Transform& transform)
    {
        m_matrix *= transform.GetMatrix();

        return *this;
    }

    Transform& Transform::Combine(const glm::mat4& matrix)
    {
        m_matrix *= matrix;

        return *this;
    }

    Transform Transform::Translated(const glm::vec3& offset)
    {
        return Transform{ *this }.Translate(offset);
    }

    Transform Transform::Scaled(const glm::vec3& factor)
    {
        return Transform{ *this }.Scale(factor);
    }

    Transform Transform::Rotated(const glm::vec3& angle)
    {
        return Transform{ *this }.Rotate(angle);
    }

    Transform Transform::Inversed()
    {
        return Transform{ *this }.Inverse();
    }

    Transform Transform::Combined(const Transform& transform)
    {
        return Transform{ *this }.Combine(transform);
    }

    Transform Transform::Combined(const glm::mat4& matrix)
    {
        return Transform{ *this }.Combine(matrix);
    }

    const glm::mat4& Transform::GetMatrix() const
    {
        return m_matrix;
    }
}
