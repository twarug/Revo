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
        ProjectionUnion(const OrthographicProjection& orthographic)
            : orthographic { orthographic }
        {

        }

        ///
        ProjectionUnion(const PerspectiveProjection& perspective)
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
        Camera(const OrthographicProjection& orthographic);

        ///
        Camera(const PerspectiveProjection& perspective);

        ///
        Camera(const Camera&) = delete;

        ///
        Camera& operator = (const Camera&) = delete;

        ///
        Camera(Camera&&) = delete;

        ///
        Camera& operator = (Camera&&) = delete;

        ///
        ~Camera() = default;

        ///
        glm::mat4 GetViewMatrix() const;

        ///
        glm::mat4 GetProjectionMatrix(const glm::uvec2& targetSize) const;

        ///
        ProjectionType GetProjectionType() const;

        #if defined(M2_DEBUG)

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
