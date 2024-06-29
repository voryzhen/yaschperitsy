#pragma once

#include "core/Layer.h"
#include "core/Window.h"
#include "core/events/MouseEvent.h"

namespace yaschperitsy::game
{

class UILayer : public core::Layer
{
    public:
        UILayer() : core::Layer("UI Layer") {}

        void on_update(const core::SDL_RendererUPtr& ren) override;
        void on_event(const core::events::EventSPtr& event) override;

    private:
        bool on_mouse_btn_pressed(
            const core::events::MouseButtonPressedEventSPtr& e);
        bool on_mouse_btn_released(
            const core::events::MouseButtonReleasedEventSPtr& e);
        bool
        on_mouse_btn_moved(const core::events::MouseMovedEventSPtr& e);

        SDL_Rect r = {50, 50, 150, 50};

        SDL_Colour curr_color = {0, 0, 255, 255};
        SDL_Colour free_color = {0, 0, 255, 255};
        SDL_Colour pressed_color = {0, 255, 0, 255};
        SDL_Colour hover_color = {255, 0, 0, 255};
};

}; // namespace yaschperitsy::game
