#include "MainMenuLayer.hpp"

namespace yaschperitsy::game::layers
{

void MainMenuLayer::render(const core::renderer::SDLRendererUPtr& ren)
{
    _new_game_button.render(ren);
    _settings_button.render(ren);
    _exit_button.render(ren);
}

void MainMenuLayer::on_event(const yaschperitsy::core::events::EventSPtr& event)
{
    _new_game_button.on_event(event);
    _settings_button.on_event(event);
    _exit_button.on_event(event);
}

}; // namespace yaschperitsy::game::layers
