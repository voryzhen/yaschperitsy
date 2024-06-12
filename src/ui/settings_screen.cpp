#include "ui/settings_screen.h"

#include "ui/button.h"
#include <memory>

SettingsScreen::SettingsScreen(TTF_FontSPtr font,
                               const SDL_RendererSPtr& _renderer)
    : _font(std::move(font)), _renderer(_renderer)
{
    btn = std::make_unique<Button>("SettingScreen", _font, _renderer,
                                   100, 100);
};

SettingsScreen::~SettingsScreen() {}

void SettingsScreen::update(const SDL_Event& event)
{
    btn->update(event);
}

void SettingsScreen::render() { btn->render(); }
