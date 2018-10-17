#pragma once

// m2
#include <m2/Config.hpp>

// SFML
#include <SFML/Window/Mouse.hpp>

namespace rv
{

namespace io
{

struct Mouse
{
    enum Code_e
    {
        Left     = sf::Mouse::Left,
        Middle   = sf::Mouse::Middle,
        Right    = sf::Mouse::Right,
        XButton1 = sf::Mouse::XButton1,
        XButton2 = sf::Mouse::XButton2,

        Count    = sf::Mouse::ButtonCount
    };

};

}

}
