#include "UILayer.h"

namespace yaschperitsy::game
{

void UILayer::on_update(const core::SDL_RendererUPtr& ren)
{
    SDL_SetRenderDrawColor(ren.get(), curr_color.r, curr_color.g,
                           curr_color.b, curr_color.a);
    SDL_RenderFillRect(ren.get(), &r);
}

void UILayer::on_event(const core::events::EventSPtr& event)
{
    core::events::EventDispatcher dispatcher(event);

    dispatcher.dispatch<core::events::MouseButtonPressedEvent>(
        [this](const core::events::MouseButtonPressedEventSPtr& event)
        { return on_mouse_btn_pressed(event); });

    dispatcher.dispatch<core::events::MouseButtonReleasedEvent>(
        [this](const core::events::MouseButtonReleasedEventSPtr& event)
        { return on_mouse_btn_released(event); });

    dispatcher.dispatch<core::events::MouseMovedEvent>(
        [this](const core::events::MouseMovedEventSPtr& event)
        { return on_mouse_btn_moved(event); });
}

bool UILayer::on_mouse_btn_pressed(
    const core::events::MouseButtonPressedEventSPtr& e)
{
    if ((abs(75 - e->y_pos()) < 25) && (abs(125 - e->x_pos()) < 75))
    {
        curr_color = pressed_color;
    }

    return true;
}

bool UILayer::on_mouse_btn_released(
    const core::events::MouseButtonReleasedEventSPtr& e)
{
    if ((abs(75 - e->y_pos()) < 25) && (abs(125 - e->x_pos()) < 75))
    {
        curr_color = free_color;
    }

    return true;
}

bool UILayer::on_mouse_btn_moved(
    const core::events::MouseMovedEventSPtr& e)
{
    if ((abs(75 - e->y_pos()) < 25) && (abs(125 - e->x_pos()) < 75))
    {
        curr_color = hover_color;
    }
    else
    {
        curr_color = free_color;
    }

    return true;
}

}; // namespace yaschperitsy::game
