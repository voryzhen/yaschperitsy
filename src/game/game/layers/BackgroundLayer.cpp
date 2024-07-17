#include "game/game/layers/BackgroundLayer.hpp"

namespace yaschperitsy::game::layers
{

void BackgroundLayer::render(const core::renderer::SDLRendererUPtr& ren)
{
    _background.render(ren);
}

void BackgroundLayer::on_event(
    const yaschperitsy::core::events::EventSPtr& event)
{
}

}; // namespace yaschperitsy::game::layers
