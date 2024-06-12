#pragma once

#include <memory>
#include <utility>

#include "SDL_surface.h"
#include "resource_manager.h"

class StartScreen
{
    public:
        StartScreen(TTF_FontSPtr font,
                    const SDL_RendererSPtr& _renderer);
        ~StartScreen();
        void update();
        void render();

    private:
        TextureSPtr _texture;
        TTF_FontSPtr _font;
        const SDL_RendererSPtr& _renderer;
};

using StartScreenUPtr = std::unique_ptr<StartScreen>;
