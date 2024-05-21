#include "keyboard_controller.h"

void KeyboardController::handle_key_down(SDL_KeyboardEvent* event)
{
    if (event->repeat == 0 &&
        event->keysym.scancode < MAX_KEYBOARD_KEYS)
    {
        _keyboard->operator[](event->keysym.scancode) = 1;
    }
}

void KeyboardController::handle_key_up(SDL_KeyboardEvent* event)
{
    if (event->repeat == 0 &&
        event->keysym.scancode < MAX_KEYBOARD_KEYS)
    {
        _keyboard->operator[](event->keysym.scancode) = 0;
    }
}

bool KeyboardController::handle_input()
{
    while (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
        case SDL_QUIT:
            return true;
            break;

        case SDL_KEYDOWN:
            handle_key_down(&event.key);
            break;

        case SDL_KEYUP:
            handle_key_up(&event.key);
            break;

        default:
            break;
        }
    }
    return false;
}
