#include "PauseMenuLayer.hpp"

namespace yaschperitsy::game::layers
{

void PauseMenuLayer::render(const core::renderer::SDLRendererUPtr& ren)
{
    _resume_button.render(ren);
    _exit_button.render(ren);
}

void PauseMenuLayer::on_event(
    const yaschperitsy::core::events::EventSPtr& event)
{
    _resume_button.on_event(event);
    _exit_button.on_event(event);
}

}; // namespace yaschperitsy::game::layers
