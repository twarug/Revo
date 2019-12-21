#include <Revo/Graphics/3D/Transform3D.hpp>

// glm
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>

namespace rv
{
    Transform3D::Transform3D(float value) noexcept
        : m_matrix { value }
    {

    }

    Transform3D::Transform3D(Mat4x4f const& matrix) noexcept
        : m_matrix { matrix }
    {

    }

    Transform3D& Transform3D::SetZero() noexcept
    {
        m_matrix = Mat4x4f{ 0.0f };

        return *this;
    }

    Transform3D& Transform3D::SetIdentity() noexcept
    {
        m_matrix = Mat4x4f{ 1.0f };

        return *this;
    }

    Transform3D& Transform3D::SetMatrix(Mat4x4f const& matrix) noexcept
    {
        m_matrix = matrix;

        return *this;
    }

    Transform3D& Transform3D::Translate(Vec3f const& offset) noexcept
    {
        m_matrix = glm::translate(m_matrix, offset);

        return *this;
    }

    Transform3D& Transform3D::Rotate(Vec3f const& angle) noexcept
    {
        // TODO remove possible gimbal lock
        m_matrix = glm::rotate(m_matrix, angle.x, { 1.0f, 0.0f, 0.0f });
        m_matrix = glm::rotate(m_matrix, angle.y, { 0.0f, 1.0f, 0.0f });
        m_matrix = glm::rotate(m_matrix, angle.z, { 0.0f, 0.0f, 1.0f });

        return *this;
    }

    Transform3D& Transform3D::Scale(Vec3f const& factor) noexcept
    {
        m_matrix = glm::scale(m_matrix, factor);

        return *this;
    }

    Transform3D& Transform3D::Inverse() noexcept
    {
        m_matrix = glm::inverse(m_matrix);

        return *this;
    }

    Transform3D& Transform3D::Combine(Transform3D const& transform) noexcept
    {
        m_matrix *= transform.GetMatrix();

        return *this;
    }

    Transform3D& Transform3D::Combine(Mat4x4f const& matrix) noexcept
    {
        m_matrix *= matrix;

        return *this;
    }

    Transform3D Transform3D::Translated(Vec3f const& offset) noexcept
    {
        return Transform3D{ *this }.Translate(offset);
    }

    Transform3D Transform3D::Scaled(Vec3f const& factor) noexcept
    {
        return Transform3D{ *this }.Scale(factor);
    }

    Transform3D Transform3D::Rotated(Vec3f const& angle) noexcept
    {
        return Transform3D{ *this }.Rotate(angle);
    }

    Transform3D Transform3D::Inversed() noexcept
    {
        return Transform3D{ *this }.Inverse();
    }

    Transform3D Transform3D::Combined(Transform3D const& transform) noexcept
    {
        return Transform3D{ *this }.Combine(transform);
    }

    Transform3D Transform3D::Combined(Mat4x4f const& matrix) noexcept
    {
        return Transform3D{ *this }.Combine(matrix);
    }

    Mat4x4f const& Transform3D::GetMatrix() const noexcept
    {
        return m_matrix;
    }
}
