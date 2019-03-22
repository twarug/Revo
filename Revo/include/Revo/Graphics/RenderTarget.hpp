#pragma once

// Revo
#include <Revo/Graphics/RenderStates.hpp>
#include <Revo/Utility/Vector.hpp>

namespace rv
{
    // FWD
    class Drawable;

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
        void Draw(Drawable const& drawable, RenderStates const& states = {});

        ///
        Vec2u GetSize() const;

    protected:

        Vec2u m_size;
    };
}
