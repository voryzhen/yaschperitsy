#pragma once

#include <memory>
#include <resource_manager.h>
#include <vector>

#include "SDL_render.h"
#include "game_parameters.h"

using SDL_RendererPtr =
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;

class Background
{
    public:
        Background(const std::shared_ptr<Texture>& background,
                   const GameField& game_field)
            : _background(background), _game_field(game_field)
        {
        }

        std::shared_ptr<Texture> get_texture() { return _background; }

        void render(const SDL_RendererPtr& renderer)
        {
            SDL_Rect dest = {0, 0, _game_field.w, _game_field.h};
            SDL_RenderCopy(renderer.get(), _background->_texture, NULL,
                           &dest);
            // make explosions
        }

    private:
        std::shared_ptr<Texture> _background;
        GameField _game_field;
};
