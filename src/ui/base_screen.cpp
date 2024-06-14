#include "ui/base_screen.h"

BaseScreen::BaseScreen(TTF_FontSPtr font,
                       const SDL_RendererSPtr& _renderer,
                       int* current_screen)
    : _current_screen(current_screen), _font(std::move(font)),
      _renderer(_renderer) {};

BaseScreen::~BaseScreen() {}

void BaseScreen::update(const SDL_Event& event) {}

void BaseScreen::render() {}
