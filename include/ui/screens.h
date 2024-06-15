#pragma once

#include "SDL_events.h"
#include "base_screen.h"
#include "game/game.h"
#include "ui/button.h"
#include <exception>
#include <iostream>
#include <memory>
#include <ostream>
#include <resource_manager.h>
#include <utility>
#include <vector>

void on_click_start_screen_new_game();
void on_click_start_screen_settings();
void on_click_start_screen_exit();

class StartScreen : public BaseScreen
{
    public:
        StartScreen(const ResourceManagerUPtr& rm,
                    const SDL_RendererUPtr& _renderer,
                    int* current_screen)
            : BaseScreen(rm, _renderer, current_screen)
        {
            _current_screen = current_screen;
            btns.emplace_back(std::make_unique<Button>(
                "New Game", _rm->get_font("lazy"), _renderer, 100,
                100));

            btns[0]->add_on_click_listeners(
                on_click_start_screen_new_game);

            btns.emplace_back(std::make_unique<Button>(
                "Settings", _rm->get_font("lazy"), _renderer, 100,
                150));

            btns[1]->add_on_click_listeners(
                on_click_start_screen_settings);

            btns.emplace_back(std::make_unique<Button>(
                "Exit", _rm->get_font("lazy"), _renderer, 100, 200));

            btns[2]->add_on_click_listeners(on_click_start_screen_exit);
        }

        void update(const SDL_Event& event) override
        {
            for (auto& btn : btns)
            {
                btn->update(event);
            }
        }

        void render() override
        {
            for (auto& btn : btns)
            {
                btn->render();
            }
        }

        void handle_events(const SDL_Event& event) override {}

        // void on_click() override { *_current_screen = 1; }

    private:
        std::vector<ButtonUPtr> btns;
        static int* _current_screen;

        friend void on_click_start_screen_new_game();
        friend void on_click_start_screen_settings();
        friend void on_click_start_screen_exit();
};

using StartScreenUPtr = std::unique_ptr<StartScreen>;

void on_click_settings_screen_settings();

class SettingsScreen : public BaseScreen
{
    public:
        SettingsScreen(const ResourceManagerUPtr& rm,
                       const SDL_RendererUPtr& _renderer,
                       int* current_screen)
            : BaseScreen(rm, _renderer, current_screen)
        {
            _current_screen = current_screen;

            btns.emplace_back(std::make_unique<Button>(
                "Back", rm->get_font("lazy"), _renderer, 100, 100));

            btns[0]->add_on_click_listeners(
                on_click_settings_screen_settings);
        }

        // void on_click() override { *_current_screen = 0; }

        void update(const SDL_Event& event) override
        {
            for (auto& btn : btns)
            {
                btn->update(event);
            }
        }

        void render() override
        {
            for (auto& btn : btns)
            {
                btn->render();
            }
        }

        void handle_events(const SDL_Event& event) override {}

    private:
        std::vector<ButtonUPtr> btns;
        static int* _current_screen;

        friend void on_click_settings_screen_settings();
};

using SettingsScreenUPtr = std::unique_ptr<SettingsScreen>;

class PlayScreen : public BaseScreen
{
    public:
        PlayScreen(const ResourceManagerUPtr& rm,
                   const SDL_RendererUPtr& _renderer,
                   int* current_screen)
            : BaseScreen(rm, _renderer, current_screen)
        {
            _game = std::make_unique<Game>(_renderer, rm);
        }

        void handle_events(const SDL_Event& event) override
        {
            _game->handle_events(event);
        }

        void update(const SDL_Event& event) override
        {
            _game->update();
        }

        void render() override { _game->render(); }

    private:
        std::unique_ptr<Game> _game;
};

using PlayScreenUPtr = std::unique_ptr<PlayScreen>;
