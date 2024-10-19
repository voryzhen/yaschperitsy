#pragma once

#include "Utility/Vector.hpp"
#include <cstdint>

enum class MOUSE_BUTTON : uint8_t
{
    Left = 0,
    Middle,
    Right
};

enum class KEYS : uint8_t
{
    A = 4,
    D = 7,
    S = 22,
    W = 26,

    F = 9,

    Right = 79,
    Left = 80,
    Down = 81,
    Up = 82
};

class Input
{
    public:
        static bool is_key_pressed(KEYS keycode);
        static Vector2D<float> mouse_position();
        static bool is_mouse_button_pressed(MOUSE_BUTTON mouse_button);
};
