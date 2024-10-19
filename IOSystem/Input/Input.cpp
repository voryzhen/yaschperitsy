#include "Input.hpp"

#include <SDL_scancode.h>
#include <iterator>

#include "SDL_keyboard.h"
#include "SDL_mouse.h"
#include "Utility/Vector.hpp"

bool Input::is_key_pressed(KEYS keycode)
{
    int numkeys = 1;
    const Uint8* keyboard_state = SDL_GetKeyboardState(&numkeys);
    return *std::next(keyboard_state, static_cast<int>(keycode)) != 0u;
}

Vector2D<float> Input::mouse_position()
{
    int x_pos = 0;
    int y_pos = 0;
    SDL_GetMouseState(&x_pos, &y_pos);
    return { .x = static_cast<float>(x_pos), .y = static_cast<float>(y_pos) };
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
