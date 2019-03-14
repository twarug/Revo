#pragma once

// Revo
#include <Revo/Graphics/Transformable.hpp>

namespace rv
{
    ///
    class Drawable : public Transformable
    {
    public:

        ///
        Drawable() = default;

        ///
        Drawable(Drawable const&) = default;

        ///
        Drawable& operator = (Drawable const&) = default;

        ///
        Drawable(Drawable&&) = default;

        ///
        Drawable& operator = (Drawable&&) = default;

        ///
        virtual ~Drawable() = default;

        ///
        virtual void Draw() const = 0;
    };
}
