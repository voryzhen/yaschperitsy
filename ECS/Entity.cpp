#include "Entity.hpp"

#include "Components/SpriteComponent.hpp"

#include <algorithm>

namespace
{

bool intersect(const RenderData& r1, const RenderData& r2)
{
    if (r1.x > r2.x + r2.w)
    {
        return false;
    }
    if (r1.x + r1.w < r2.x)
    {
        return false;
    }
    if (r1.y > r2.y + r2.h)
    {
        return false;
    }
    if (r1.y + r1.w < r2.y)
    {
        return false;
    }

    return true;
}

}; // namespace

void Entity::events()
{
    std::ranges::for_each(components_,
                          [&](auto& component) { component.second->events(); });
}

void Entity::update()
{
    std::ranges::for_each(components_,
                          [&](auto& component) { component.second->update(); });
}

void Entity::render(const Renderer& ren)
{
    std::ranges::for_each(components_, [&](auto& component)
                          { component.second->render(ren); });
}

void Entity::on_event(const EventSPtr& event)
{
    std::ranges::for_each(components_, [&](auto& component)
                          { component.second->on_event(); });
}

bool Entity::is_intersect(const EntityPtr& entity) const
{
    const auto rect1 = get_component<SpriteComponent>()->render_data();
    const auto rect2 = entity->get_component<SpriteComponent>()->render_data();
    return intersect(rect1, rect2);
}
