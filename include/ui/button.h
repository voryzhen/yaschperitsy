#pragma once

#include "resource_manager.h"
#include <memory>
#include <string_view>
#include <vector>

namespace yaschperitsy::app
{

class Button
{
    public:
        Button(resource::ButtonTextures textures, int x, int y)
            : _textures(textures), _x(x), _y(y)
        {
        }

        ~Button() {}

        void update();
        void render(const resource::SDL_RendererUPtr& renderer);
        void handle_event(const SDL_Event& event);

        void add_on_click_listeners(void (*listener)())
        {
            on_click_listeners.emplace_back(listener);
        }

    private:
        void on_hover();
        void defocus();
        void on_click();

        resource::ButtonTextures _textures;
        int _x = 0;
        int _y = 0;
        bool hover = false;
        resource::TTF_FontSPtr _font;

        std::vector<void (*)()> on_click_listeners;
};

using ButtonUPtr = std::unique_ptr<Button>;

}; // namespace yaschperitsy::app
