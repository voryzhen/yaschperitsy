#pragma once

#include "SDL_events.h"
#include "core/Window.h"
#include "ui/BaseScreen.h"
#include "ui/Button.h"
#include <core/ResourceManager.h>
#include <vector>

namespace yaschperitsy::ui
{

void on_click_start_screen_new_game();
void on_click_start_screen_settings();
void on_click_start_screen_exit();

class StartScreen : public BaseScreen
{
    public:
        StartScreen(const resource::ResourceManagerUPtr& rm,
                    int* current_screen)
            : BaseScreen(rm, current_screen)
        {
            _current_screen = current_screen;
            btns.emplace_back(std::make_unique<Button>(
                _rm->get_button_texture("New Game"), 100, 100));

            btns[0]->add_on_click_listeners(
                on_click_start_screen_new_game);

            btns.emplace_back(std::make_unique<Button>(
                _rm->get_button_texture("Settings"), 100, 150));

            btns[1]->add_on_click_listeners(
                on_click_start_screen_settings);

            btns.emplace_back(std::make_unique<Button>(
                _rm->get_button_texture("Exit"), 100, 200));

            btns[2]->add_on_click_listeners(on_click_start_screen_exit);
        }

        int update() override
        {
            for (auto& btn : btns)
            {
                btn->update();
            }
            return 0;
        }

        void render(const core::SDL_RendererUPtr& _renderer) override
        {
            // Set bg color
            SDL_SetRenderDrawColor(
                _renderer.get(), screen_background_color.r,
                screen_background_color.g, screen_background_color.b,
                screen_background_color.a);

            // Draw buttons
            for (auto& btn : btns)
            {
                btn->render(_renderer);
            }
        }

        void handle_events(const SDL_Event& event) override
        {
            for (auto& btn : btns)
            {
                btn->handle_event(event);
            }
        }

    private:
        std::vector<ButtonUPtr> btns;
        static int* _current_screen;

        friend void on_click_start_screen_new_game();
        friend void on_click_start_screen_settings();
        friend void on_click_start_screen_exit();
};

using StartScreenUPtr = std::unique_ptr<StartScreen>;

}; // namespace yaschperitsy::ui
