#pragma once

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
        bool hover = false;
        TextureSPtr _texture;
        TextureSPtr _texture_on_hover;
        TTF_FontSPtr _font;
        const SDL_RendererSPtr& _renderer;
};

using SettingsScreenUPtr = std::unique_ptr<SettingsScreen>;
