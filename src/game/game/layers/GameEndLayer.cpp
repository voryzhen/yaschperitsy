#include "GameEndLayer.hpp"

namespace yaschperitsy::game::layers
{

void GameEndLayer::render(const core::renderer::SDLRendererUPtr& ren)
{
    _label.render(ren);
    _new_game_button.render(ren);
    _exit_button.render(ren);
}

void GameEndLayer::on_event(const yaschperitsy::core::events::EventSPtr& event)
{
    _new_game_button.on_event(event);
    _exit_button.on_event(event);
}

}; // namespace yaschperitsy::game::layers
