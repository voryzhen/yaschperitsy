#include "GameEndLayer.hpp"

namespace yaschperitsy::game::layers
{

void GameEndLayer::render(const core::renderer::SDLRendererUPtr& ren)
{
    _label.render(ren);
    new_game_button.render(ren);
    exit_button.render(ren);
}

void GameEndLayer::on_event(const yaschperitsy::core::events::EventSPtr& event)
{
    new_game_button.on_event(event);
    // settings_button.on_event(event);
    exit_button.on_event(event);
}

}; // namespace yaschperitsy::game::layers
