#pragma once

#include <tuple>

namespace yaschperitsy::core::input
{

enum class MOUSE_BUTTON
{
    left,
    middle,
    right
};

class Input
{
    public:
        static bool is_key_pressed(int keycode);
        static std::tuple<int, int> mouse_position();
        static bool is_mouse_button_pressed(MOUSE_BUTTON mouse_button);
};

}; // namespace yaschperitsy::core::input
