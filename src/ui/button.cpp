#include "ui/Button.h"
#include "SDL_events.h"

namespace yaschperitsy::ui
{

void Button::update() {}

void Button::handle_event(const SDL_Event& event)
{
    int x = 0;
    int y = 0;
    SDL_GetMouseState(&x, &y);

    SDL_Rect rect1 = {_x, _y, _textures.normal->_w,
                      _textures.normal->_h};
    SDL_Rect rect2 = {x, y, 1, 1};

    if (SDL_HasIntersection(&rect1, &rect2) != 0u)
    {
        on_hover();
        if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            on_click();
        }
    }
    else
    {
        defocus();
    }
}

void Button::on_hover() { hover = true; }

void Button::defocus() { hover = false; }

void Button::on_click()
{
    if (!on_click_listeners.empty())
    {
        for (auto listener : on_click_listeners)
        {
            listener();
        }
    }
}

void Button::render(const resource::SDL_RendererUPtr& renderer)
{
    SDL_Rect rect = {_x, _y, _textures.normal->_w,
                     _textures.normal->_h};
    const auto texture = hover ? _textures.on_hover : _textures.normal;
    SDL_RenderCopy(renderer.get(), texture->_texture, NULL, &rect);
}

}; // namespace yaschperitsy::ui
