#include "ui/start_screen.h"
#include "SDL_render.h"

StartScreen::StartScreen(TTF_FontSPtr font,
                         const SDL_RendererPtr& _renderer)
    : _font(std::move(font)), _renderer(_renderer)
{
    SDL_Color _text_color{0, 200, 200};
    SDL_Surface* text_surface =
        TTF_RenderText_Solid(_font.get(), "StartScreen", _text_color);

    _texture = std::make_shared<Texture>(
        SDL_CreateTextureFromSurface(_renderer.get(), text_surface));

    SDL_FreeSurface(text_surface);
};

StartScreen::~StartScreen() { SDL_DestroyTexture(_texture->_texture); }

void StartScreen::update() {}

void StartScreen::render()
{
    SDL_Rect rect = {100, 100, _texture->_w, _texture->_h};
    SDL_RenderCopy(_renderer.get(), _texture->_texture, NULL, &rect);
}