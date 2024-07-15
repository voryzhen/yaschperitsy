#pragma once

#include "core/scene/Layer.hpp"
#include "game/game/button/Button.hpp"

namespace yaschperitsy::game::layers
{

class SettingsMenuLayer : public yaschperitsy::core::Layer
{
    public:
        SettingsMenuLayer(const ui::EventCallbackFn& callback)
        {
            _back_button.set_event_callback(callback);
        };

        SDL_Rect rect = {50, 50, 300, 100};
        SDL_Rect dest = {50, 50, 300, 100};
        SDL_Color color = {50, 50, 100, 255};

        void render(SDL_Renderer* ren) override;

        void
        on_event(const yaschperitsy::core::events::EventSPtr& event) override;

    private:
        ui::Button _back_button{200, 200, 300, 50, "Back", 4};
};

}; // namespace yaschperitsy::game::layers
