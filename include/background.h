#pragma once

#include <resource_manager.h>
#include <vector>

#include "SDL_render.h"
#include "game_parameters.h"

using renderer_type =
    std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)>;

class Background
{
    public:
        Background(Texture background, const GameField& game_field)
            : _background(background), _game_field(game_field)
        {
        }

        Texture get_texture() { return _background; }

        void render(const renderer_type& renderer)
        {
            SDL_Rect dest = {0, 0, _game_field.w, _game_field.h};
            SDL_RenderCopy(renderer.get(), _background._texture, NULL,
                           &dest);
            // make explosions
        }

    private:
        Texture _background{nullptr};
        GameField _game_field;
};
