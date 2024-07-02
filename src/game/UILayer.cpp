#include "UILayer.h"

namespace yaschperitsy::game
{

void UILayer::on_update(const core::SDL_RendererUPtr& ren)
{
    for (const auto& _btn : _btns)
    {
        _btn->render(ren);
    }
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
    for (const auto& _btn : _btns)
    {
        if (_btn->intersect(e->x_pos(), e->y_pos()))
        {
            _btn->on_pressed();
        }
    }

    return true;
}

bool UILayer::on_mouse_btn_released(
    const core::events::MouseButtonReleasedEventSPtr& e)
{
    for (const auto& _btn : _btns)
    {
        if (_btn->intersect(e->x_pos(), e->y_pos()))
        {
            _btn->on_released();
        }
    }

    return true;
}

bool UILayer::on_mouse_btn_moved(
    const core::events::MouseMovedEventSPtr& e)
{
    for (const auto& _btn : _btns)
    {
        if (_btn->intersect(e->x_pos(), e->y_pos()))
        {
            _btn->on_hover();
        }
        else
        {
            _btn->on_loose_focus();
        }
    }

    return true;
}
}; // namespace yaschperitsy::game
