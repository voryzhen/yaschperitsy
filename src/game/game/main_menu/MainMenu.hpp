#pragma once

#include "core/scene/Layer.hpp"
#include "game/game/button/Button.hpp"
#include "game/game/events/UIEvent.hpp"

namespace yaschperitsy::game::ui::main_menu
{

class MainMenuLayer : public yaschperitsy::core::Layer
{
    public:
        MainMenuLayer(const EventCallbackFn& callback)
        {
            new_game_button.set_event_callback(callback);
            settings_button.set_event_callback(callback);
            exit_button.set_event_callback(callback);
        }

        SDL_Rect rect = {50, 50, 300, 100};
        SDL_Rect dest = {50, 50, 300, 100};
        SDL_Color color = {50, 50, 100, 255};

        void render(SDL_Renderer* ren) override;

        void
        on_event(const yaschperitsy::core::events::EventSPtr& event) override;

    private:
        Button new_game_button{200, 200, 300, 50, "New game", 1};
        Button settings_button{200, 260, 300, 50, "Settings", 2};
        Button exit_button{200, 320, 300, 50, "Exit", 3};
};

}; // namespace yaschperitsy::game::ui::main_menu
