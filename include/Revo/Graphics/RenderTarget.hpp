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
        RenderTarget(const RenderTarget&) = default;

        ///
        RenderTarget& operator = (const RenderTarget&) = default;

        ///
        RenderTarget(RenderTarget&&) = default;

        ///
        RenderTarget& operator = (RenderTarget&&) = default;

        ///
        ~RenderTarget() = default;

        ///
        virtual void Bind() const = 0;

        ///
        void Clear(const glm::vec4& color = { 0.0f, 0.0f, 0.0f, 0.0f });

        ///
        void Draw(const Drawable& drawable, const RenderStates& states = {});

        ///
        glm::uvec2 GetSize() const;

    protected:

        glm::uvec2 m_size;
    };
}
