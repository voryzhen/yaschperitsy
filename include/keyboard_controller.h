#pragma once

#include "array"

#include "SDL.h"

static constexpr int MAX_KEYBOARD_KEYS{350};

class KeyboardController
{
    public:
        KeyboardController(std::array<int, MAX_KEYBOARD_KEYS>* keyboard)
            : _keyboard(keyboard)
        {
        }

        bool handle_input();

    private:
        void handle_key_down(SDL_KeyboardEvent* event);
        void handle_key_up(SDL_KeyboardEvent* event);

        SDL_Event event{};
        std::array<int, MAX_KEYBOARD_KEYS>* _keyboard;
};