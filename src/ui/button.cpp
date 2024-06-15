#include "ui/button.h"
#include "SDL_events.h"

// Button::Button(std::string_view text, TTF_FontSPtr font, int x, int
// y) : _x(x), _y(y), _font(std::move(font))
// {
// }

Button::~Button()
{
    // SDL_DestroyTexture(_texture->_texture);
    // SDL_DestroyTexture(_texture_on_hover->_texture);
}

void Button::update(const SDL_Event& event)
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

void Button::render(const SDL_RendererUPtr& renderer)
{
    SDL_Rect rect = {_x, _y, _textures.normal->_w,
                     _textures.normal->_h};
    const auto texture = hover ? _textures.on_hover : _textures.normal;
    SDL_RenderCopy(renderer.get(), texture->_texture, NULL, &rect);
}
