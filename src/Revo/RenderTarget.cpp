#include <Revo/RenderTarget.hpp>

// Revo
#include <Revo/Camera.hpp>
#include <Revo/Drawable.hpp>
#include <Revo/ShaderProgram.hpp>

namespace rv
{

    void RenderTarget::Clear(const glm::vec4& color)
    {
        Bind();

        glClearColor(color.x, color.y, color.z, color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RenderTarget::Draw(const Drawable& drawable, const RenderStates& states)
    {
        if (states.shaderProgram && states.camera)
        {
            Bind();

            glm::mat4 mvp = glm::mat4{ 1.0f };
            mvp *= states.camera->GetProjectionMatrix(m_size);
            mvp *= states.camera->GetViewMatrix();
            mvp *= drawable.GetTransform();

            states.shaderProgram->UseProgram();
            states.shaderProgram->SetUniform("mvp", mvp);

            drawable.Draw();
        }
    }

    glm::uvec2 RenderTarget::GetSize() const
    {
        return m_size;
    }

}
