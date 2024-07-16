#include "SettingsMenuLayer.hpp"

namespace yaschperitsy::game::layers
{

void SettingsMenuLayer::render(const core::renderer::SDLRendererUPtr& ren)
{
    _back_button.render(ren);
}

void SettingsMenuLayer::on_event(
    const yaschperitsy::core::events::EventSPtr& event)
{
    _back_button.on_event(event);
}

}; // namespace yaschperitsy::game::layers
