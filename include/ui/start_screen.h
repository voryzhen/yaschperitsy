#pragma once

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
        bool hover = false;
        TextureSPtr _texture;
        TextureSPtr _texture_on_hover;
        TTF_FontSPtr _font;
        const SDL_RendererSPtr& _renderer;
};

using StartScreenUPtr = std::unique_ptr<StartScreen>;
