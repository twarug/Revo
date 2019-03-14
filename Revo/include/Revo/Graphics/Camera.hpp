#pragma once

// glm
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>

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
        glm::mat4 GetViewMatrix() const;

        ///
        glm::mat4 GetProjectionMatrix(glm::uvec2 const& targetSize) const;

        ///
        ProjectionType GetProjectionType() const;

        #if defined(RV_DEBUG)

        ///
        void D_ShowCameraEditor(bool* open);

        #endif

    private:

        ProjectionType m_projectionType;
        ProjectionUnion m_projection;
        glm::vec3 m_cameraPosition;
        glm::vec3 m_centerPosition;
        glm::vec3 m_upDirection;
    };
}
