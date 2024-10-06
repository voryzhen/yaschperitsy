#include "Manager.hpp"

void Manager::events()
{
    std::ranges::for_each(entities_,
                          [&](const auto& entity) { entity->events(); });
}

void Manager::update()
{
    std::ranges::for_each(entities_,
                          [&](const auto& entity) { entity->update(); });
}

void Manager::render(const Renderer& ren)
{
    std::ranges::for_each(entities_,
                          [&](const auto& entity) { entity->render(ren); });
}

void Manager::on_event(const EventSPtr& event)
{
    std::ranges::for_each(entities_,
                          [&](const auto& entity) { entity->on_event(event); });
}

void Manager::add_entity(const EntityPtr& entity) // Add creator
{
    entities_.push_back(entity);
}

void Manager::refresh()
{
    auto removed_entity = std::ranges::remove_if(
        entities_, [](const auto& entity) { return !entity->is_active(); });
    entities_.erase(removed_entity.begin(), entities_.end());
}
