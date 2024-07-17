#include "Input.hpp"

#include <iterator>
#include <tuple>

#include <core/Logger.hpp>

#include "SDL_keyboard.h"
#include "SDL_mouse.h"

namespace yaschperitsy::core::input
{

bool Input::is_key_pressed(int keycode)
{
    int numkeys = 1;

    const Uint8* keyboard_state = SDL_GetKeyboardState(&numkeys);

    return *std::next(keyboard_state, keycode) != 0u;
}

std::tuple<int, int> Input::mouse_position()
{
    int x = 0;
    int y = 0;
    SDL_GetMouseState(&x, &y);
    return std::tie(x, y);
}

bool Input::is_mouse_button_pressed(MOUSE_BUTTON mouse_button)
{
    int x = 0;
    int y = 0;
    Uint32 button = SDL_GetMouseState(&x, &y);
    unsigned char btn_mask = 1;
    btn_mask <<= static_cast<unsigned int>(mouse_button);
    return (button & btn_mask) != 0u;
}

}; // namespace yaschperitsy::core::input
