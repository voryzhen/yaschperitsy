#include "Button.hpp"
#include "core/events/Event.hpp"
#include "core/events/MouseEvent.hpp"
#include "game/game/events/UIEvent.hpp"

namespace yaschperitsy::game::ui
{

void Button::render(const core::renderer::SDLRendererUPtr& ren)
{
    texture_index = _is_hover ? (_is_pressed ? 1 : 2) : 0;
    _btn_textures[texture_index].render(ren);
}

void Button::on_event(const yaschperitsy::core::events::EventSPtr& event)
{
    core::events::EventDispatcher ed{event};

    ed.dispatch<yaschperitsy::core::events::MouseMovedEvent>(
        [this](const yaschperitsy::core::events::MouseMovedEventSPtr& event)
        { return hover(event); });

    ed.dispatch<yaschperitsy::core::events::MouseButtonPressedEvent>(
        [this](const yaschperitsy::core::events::MouseButtonPressedEventSPtr&
                   event) { return click(event); });

    ed.dispatch<yaschperitsy::core::events::MouseButtonReleasedEvent>(
        [this](const yaschperitsy::core::events::MouseButtonReleasedEventSPtr&
                   event) { return released(event); });
}

bool Button::is_intersect(int x, int y) const
{
    auto dest = _btn_textures[texture_index].rect();
    int _x = dest.x;
    int _y = dest.y;
    int _w = dest.w;
    int _h = dest.h;

    if (x < _x || x > _x + _w)
    {
        return false;
    }

    if (y < _y || y > _y + _h)
    {
        return false;
    }

    return true;
}

bool Button::released(const core::events::MouseButtonReleasedEventSPtr& /*e*/)
{
    _is_pressed = false;
    return true;
}

bool Button::click(const core::events::MouseButtonPressedEventSPtr& e)
{
    int x = e->x_pos();
    int y = e->y_pos();

    if (is_intersect(x, y))
    {
        _is_pressed = true;
        _event_callback(std::make_shared<events::UIEvent>(_code));
    }

    return true;
}

bool Button::hover(const core::events::MouseMovedEventSPtr& e)
{
    int x = e->x_pos();
    int y = e->y_pos();

    _is_hover = is_intersect(x, y);
    return true;
}

}; // namespace yaschperitsy::game::ui
