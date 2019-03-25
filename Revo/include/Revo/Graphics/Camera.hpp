#pragma once

// Revo
#include <Revo/Utility/Matrix.hpp>
#include <Revo/Utility/Vector.hpp>

namespace rv
{
    // FWD
    class RenderTarget;

    ///
    struct OrthographicProjection {};

    ///
    struct PerspectiveProjection {};

    ///
    enum class ProjectionType : int32_t
    {
        Orthographic,
        Perspective
    };

    ///
    union ProjectionUnion
    {
        ///
        ProjectionUnion(OrthographicProjection const& orthographic)
            : orthographic { orthographic }
        {

        }

        ///
        ProjectionUnion(PerspectiveProjection const& perspective)
            : perspective { perspective }
        {

        }

        OrthographicProjection orthographic;
        PerspectiveProjection perspective;
    };

    ///
    class Camera
    {
    public:

        ///
        Camera(OrthographicProjection const& orthographic);

        ///
        Camera(PerspectiveProjection const& perspective);

        ///
        Camera(Camera const&) = delete;

        ///
        Camera& operator = (Camera const&) = delete;

        ///
        Camera(Camera&&) = delete;

        ///
        Camera& operator = (Camera&&) = delete;

        ///
        ~Camera() = default;

        ///
        Mat4x4f GetViewMatrix() const;

        ///
        Mat4x4f GetProjectionMatrix(Vec2u const& targetSize) const;

        ///
        ProjectionType GetProjectionType() const;

        #if defined(RV_DEBUG)

        ///
        void D_ShowCameraEditor(bool* open);

        #endif

    private:

        ProjectionType m_projectionType;
        ProjectionUnion m_projection;
        Vec3f m_cameraPosition;
        Vec3f m_centerPosition;
        Vec3f m_upDirection;
    };
}
