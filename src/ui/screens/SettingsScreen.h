#pragma once

#include "SDL_events.h"
#include "app/Window.h"
#include "ui/BaseScreen.h"
#include "ui/Button.h"
#include <app/ResourceManager.h>
#include <vector>

namespace yaschperitsy::ui
{

void on_click_settings_screen_settings();

class SettingsScreen : public BaseScreen
{
    public:
        SettingsScreen(const resource::ResourceManagerUPtr& rm,
                       int* current_screen)
            : BaseScreen(rm, current_screen)
        {
            _current_screen = current_screen;

            btns.emplace_back(std::make_unique<Button>(
                rm->get_button_texture("Back"), 100, 100));

            btns[0]->add_on_click_listeners(
                on_click_settings_screen_settings);
        }

        int update() override
        {
            for (auto& btn : btns)
            {
                btn->update();
            }
            return 0;
        }

        void render(const app::SDL_RendererUPtr& _renderer) override
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

        friend void on_click_settings_screen_settings();
};

using SettingsScreenUPtr = std::unique_ptr<SettingsScreen>;

}; // namespace yaschperitsy::ui
