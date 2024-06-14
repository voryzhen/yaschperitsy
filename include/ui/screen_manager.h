#pragma once

#include <memory>
#include <utility>

#include "resource_manager.h"
#include "screens.h"
// #include "ui/settings_screen.h"

enum class SCREENS
{
    start,
    settings
};

class ScreenManager
{
    public:
        ScreenManager(TTF_FontSPtr font,
                      const SDL_RendererSPtr& _renderer)
            : _font(std::move(font)), _renderer(_renderer),
              _start_screen(std::make_unique<StartScreen>(
                  _font, _renderer, (int*)(&_current_screen))),
              _settings_screent(std::make_unique<SettingsScreen>(
                  _font, _renderer, (int*)(&_current_screen))) {};
        ~ScreenManager() = default;

        void update(const SDL_Event& event);

        void render();

    private:
        TTF_FontSPtr _font;
        SDL_RendererSPtr _renderer;

        SCREENS _current_screen{SCREENS::start};
        StartScreenUPtr _start_screen;
        SettingsScreenUPtr _settings_screent;
};

using ScreenManagerUPtr = std::unique_ptr<ScreenManager>;
