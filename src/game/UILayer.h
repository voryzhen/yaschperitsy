#pragma once

#include "SDL_pixels.h"
#include "SDL_rect.h"
#include "core/Layer.h"
#include "core/Window.h"
#include "core/events/MouseEvent.h"
#include "ui/UIButton.h"

namespace yaschperitsy::game
{

class UILayer : public core::Layer
{
    public:
        UILayer() : core::Layer("UI Layer")
        {
            SDL_Rect geom = {50, 50, 150, 50};
            btn.set_geom(geom);
            SDL_Color c = {0, 0, 255, 0};
            SDL_Color hc = {0, 255, 0, 0};
            SDL_Color pc = {255, 0, 0, 0};
            btn.set_colors(c, hc, pc);
        }

        void on_update(const core::SDL_RendererUPtr& ren) override;
        void on_event(const core::events::EventSPtr& event) override;

    private:
        bool on_mouse_btn_pressed(
            const core::events::MouseButtonPressedEventSPtr& e);
        bool on_mouse_btn_released(
            const core::events::MouseButtonReleasedEventSPtr& e);
        bool
        on_mouse_btn_moved(const core::events::MouseMovedEventSPtr& e);

        ui::UIButton btn;
};

}; // namespace yaschperitsy::game
