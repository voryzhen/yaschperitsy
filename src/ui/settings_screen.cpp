#include "ui/settings_screen.h"

#include "ui/button.h"
#include <memory>

SettingsScreen::SettingsScreen(TTF_FontSPtr font,
                               const SDL_RendererSPtr& _renderer)
    : _font(std::move(font)), _renderer(_renderer)
{
    btn = std::make_unique<Button>("SettingScreen", _font, _renderer);
};

SettingsScreen::~SettingsScreen() {}

void SettingsScreen::update() { btn->update(); }

void SettingsScreen::render() { btn->render(); }
