#pragma once

#include "resource_manager.h"
#include <memory>
#include <string_view>
#include <vector>

class Button
{
    public:
        Button(std::string_view text, TTF_FontSPtr font,
               const SDL_RendererUPtr& _renderer, int x, int y);
        ~Button();

        void update(const SDL_Event& event);
        void render();

        void add_on_click_listeners(void (*listener)())
        {
            on_click_listeners.emplace_back(listener);
        }

    private:
        void on_hover();
        void defocus();
        void on_click();

        int _x = 0;
        int _y = 0;
        bool hover = false;
        TextureSPtr _texture;
        TextureSPtr _texture_on_hover;
        TTF_FontSPtr _font;
        const SDL_RendererUPtr& _renderer;

        std::vector<void (*)()> on_click_listeners;
};

using ButtonUPtr = std::unique_ptr<Button>;
