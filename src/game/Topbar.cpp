#include "game/Topbar.h"
#include "SDL_ttf.h"
#include <string>

namespace yaschperitsy::game
{

using SDL_RendererUPtr =
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;

void Topbar::render(const SDL_RendererUPtr& renderer)
{
    render_text(renderer,
                "Total Score: " + std::to_string(_stat->_score), 5, 5);
    render_text(renderer,
                "Max Score: " + std::to_string(_stat->_max_score), 300,
                5);

    render_text(renderer, "HP: " + std::to_string(_stat->_curr_hp), 600,
                5);

    auto text = _stat->_yaschperitsy_total_num != _stat->_score
                    ? "Remaining yaschperitsy: " +
                          std::to_string(_stat->_yaschperitsy_num)
                    : "You win";
    render_text(renderer, text, 900, 5);
}

// TODO: refactor text surface creator
void Topbar::render_text(const SDL_RendererUPtr& renderer,
                         const std::string& text, int x, int y)
{
    SDL_Surface* text_surface =
        TTF_RenderText_Solid(_font.get(), text.c_str(), _text_color);

    SDL_Texture* text_texture{nullptr};

    int w = 0;
    int h = 0;

    if (text_surface == nullptr)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n",
               TTF_GetError());
    }
    else
    {
        // Create texture from surface pixels
        text_texture =
            SDL_CreateTextureFromSurface(renderer.get(), text_surface);
        if (text_texture == nullptr)
        {
            printf("Unable to create texture from rendered text! SDL "
                   "Error: %s\n",
                   SDL_GetError());
        }
        else
        {
            // Get image dimensions
            w = text_surface->w;
            h = text_surface->h;
        }

        // Get rid of old surface
        SDL_FreeSurface(text_surface);
    }

    SDL_Rect rect = {x, y, w, h};
    SDL_RenderCopy(renderer.get(), text_texture, NULL, &rect);
}

}; // namespace yaschperitsy::game
