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
            resume_button.set_event_callback(callback);
            exit_button.set_event_callback(callback);
        }

        SDL_Rect rect = {50, 50, 300, 100};
        SDL_Rect dest = {50, 50, 300, 100};
        SDL_Color color = {50, 50, 100, 255};

        void render(const core::renderer::SDLRendererUPtr&) override;

        void
        on_event(const yaschperitsy::core::events::EventSPtr& event) override;

    private:
        ui::Button resume_button{200, 200, 300, 50, "Resume game", 5};
        ui::Button exit_button{200, 260, 300, 50, "Exit", 3};
};

}; // namespace yaschperitsy::game::layers
