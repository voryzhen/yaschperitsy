#pragma once

#include <memory>
#include <resource_manager.h>
#include <utility>
#include <vector>

#include "SDL_render.h"
#include "game_parameters.h"

namespace yaschperitsy::app
{

using SDL_RendererUPtr =
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;

class Background
{
    public:
        Background(resource::TextureSPtr background,
                   const GameField& game_field)
            : _background(std::move(background)),
              _game_field(game_field)
        {
        }

        resource::TextureSPtr get_texture() { return _background; }

        void render(const SDL_RendererUPtr& renderer)
        {
            SDL_Rect dest = {0, 0, _game_field.w, _game_field.h};
            SDL_RenderCopy(renderer.get(), _background->_texture, NULL,
                           &dest);
            // make explosions
        }

        void set_game_field(const GameField& game_field)
        {
            _game_field = game_field;
        }

    private:
        resource::TextureSPtr _background;
        GameField _game_field;
};

}; // namespace yaschperitsy::app
