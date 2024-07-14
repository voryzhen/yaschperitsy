#pragma once

#include "core/scene/Layer.hpp"

namespace yaschperitsy::game::ui::main_menu
{

class MainMenuLayer : public yaschperitsy::core::Layer
{
    public:
        SDL_Rect rect = {50, 50, 300, 100};
        SDL_Rect dest = {50, 50, 300, 100};
        SDL_Color color = {50, 50, 100, 255};

        void render(SDL_Renderer* ren) override;

        void
        on_event(const yaschperitsy::core::events::EventSPtr& event) override;
};

}; // namespace yaschperitsy::game::ui::main_menu
