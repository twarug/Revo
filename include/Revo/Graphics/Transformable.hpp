#pragma once

// Revo
#include <Revo/Graphics/Transform.hpp>

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
        void TranslatePosition(const glm::vec3& offset);

        ///
        void SetPosition(const glm::vec3& position);

        ///
        const glm::vec3& GetPosition() const;

        ///
        void TranslateOrigin(const glm::vec3& offset);

        ///
        void SetOrigin(const glm::vec3& origin);

        ///
        const glm::vec3& GetOrigin() const;

        ///
        void Rotate(const glm::vec3& angle);

        ///
        void SetRotation(const glm::vec3& rotation);

        ///
        const glm::vec3& GetRotation() const;

        ///
        void Scale(const glm::vec3& factor);

        ///
        void SetScale(const glm::vec3& scale);

        ///
        const glm::vec3& GetScale() const;

        ///
        Transform GetTransform() const;

        ///
        Transform GetInverseTransform() const;

    public:

        #if defined(RV_DEBUG)

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
        mutable Transform m_transform;
        mutable bool m_needsUpdate;
    };
}
