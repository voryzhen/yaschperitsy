#include "MainMenu.hpp"

#include "core/events/MouseEvent.hpp"

namespace yaschperitsy::game::ui::main_menu
{

void MainMenuLayer::render(SDL_Renderer* ren)
{
    SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(ren, &rect);
}

void MainMenuLayer::on_event(const yaschperitsy::core::events::EventSPtr& event)
{
    if (event->event_type() ==
        yaschperitsy::core::events::EventType::MouseMoved)
    {
        auto e = std::dynamic_pointer_cast<
            yaschperitsy::core::events::MouseMovedEvent>(event);
        color.b = e->x_pos() % 255;
        color.r = e->y_pos() % 255;
    }
}

}; // namespace yaschperitsy::game::ui::main_menu
