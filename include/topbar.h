#pragma once

#include "SDL_ttf.h"
#include "memory"
#include "string"

#include "SDL_render.h"

struct GameStatistic
{
        size_t _score{0};
        size_t _max_score{0};
};

using renderer_type =
    std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)>;

class Topbar
{
    public:
        Topbar(TTF_Font* font,
               const std::unique_ptr<GameStatistic>& stat)
            : _font(font), _stat(stat)
        {
        }

        void render(const renderer_type& renderer);

    private:
        void render_text(const renderer_type& renderer,
                         const std::string& text, int x, int y);

        SDL_Color _text_color{0, 200, 200};
        TTF_Font* _font{nullptr};

        // NOLINTNEXTLINE(cppcoreguidelines-avoid-const-or-ref-data-members)
        const std::unique_ptr<GameStatistic>& _stat;
};
