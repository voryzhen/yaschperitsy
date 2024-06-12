#pragma once

#include "ui/button.h"
#include <memory>
#include <resource_manager.h>

class SettingsScreen
{
    public:
        SettingsScreen(TTF_FontSPtr font,
                       const SDL_RendererSPtr& _renderer,
                       int* current_screen);
        ~SettingsScreen();
        void update(const SDL_Event& event);
        void render();

    private:
        ButtonUPtr btn;
        static int* _current_screen;

        TTF_FontSPtr _font;
        const SDL_RendererSPtr& _renderer;
};

using SettingsScreenUPtr = std::unique_ptr<SettingsScreen>;
