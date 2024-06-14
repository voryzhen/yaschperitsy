#pragma once

#include "base_screen.h"
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
        StartScreen(TTF_FontSPtr font,
                    const SDL_RendererSPtr& _renderer,
                    int* current_screen)
            : BaseScreen(std::move(font), _renderer, current_screen)
        {
            _current_screen = current_screen;
            btns.emplace_back(std::make_unique<Button>(
                "New Game", _font, _renderer, 100, 100));

            btns[0]->add_on_click_listeners(
                on_click_start_screen_new_game);

            btns.emplace_back(std::make_unique<Button>(
                "Settings", _font, _renderer, 100, 150));

            btns[1]->add_on_click_listeners(
                on_click_start_screen_settings);

            btns.emplace_back(std::make_unique<Button>(
                "Exit", _font, _renderer, 100, 200));

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
        SettingsScreen(TTF_FontSPtr font,
                       const SDL_RendererSPtr& _renderer,
                       int* current_screen)
            : BaseScreen(std::move(font), _renderer, current_screen)
        {
            _current_screen = current_screen;

            btns.emplace_back(std::make_unique<Button>(
                "Back", _font, _renderer, 100, 100));

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

    private:
        std::vector<ButtonUPtr> btns;
        static int* _current_screen;

        friend void on_click_settings_screen_settings();
};

using SettingsScreenUPtr = std::unique_ptr<SettingsScreen>;
