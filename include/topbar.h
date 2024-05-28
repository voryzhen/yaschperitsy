#pragma once

#include "SDL_ttf.h"
#include "string"

#include "SDL_render.h"

struct GameStatistic
{
        size_t _score{0};
        size_t _max_score{0};
};

class Topbar
{
    public:
        Topbar(TTF_Font* font, GameStatistic& stat)
            : _font(font), _stat(stat)
        {
        }

        void render(SDL_Renderer* renderer);

    private:
        void render_text(SDL_Renderer* renderer,
                         const std::string& text, int x, int y);

        SDL_Color _text_color{0, 200, 200};
        TTF_Font* _font{nullptr};

        // NOLINTNEXTLINE(cppcoreguidelines-avoid-const-or-ref-data-members)
        GameStatistic& _stat; // TODO: refactor
};
