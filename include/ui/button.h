#pragma once

#include "resource_manager.h"
#include <memory>
#include <string_view>

class Button
{
    public:
        Button(std::string_view text, TTF_FontSPtr font,
               const SDL_RendererSPtr& _renderer);
        ~Button();

        void update();
        void render();

    private:
        bool hover = false;
        TextureSPtr _texture;
        TextureSPtr _texture_on_hover;
        TTF_FontSPtr _font;
        const SDL_RendererSPtr& _renderer;
};

using ButtonUPtr = std::unique_ptr<Button>;
