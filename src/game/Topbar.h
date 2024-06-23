#pragma once

#include <utility>

#include "SDL_ttf.h"
#include "app/ResourceManager.h"
#include "memory"
#include "string"

#include "SDL_render.h"

#include "GameParameters.h"
#include <memory>

namespace yaschperitsy::game
{

using SDL_RendererUPtr =
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;

class Topbar
{
    public:
        Topbar(resource::TTF_FontSPtr font,
               const std::unique_ptr<GameStatistic>& stat)
            : _font(std::move(font)), _stat(stat)
        {
        }

        void render(const SDL_RendererUPtr& renderer);

    private:
        void render_text(const SDL_RendererUPtr& renderer,
                         const std::string& text, int x, int y);

        SDL_Color _text_color{0, 200, 200};
        resource::TTF_FontSPtr _font;

        // NOLINTNEXTLINE(cppcoreguidelines-avoid-const-or-ref-data-members)
        const std::unique_ptr<GameStatistic>& _stat;
};

}; // namespace yaschperitsy::game
