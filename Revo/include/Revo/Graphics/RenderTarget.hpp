#pragma once

// Revo
#include <Revo/Math/Vector.hpp>

namespace rv
{
    // FWD
    class Camera;
    class Drawable;
    class ShaderProgram;

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
        virtual void Bind() const = 0;

        ///
        void Clear(Vec4f const& color = { 0.0f, 0.0f, 0.0f, 0.0f });

        ///
        void Draw(Drawable const& drawable, ShaderProgram const& shaderProgram, Camera const& camera);

        ///
        Vec2u GetSize() const;

    protected:

        Vec2u m_size;
    };
}
