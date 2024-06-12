#include "ui/settings_screen.h"
#include "SDL_render.h"

SettingsScreen::SettingsScreen(TTF_FontSPtr font,
                               const SDL_RendererSPtr& _renderer)
    : _font(std::move(font)), _renderer(_renderer)
{
    SDL_Color _text_color{0, 200, 200};
    SDL_Surface* text_surface = TTF_RenderText_Solid(
        _font.get(), "SettingsScreen", _text_color);

    _texture = std::make_shared<Texture>(
        SDL_CreateTextureFromSurface(_renderer.get(), text_surface));

    SDL_FreeSurface(text_surface);

    _text_color = {0, 100, 200};
    text_surface = TTF_RenderText_Solid(_font.get(), "SettingsScreen",
                                        _text_color);

    _texture_on_hover = std::make_shared<Texture>(
        SDL_CreateTextureFromSurface(_renderer.get(), text_surface));

    SDL_FreeSurface(text_surface);
};

SettingsScreen::~SettingsScreen()
{
    SDL_DestroyTexture(_texture->_texture);
    SDL_DestroyTexture(_texture_on_hover->_texture);
}

void SettingsScreen::update()
{
    int x = 0;
    int y = 0;
    SDL_GetMouseState(&x, &y);

    SDL_Rect rect1 = {100, 100, _texture->_w, _texture->_h};
    SDL_Rect rect2 = {x, y, 1, 1};

    hover = SDL_HasIntersection(&rect1, &rect2) == 0u ? false : true;
}

void SettingsScreen::render()
{
    SDL_Rect rect = {100, 100, _texture->_w, _texture->_h};
    const auto& texture =
        hover ? _texture_on_hover->_texture : _texture->_texture;
    SDL_RenderCopy(_renderer.get(), texture, NULL, &rect);
}
