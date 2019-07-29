#include <Revo/Graphics/RenderTarget.hpp>

// Revo
#include <Revo/Graphics/Camera.hpp>
#include <Revo/Graphics/ShaderProgram.hpp>
#include <Revo/Graphics/Transform.hpp>

namespace rv
{
    void RenderTarget::Clear(Vec4f const& color)
    {
        Bind();

        glClearColor(color.x, color.y, color.z, color.w);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void RenderTarget::PrepareToRender(ShaderProgram const& shaderProgram, Camera const& camera) const
    {
        Bind();

        Mat4x4f mvp = Mat4x4f{ 1.0f };
        mvp *= camera.GetProjectionMatrix(m_size);
        mvp *= camera.GetViewMatrix();

        shaderProgram.UseProgram();
        shaderProgram.SetUniform("mvp", mvp);
    }

    void RenderTarget::PrepareToRender(Transform const& transform, ShaderProgram const& shaderProgram, Camera const& camera) const
    {
        Bind();

        Mat4x4f mvp = Mat4x4f{ 1.0f };
        mvp *= camera.GetProjectionMatrix(m_size);
        mvp *= camera.GetViewMatrix();
        mvp *= transform.GetMatrix();

        shaderProgram.UseProgram();
        shaderProgram.SetUniform("mvp", mvp);
    }

    Vec2u RenderTarget::GetSize() const
    {
        return m_size;
    }
}
