#include "MainMenuLayer.hpp"

namespace yaschperitsy::game::layers
{

void MainMenuLayer::render(const core::renderer::SDLRendererUPtr& ren)
{
    new_game_button.render(ren);
    settings_button.render(ren);
    exit_button.render(ren);
}

void MainMenuLayer::on_event(const yaschperitsy::core::events::EventSPtr& event)
{
    new_game_button.on_event(event);
    settings_button.on_event(event);
    exit_button.on_event(event);
}

}; // namespace yaschperitsy::game::layers
