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
        Transform& Translate(glm::vec3 const& offset);

        ///
        Transform& Rotate(glm::vec3 const& angle);

        ///
        Transform& Scale(glm::vec3 const& factor);

        ///
        Transform& Inverse();

        ///
        Transform& Combine(Transform const& transform);

        ///
        Transform& Combine(glm::mat4 const& matrix);

        ///
        Transform Translated(glm::vec3 const& offset);

        ///
        Transform Rotated(glm::vec3 const& angle);

        ///
        Transform Scaled(glm::vec3 const& factor);

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
