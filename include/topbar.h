#pragma once

#include "SDL_ttf.h"
#include "string"

#include "SDL_render.h"

class Topbar

{
    public:
        Topbar(TTF_Font* font) : _font(font) {} // TODO: add score

        void render(SDL_Renderer* renderer);

    private:
        void render_text(SDL_Renderer* renderer,
                         const std::string& text, int x, int y);

        SDL_Color _text_color{0, 200, 200};
        TTF_Font* _font{nullptr};
};
