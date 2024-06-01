#include "topbar.h"
#include "SDL_ttf.h"
#include <string>

void Topbar::render(const renderer_type& renderer)
{
    render_text(renderer,
                "Total Score: " + std::to_string(_stat->_score), 5, 5);
    render_text(renderer,
                "Max Score: " + std::to_string(_stat->_max_score), 500,
                5);
}

void Topbar::render_text(const renderer_type& renderer,
                         const std::string& text, int x, int y)
{
    SDL_Surface* text_surface =
        TTF_RenderText_Solid(_font, text.c_str(), _text_color);

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