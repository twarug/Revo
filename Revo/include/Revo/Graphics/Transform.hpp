#pragma once

// Revo
#include <Revo/Utility/Matrix.hpp>
#include <Revo/Utility/Vector.hpp>

namespace rv
{
    ///
    class Transform
    {
    public:

        ///
        struct ZeroTag {};

        ///
        struct IdentityTag {};

        ///
        Transform() = default;

        ///
        explicit Transform(ZeroTag);

        ///
        explicit Transform(IdentityTag);

        ///
        explicit Transform(glm::mat4 const& matrix);

        ///
        Transform(Transform const&) = default;

        ///
        Transform& operator = (Transform const&) = default;

        ///
        Transform(Transform&& rhs) = default;

        ///
        Transform& operator = (Transform&& rhs) = default;

        ///
        ~Transform() = default;

        ///
        Transform& SetZero();

        ///
        Transform& SetIdentity();

        ///
        Transform& Translate(Vec3f const& offset);

        ///
        Transform& Rotate(Vec3f const& angle);

        ///
        Transform& Scale(Vec3f const& factor);

        ///
        Transform& Inverse();

        ///
        Transform& Combine(Transform const& transform);

        ///
        Transform& Combine(glm::mat4 const& matrix);

        ///
        Transform Translated(Vec3f const& offset);

        ///
        Transform Rotated(Vec3f const& angle);

        ///
        Transform Scaled(Vec3f const& factor);

        ///
        Transform Inversed();

        ///
        Transform Combined(Transform const& transform);

        ///
        Transform Combined(glm::mat4 const& matrix);

        ///
        glm::mat4 const& GetMatrix() const;

    private:

        glm::mat4 m_matrix;
    };
}
