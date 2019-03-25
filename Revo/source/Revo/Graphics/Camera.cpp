#include <Revo/Graphics/Camera.hpp>

// Revo
#include <Revo/ImGui/ImGuiContext.hpp>

// C++
#include <string>

// glm
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace rv
{
    Camera::Camera(OrthographicProjection const& orthographic)
        : m_projectionType { ProjectionType::Orthographic }
        , m_projection { orthographic }
        , m_cameraPosition { 0.0f, 0.0f, 1.0f }
        , m_centerPosition { 0.0f, 0.0f, 0.0f }
        , m_upDirection { 0.0f, 1.0f, 0.0f }
    {

    }

    Camera::Camera(PerspectiveProjection const& perspective)
        : m_projectionType { ProjectionType::Perspective }
        , m_projection { perspective }
        , m_cameraPosition { 0.0f, 0.0f, 1.0f }
        , m_centerPosition { 0.0f, 0.0f, 0.0f }
        , m_upDirection { 0.0f, 1.0f, 0.0f }
    {

    }

    Mat4x4f Camera::GetViewMatrix() const
    {
        switch (m_projectionType)
        {
            case ProjectionType::Orthographic: return Mat4x4f{ 1.0f };
            case ProjectionType::Perspective: return glm::lookAt(m_cameraPosition, m_centerPosition, m_upDirection);
        }

        return Mat4x4f{ 1.0f };
    }

    Mat4x4f Camera::GetProjectionMatrix(Vec2u const& targetSize) const
    {
        switch (m_projectionType)
        {
            case ProjectionType::Orthographic: return glm::ortho(0.0f, (float)targetSize.x, 0.0f, (float)targetSize.y, -1.0f, 1.0f);
            case ProjectionType::Perspective: return glm::perspectiveFov(glm::radians(45.0f), (float)targetSize.x, (float)targetSize.y, 0.1f, 100.0f);
        }

        return Mat4x4f{ 1.0f };
    }

    ProjectionType Camera::GetProjectionType() const
    {
        return m_projectionType;
    }

    #if defined(RV_DEBUG)

    void Camera::D_ShowCameraEditor(bool* open)
    {
        if (ImGui::Begin(("Camera editor " + std::to_string((size_t)this)).data(), open))
        {
            if (ImGui::DragFloat3("m_cameraPosition", glm::value_ptr(m_cameraPosition), 0.01f) |
                ImGui::DragFloat3("m_centerPosition", glm::value_ptr(m_centerPosition), 0.01f) |
                ImGui::DragFloat3("m_upDirection", glm::value_ptr(m_upDirection), 0.01f))
            {

            }
        }
        ImGui::End();
    }

    #endif
}
