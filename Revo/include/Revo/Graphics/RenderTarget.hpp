#pragma once

// Revo
#include <Revo/Graphics/RenderStates.hpp>

// glm
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

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
        void Clear(glm::vec4 const& color = { 0.0f, 0.0f, 0.0f, 0.0f });

        ///
        void Draw(Drawable const& drawable, RenderStates const& states = {});

        ///
        glm::uvec2 GetSize() const;

    protected:

        glm::uvec2 m_size;
    };
}
