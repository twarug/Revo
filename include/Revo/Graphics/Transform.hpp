#pragma once

// Revo
#include <Revo/Config.hpp>

// glm
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

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
        Transform(ZeroTag);

        ///
        Transform(IdentityTag);

        ///
        Transform(const glm::mat4& matrix);

        ///
        Transform(const Transform&) = default;

        ///
        Transform& operator = (const Transform&) = default;

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
        Transform& Translate(const glm::vec3& offset);

        ///
        Transform& Rotate(const glm::vec3& angle);

        ///
        Transform& Scale(const glm::vec3& factor);

        ///
        Transform& Inverse();

        ///
        Transform& Combine(const Transform& transform);

        ///
        Transform& Combine(const glm::mat4& matrix);

        ///
        Transform Translated(const glm::vec3& offset);

        ///
        Transform Rotated(const glm::vec3& angle);

        ///
        Transform Scaled(const glm::vec3& factor);

        ///
        Transform Inversed();

        ///
        Transform Combined(const Transform& transform);

        ///
        Transform Combined(const glm::mat4& matrix);

        ///
        const glm::mat4& GetMatrix() const;

    private:

        glm::mat4 m_matrix;
    };
}
