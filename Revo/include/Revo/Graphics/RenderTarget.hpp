#pragma once

// Revo
#include <Revo/Math/Vector.hpp>

namespace rv
{
    // FWD
    class Camera;
    class ShaderProgram;
    class Transform;

    ///
    class RenderTarget
    {
    public:

        ///
        RenderTarget() = default;

        ///
        RenderTarget(RenderTarget const&) = default;

        ///
        RenderTarget& operator = (RenderTarget const&) = default;

        ///
        RenderTarget(RenderTarget&&) = default;

        ///
        RenderTarget& operator = (RenderTarget&&) = default;

        ///
        ~RenderTarget() = default;

        ///
        void Clear(Vec4f const& color = { 0.0f, 0.0f, 0.0f, 0.0f });

        ///
        void PrepareToRender(ShaderProgram const& shaderProgram, Camera const& camera) const;

        ///
        void PrepareToRender(Transform const& transform, ShaderProgram const& shaderProgram, Camera const& camera) const;

        ///
        Vec2u GetSize() const;

    protected:

        Vec2u m_size;
    };
}
