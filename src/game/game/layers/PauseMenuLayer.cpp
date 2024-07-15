#include "PauseMenuLayer.hpp"

namespace yaschperitsy::game::layers
{

void PauseMenuLayer::render(SDL_Renderer* ren)
{
    resume_button.render(ren);
    exit_button.render(ren);
}

void PauseMenuLayer::on_event(
    const yaschperitsy::core::events::EventSPtr& event)
{
    resume_button.on_event(event);
    exit_button.on_event(event);
}

}; // namespace yaschperitsy::game::layers
