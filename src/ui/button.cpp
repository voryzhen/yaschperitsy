#include "ui/button.h"
#include "SDL_events.h"

Button::Button(std::string_view text, TTF_FontSPtr font,
               const SDL_RendererUPtr& _renderer, int x, int y)
    : _x(x), _y(y), _font(std::move(font)), _renderer(_renderer)
{
    SDL_Color _text_color{0, 200, 200};
    SDL_Surface* text_surface =
        TTF_RenderText_Solid(_font.get(), text.data(), _text_color);

    _texture = std::make_shared<Texture>(
        SDL_CreateTextureFromSurface(_renderer.get(), text_surface));

    SDL_FreeSurface(text_surface);

    _text_color = {0, 100, 200};
    text_surface =
        TTF_RenderText_Solid(_font.get(), text.data(), _text_color);

    _texture_on_hover = std::make_shared<Texture>(
        SDL_CreateTextureFromSurface(_renderer.get(), text_surface));

    SDL_FreeSurface(text_surface);
}

Button::~Button()
{
    SDL_DestroyTexture(_texture->_texture);
    SDL_DestroyTexture(_texture_on_hover->_texture);
}

void Button::update(const SDL_Event& event)
{
    int x = 0;
    int y = 0;
    SDL_GetMouseState(&x, &y);

    SDL_Rect rect1 = {_x, _y, _texture->_w, _texture->_h};
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

void Button::render()
{
    SDL_Rect rect = {_x, _y, _texture->_w, _texture->_h};
    const auto& texture =
        hover ? _texture_on_hover->_texture : _texture->_texture;
    SDL_RenderCopy(_renderer.get(), texture, NULL, &rect);
}
