#include "EntityLayer.hpp"

namespace yaschperitsy::game::layers
{

void EntityLayer::render(const core::renderer::SDLRendererUPtr& ren)
{
    for (auto& ent : _entities)
    {
        ent.render(ren);
    }
}

void EntityLayer::on_event(const yaschperitsy::core::events::EventSPtr& event)
{
}

}; // namespace yaschperitsy::game::layers
