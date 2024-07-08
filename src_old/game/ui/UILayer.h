#pragma once

#include <memory>
#include <utility>

#include "SDL_pixels.h"
#include "SDL_rect.h"
#include "UIButton.h"
#include "core/Layer.h"
#include "core/ResourceManager.h"
#include "core/Window.h"
#include "core/events/MouseEvent.h"
#include "core/resource_management/Resource.h"

namespace yaschperitsy::game
{

class UILayer : public core::Layer
{
    public:
        UILayer(std::vector<std::shared_ptr<ui::UIButton>> btns)
            : core::Layer("UI Layer"), _btns(btns)
        {
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

        std::vector<std::shared_ptr<ui::UIButton>> _btns;
};

}; // namespace yaschperitsy::game
