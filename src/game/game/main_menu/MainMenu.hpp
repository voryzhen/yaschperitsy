#pragma once

#include "core/scene/Layer.hpp"
#include "game/game/button/Button.hpp"

namespace yaschperitsy::game::ui::main_menu
{

class MainMenuLayer : public yaschperitsy::core::Layer
{
    public:
        MainMenuLayer() = default;

        SDL_Rect rect = {50, 50, 300, 100};
        SDL_Rect dest = {50, 50, 300, 100};
        SDL_Color color = {50, 50, 100, 255};

        void render(SDL_Renderer* ren) override;

        void
        on_event(const yaschperitsy::core::events::EventSPtr& event) override;

    private:
        button::Button new_game_button{200, 200, 300, 50, "New game"};
        button::Button settings_button{200, 260, 300, 50, "Settings"};
        button::Button exit_button{200, 320, 300, 50, "Exit"};
};

}; // namespace yaschperitsy::game::ui::main_menu
