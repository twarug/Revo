#pragma once

// m2
#include <m2/Config.hpp>

// glm
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

namespace rv
{

    ///
    class Transformable
    {
    public:

        ///
        Transformable();

        ///
        Transformable(const glm::vec3& position, const glm::vec3& origin, const glm::vec3& rotation, const glm::vec3& scale);

        ///
        Transformable(const Transformable&) = default;

        ///
        Transformable& operator = (const Transformable&) = default;

        ///
        Transformable(Transformable&& rhs) = default;

        ///
        Transformable& operator = (Transformable&& rhs) = default;

        ///
        ~Transformable() = default;

        ///
        void SetTransform(const glm::vec3& position, const glm::vec3& origin, const glm::vec3& rotation, const glm::vec3& scale);

        ///
        void SetTransform(const glm::mat4& matrix);

        ///
        void SetTransform(const Transformable& transform);

        ///
        void Translate(const glm::vec3& offset);

        ///
        void SetPosition(const glm::vec3& position);

        ///
        glm::vec3 GetPosition() const;

        ///
        void TranslateOrigin(const glm::vec3& offset);

        ///
        void SetOrigin(const glm::vec3& origin);

        ///
        glm::vec3 GetOrigin() const;

        ///
        void Rotate(const glm::vec3& angle);

        ///
        void SetRotation(const glm::vec3& rotation);

        ///
        glm::vec3 GetRotation() const;

        ///
        void Scale(const glm::vec3& factor);

        ///
        void SetScale(const glm::vec3& scale);

        ///
        glm::vec3 GetScale() const;

        ///
        glm::mat4 GetTransform() const;

        ///
        glm::mat4 GetInverseTransform() const;

        #if defined(M2_DEBUG)

        ///
        void D_ShowTransformableEditor(bool* open);

        #endif

    private:

        ///
        void M_UpdateMatrix() const;

        glm::vec3 m_position;
        glm::vec3 m_origin;
        glm::vec3 m_rotation;
        glm::vec3 m_scale;
        mutable glm::mat4 m_matrix;
        mutable bool m_needsUpdate;
    };

}
