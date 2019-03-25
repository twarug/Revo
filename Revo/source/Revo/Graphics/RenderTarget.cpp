#include <Revo/Graphics/RenderTarget.hpp>

// Revo
#include <Revo/Graphics/Camera.hpp>
#include <Revo/Graphics/Drawable.hpp>
#include <Revo/Graphics/ShaderProgram.hpp>

namespace rv
{
    void RenderTarget::Clear(Vec4f const& color)
    {
        Bind();

        glClearColor(color.x, color.y, color.z, color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RenderTarget::Draw(Drawable const& drawable, RenderStates const& states)
    {
        if (states.shaderProgram && states.camera)
        {
            Bind();

            Mat4x4f mvp = Mat4x4f{ 1.0f };
            mvp *= states.camera->GetProjectionMatrix(m_size);
            mvp *= states.camera->GetViewMatrix();
            mvp *= drawable.GetTransform().GetMatrix();

            states.shaderProgram->UseProgram();
            states.shaderProgram->SetUniform("mvp", mvp);

            drawable.Draw();
        }
    }

    Vec2u RenderTarget::GetSize() const
    {
        return m_size;
    }
}
