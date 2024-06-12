#include "ui/start_screen.h"
#include "ui/button.h"
#include <memory>

StartScreen::StartScreen(TTF_FontSPtr font,
                         const SDL_RendererSPtr& _renderer)
    : _font(std::move(font)), _renderer(_renderer)
{
    btn = std::make_unique<Button>("StartScreen", _font, _renderer);
};

StartScreen::~StartScreen() {}

void StartScreen::update() { btn->update(); }

void StartScreen::render() { btn->render(); }
