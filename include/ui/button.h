#pragma once

#include "resource_manager.h"
#include <memory>
#include <string_view>
#include <vector>

class Button
{
    public:
        Button(ButtonTextures textures, int x, int y)
            : _textures(textures), _x(x), _y(y)
        {
        }

        ~Button();

        void update(const SDL_Event& event);
        void render(const SDL_RendererUPtr& renderer);

        void add_on_click_listeners(void (*listener)())
        {
            on_click_listeners.emplace_back(listener);
        }

    private:
        void on_hover();
        void defocus();
        void on_click();

        ButtonTextures _textures;
        int _x = 0;
        int _y = 0;
        bool hover = false;
        TTF_FontSPtr _font;

        std::vector<void (*)()> on_click_listeners;
};

using ButtonUPtr = std::unique_ptr<Button>;
