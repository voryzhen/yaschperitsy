#pragma once

#include "core/scene/Layer.hpp"
#include "game/game/button/Button.hpp"

namespace yaschperitsy::game::layers
{

class PauseMenuLayer : public yaschperitsy::core::Layer
{
    public:
        PauseMenuLayer(const ui::EventCallbackFn& callback)
        {
            _resume_button.set_event_callback(callback);
            _exit_button.set_event_callback(callback);
        }

        void render(const core::renderer::SDLRendererUPtr&) override;

        void
        on_event(const yaschperitsy::core::events::EventSPtr& event) override;

    private:
        ui::Button _resume_button{200, 200, "Resume game", 5};
        ui::Button _exit_button{200, 260, "Exit", 3};
};

}; // namespace yaschperitsy::game::layers
