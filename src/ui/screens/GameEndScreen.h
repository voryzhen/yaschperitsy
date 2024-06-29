#pragma once

#include "core/Window.h"
#include "ui/BaseScreen.h"
#include "ui/Button.h"
#include <memory>

namespace yaschperitsy::ui
{

void on_click_gameend_screen_reset();

class GameEndScreen : public BaseScreen
{
    public:
        GameEndScreen(const resource::ResourceManagerUPtr& rm,
                      int* current_screen)
            : BaseScreen(rm, current_screen)
        {
            _current_screen = current_screen;

            btns.emplace_back(std::make_unique<Button>(
                _rm->get_button_texture("You win"), 100, 100));

            btns.emplace_back(std::make_unique<Button>(
                _rm->get_button_texture("Reset"), 100, 200));

            btns[1]->add_on_click_listeners(
                on_click_gameend_screen_reset);
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

        friend void on_click_gameend_screen_reset();
};

using GameEndScreenUPtr = std::unique_ptr<GameEndScreen>;

}; // namespace yaschperitsy::ui
