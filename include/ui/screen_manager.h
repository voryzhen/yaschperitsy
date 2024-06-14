#pragma once

#include <memory>
#include <utility>

#include "SDL_events.h"
#include "resource_manager.h"
#include "screens.h"

// Refactor to gameState or smth
enum class SCREENS
{
    start,
    settings,
    exit,
    play
};

class ScreenManager
{
    public:
        ScreenManager(const ResourceManagerUPtr& rm,
                      const SDL_RendererSPtr& _renderer)
            : _rm(rm), _renderer(_renderer),
              _start_screen(std::make_unique<StartScreen>(
                  _rm, _renderer, (int*)(&_current_screen))),
              _settings_screent(std::make_unique<SettingsScreen>(
                  _rm, _renderer, (int*)(&_current_screen))),
              _play_screen(std::make_unique<PlayScreen>(
                  _rm, _renderer, (int*)(&_current_screen))) {};
        ~ScreenManager() = default;

        int update(const SDL_Event& event);
        void handle_events(const SDL_Event& event);
        void render();

    private:
        const ResourceManagerUPtr& _rm;
        SDL_RendererSPtr _renderer;

        SCREENS _current_screen{SCREENS::start};

        StartScreenUPtr _start_screen;
        SettingsScreenUPtr _settings_screent;
        PlayScreenUPtr _play_screen;
};

using ScreenManagerUPtr = std::unique_ptr<ScreenManager>;
