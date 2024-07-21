#pragma once

#include "core/scene/Layer.hpp"
#include "game/game/button/Button.hpp"
#include "game/game/label/Label.hpp"

namespace yaschperitsy::game::layers
{

class GameEndLayer : public yaschperitsy::core::Layer
{
    public:
        GameEndLayer(const ui::EventCallbackFn& callback)
        {
            new_game_button.set_event_callback(callback);
            exit_button.set_event_callback(callback);
        }

        SDL_Rect rect = {50, 50, 300, 100};
        SDL_Rect dest = {50, 50, 300, 100};
        SDL_Color color = {50, 50, 100, 255};

        void render(const core::renderer::SDLRendererUPtr&) override;

        void
        on_event(const yaschperitsy::core::events::EventSPtr& event) override;

    private:
        ui::Label _label{200, 200, "You win"};
        ui::Button new_game_button{200, 260, "New game", 1};
        ui::Button exit_button{200, 320, "Exit", 3};
};

}; // namespace yaschperitsy::game::layers
