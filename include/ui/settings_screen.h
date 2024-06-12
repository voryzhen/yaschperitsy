#pragma once

#include "ui/button.h"
#include <memory>
#include <resource_manager.h>

class SettingsScreen
{
    public:
        SettingsScreen(TTF_FontSPtr font,
                       const SDL_RendererSPtr& _renderer);
        ~SettingsScreen();
        void update();
        void render();

    private:
        ButtonUPtr btn;

        TTF_FontSPtr _font;
        const SDL_RendererSPtr& _renderer;
};

using SettingsScreenUPtr = std::unique_ptr<SettingsScreen>;
