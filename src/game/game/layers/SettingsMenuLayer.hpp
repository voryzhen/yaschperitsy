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

        void render(const core::renderer::SDLRendererUPtr&) override;

        void
        on_event(const yaschperitsy::core::events::EventSPtr& event) override;

    private:
        ui::Button _back_button{200, 200, "Back", 4};
};

}; // namespace yaschperitsy::game::layers
