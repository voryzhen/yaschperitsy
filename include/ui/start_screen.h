#pragma once

#include "ui/button.h"
#include <memory>
#include <resource_manager.h>
#include <vector>

class StartScreen
{
    public:
        StartScreen(TTF_FontSPtr font,
                    const SDL_RendererSPtr& _renderer);
        ~StartScreen();
        void update(const SDL_Event& event);
        void render();

    private:
        std::vector<ButtonUPtr> btns;
        TTF_FontSPtr _font;
        const SDL_RendererSPtr& _renderer;
};

using StartScreenUPtr = std::unique_ptr<StartScreen>;
