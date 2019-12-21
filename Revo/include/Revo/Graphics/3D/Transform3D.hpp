#pragma once

// Revo
#include <Revo/Math/Matrix.hpp>
#include <Revo/Math/Vector.hpp>

namespace rv
{
    ///
    class Transform3D
    {
    public:

        ///
        Transform3D() noexcept = default;

        ///
        explicit Transform3D(float value) noexcept;

        ///
        explicit Transform3D(Mat4x4f const& matrix) noexcept;

        ///
        Transform3D(Transform3D const&) noexcept = default;

        ///
        Transform3D& operator = (Transform3D const&) noexcept = default;

        ///
        Transform3D(Transform3D&& rhs) noexcept = default;

        ///
        Transform3D& operator = (Transform3D&& rhs) noexcept = default;

        ///
        Transform3D(Transform3D const&&) = delete;

        ///
        Transform3D& operator = (Transform3D const&&) = delete;

        ///
        ~Transform3D() noexcept = default;

        ///
        Transform3D& SetZero() noexcept;

        ///
        Transform3D& SetIdentity() noexcept;

        ///
        Transform3D& SetMatrix(Mat4x4f const& matrix) noexcept;

        ///
        Transform3D& Translate(Vec3f const& offset) noexcept;

        ///
        Transform3D& Rotate(Vec3f const& angle) noexcept;

        ///
        Transform3D& Scale(Vec3f const& factor) noexcept;

        ///
        Transform3D& Inverse() noexcept;

        ///
        Transform3D& Combine(Transform3D const& transform) noexcept;

        ///
        Transform3D& Combine(Mat4x4f const& matrix) noexcept;

        ///
        Transform3D Translated(Vec3f const& offset) noexcept;

        ///
        Transform3D Rotated(Vec3f const& angle) noexcept;

        ///
        Transform3D Scaled(Vec3f const& factor) noexcept;

        ///
        Transform3D Inversed() noexcept;

        ///
        Transform3D Combined(Transform3D const& transform) noexcept;

        ///
        Transform3D Combined(Mat4x4f const& matrix) noexcept;

        ///
        Mat4x4f const& GetMatrix() const noexcept;

    private:

        Mat4x4f m_matrix;
    };
}
