#pragma once

#include "ui/button.h"
#include <memory>
#include <resource_manager.h>
#include <vector>

class StartScreen
{
    public:
        StartScreen(TTF_FontSPtr font,
                    const SDL_RendererSPtr& _renderer,
                    int* current_screen);
        ~StartScreen();
        void update(const SDL_Event& event);
        void render();

    private:
        static void on_click();
        std::vector<ButtonUPtr> btns;
        static int* _current_screen;
        TTF_FontSPtr _font;
        const SDL_RendererSPtr& _renderer;
};

using StartScreenUPtr = std::unique_ptr<StartScreen>;
