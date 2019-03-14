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
        Transformable(glm::vec3 const& position, glm::vec3 const& origin, glm::vec3 const& rotation, glm::vec3 const& scale);

        ///
        Transformable(Transformable const&) = default;

        ///
        Transformable& operator = (Transformable const&) = default;

        ///
        Transformable(Transformable&& rhs) = default;

        ///
        Transformable& operator = (Transformable&& rhs) = default;

        ///
        ~Transformable() = default;

        ///
        void SetTransform(glm::vec3 const& position, glm::vec3 const& origin, glm::vec3 const& rotation, glm::vec3 const& scale);

        ///
        void TranslatePosition(glm::vec3 const& offset);

        ///
        void SetPosition(glm::vec3 const& position);

        ///
        glm::vec3 const& GetPosition() const;

        ///
        void TranslateOrigin(glm::vec3 const& offset);

        ///
        void SetOrigin(glm::vec3 const& origin);

        ///
        glm::vec3 const& GetOrigin() const;

        ///
        void Rotate(glm::vec3 const& angle);

        ///
        void SetRotation(glm::vec3 const& rotation);

        ///
        glm::vec3 const& GetRotation() const;

        ///
        void Scale(glm::vec3 const& factor);

        ///
        void SetScale(glm::vec3 const& scale);

        ///
        glm::vec3 const& GetScale() const;

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
