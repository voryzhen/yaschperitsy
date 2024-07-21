#pragma once

#include "core/scene/Layer.hpp"
#include "game/game/button/Button.hpp"

namespace yaschperitsy::game::layers
{

class MainMenuLayer : public yaschperitsy::core::Layer
{
    public:
        MainMenuLayer(const ui::EventCallbackFn& callback)
        {
            _new_game_button.set_event_callback(callback);
            _settings_button.set_event_callback(callback);
            _exit_button.set_event_callback(callback);
        }

        void render(const core::renderer::SDLRendererUPtr&) override;

        void
        on_event(const yaschperitsy::core::events::EventSPtr& event) override;

    private:
        ui::Button _new_game_button{200, 200, "New game", 1};
        ui::Button _settings_button{200, 260, "Settings", 2};
        ui::Button _exit_button{200, 320, "Exit", 3};
};

}; // namespace yaschperitsy::game::layers
