#pragma once

// Revo
#include <Revo/Transformable.hpp>

namespace rv
{

    ///
    class Drawable : public Transformable
    {
    public:

        ///
        Drawable() = default;

        ///
        Drawable(const Drawable&) = default;

        ///
        Drawable& operator = (const Drawable&) = default;

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
