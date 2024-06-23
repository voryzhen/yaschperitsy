#pragma once

#include <memory>
#include <utility>

#include "SDL_events.h"
#include "app/ResourceManager.h"
#include "screens/Screens.h"
#include "ui/screens/GameEndScreen.h"

namespace yaschperitsy::ui
{

// Refactor to gameState or smth
enum class SCREENS
{
    start,
    settings,
    exit,
    play,
    gameend
};

class ScreenManager
{
    public:
        // TODO: refactor
        ScreenManager(const resource::ResourceManagerUPtr& rm)
            : _rm(rm), _start_screen(std::make_unique<StartScreen>(
                           _rm, (int*)(&_current_screen))),
              _settings_screent(std::make_unique<SettingsScreen>(
                  _rm, (int*)(&_current_screen))),
              _play_screen(std::make_unique<GameScreen>(
                  _rm, (int*)(&_current_screen))),
              _game_end_screen(std::make_unique<GameEndScreen>(
                  _rm, (int*)(&_current_screen))) {};

        ~ScreenManager() = default;

        int update();
        void handle_events(const SDL_Event& event);
        void render(const resource::SDL_RendererUPtr& renderer);

    private:
        const resource::ResourceManagerUPtr& _rm;
        // const SDL_RendererUPtr& _renderer;

        SCREENS _current_screen{SCREENS::start};

        StartScreenUPtr _start_screen;
        SettingsScreenUPtr _settings_screent;
        GameScreenUPtr _play_screen;
        GameEndScreenUPtr _game_end_screen;
};

using ScreenManagerUPtr = std::unique_ptr<ScreenManager>;

}; // namespace yaschperitsy::ui
