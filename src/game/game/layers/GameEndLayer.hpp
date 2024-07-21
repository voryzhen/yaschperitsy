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
            _new_game_button.set_event_callback(callback);
            _exit_button.set_event_callback(callback);
        }

        void render(const core::renderer::SDLRendererUPtr&) override;

        void
        on_event(const yaschperitsy::core::events::EventSPtr& event) override;

    private:
        ui::Label _label{200, 200, "You win"};
        ui::Button _new_game_button{200, 260, "New game", 1};
        ui::Button _exit_button{200, 320, "Exit", 3};
};

}; // namespace yaschperitsy::game::layers
