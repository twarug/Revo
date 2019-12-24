#pragma once

// Revo
#include <Revo/Graphics/3D/Transform3D.hpp>

namespace rv
{
    ///
    class Transformable3D
    {
    public:

        ///
        Transformable3D() noexcept;

        ///
        Transformable3D(Vec3f const& position, Vec3f const& origin, Vec3f const& rotation, Vec3f const& scale) noexcept;

        ///
        Transformable3D(Transformable3D const&) noexcept = default;

        ///
        Transformable3D& operator = (Transformable3D const&) noexcept = default;

        ///
        Transformable3D(Transformable3D&& rhs) noexcept = default;

        ///
        Transformable3D& operator = (Transformable3D&& rhs) noexcept = default;

        ///
        Transformable3D(Transformable3D const&&) = delete;

        ///
        Transformable3D& operator = (Transformable3D const&&) = delete;

        ///
        ~Transformable3D() noexcept = default;

        ///
        void SetTransform(Vec3f const& position, Vec3f const& origin, Vec3f const& rotation, Vec3f const& scale) noexcept;

        ///
        void TranslatePosition(Vec3f const& offset) noexcept;

        ///
        void SetPosition(Vec3f const& position) noexcept;

        ///
        Vec3f const& GetPosition() const noexcept;

        ///
        void TranslateOrigin(Vec3f const& offset) noexcept;

        ///
        void SetOrigin(Vec3f const& origin) noexcept;

        ///
        Vec3f const& GetOrigin() const noexcept;

        ///
        void Rotate(Vec3f const& angle) noexcept;

        ///
        void SetRotation(Vec3f const& rotation) noexcept;

        ///
        Vec3f const& GetRotation() const noexcept;

        ///
        void Scale(Vec3f const& factor) noexcept;

        ///
        void SetScale(Vec3f const& scale) noexcept;

        ///
        Vec3f const& GetScale() const noexcept;

        ///
        Transform3D const& GetTransform() const noexcept;

        ///
        Transform3D GetInverseTransform() const noexcept;

        #if defined(RV_DEBUG)

        ///
        void D_ShowTransformableEditor(bool* open = nullptr);

        #endif

    private:

        ///
        void M_UpdateTransform() const noexcept;

        Vec3f m_position;
        Vec3f m_origin;
        Vec3f m_rotation;
        Vec3f m_scale;
        mutable Transform3D m_cachedTransform;
        mutable bool m_needsUpdate;
    };
}
