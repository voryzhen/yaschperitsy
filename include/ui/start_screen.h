#pragma once

#include "ui/button.h"
#include <memory>
#include <resource_manager.h>

class StartScreen
{
    public:
        StartScreen(TTF_FontSPtr font,
                    const SDL_RendererSPtr& _renderer);
        ~StartScreen();
        void update();
        void render();

    private:
        ButtonUPtr btn;
        TTF_FontSPtr _font;
        const SDL_RendererSPtr& _renderer;
};

using StartScreenUPtr = std::unique_ptr<StartScreen>;
