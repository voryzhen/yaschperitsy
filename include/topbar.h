#pragma once

#include <utility>

#include "SDL_ttf.h"
#include "memory"
#include "resource_manager.h"
#include "string"

#include "SDL_render.h"

#include "game_parameters.h"
#include <memory>

using SDL_RendererPtr =
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;

class Topbar
{
    public:
        Topbar(TTF_FontSPtr font,
               const std::unique_ptr<GameStatistic>& stat)
            : _font(std::move(font)), _stat(stat)
        {
        }

        void render(const SDL_RendererPtr& renderer);

    private:
        void render_text(const SDL_RendererPtr& renderer,
                         const std::string& text, int x, int y);

        SDL_Color _text_color{0, 200, 200};
        TTF_FontSPtr _font;

        // NOLINTNEXTLINE(cppcoreguidelines-avoid-const-or-ref-data-members)
        const std::unique_ptr<GameStatistic>& _stat;
};
