#include "core/ecs/Entity.h"
#include <core/ecs/EntityCreator.h>

#include <game/entities/Ammunition.h>
#include <game/entities/Organism.h>

#include <memory>
#include <utility>

namespace yaschperitsy::ecs
{

void EntityCreator::init_components(EntitySPtr entity, float x_pox,
                                    float y_pox, int speed,
                                    resource::TextureSPtr texture)
{

    entity->add_component<components::TransformComponent>(x_pox, y_pox,
                                                          speed);

    if (texture != nullptr)
    {
        entity->add_component<components::SpriteComponent>(texture);
    }
    else
    {
        entity->add_component<components::SpriteComponent>();
    }

    switch (entity->type())
    {
    case EntityType::yaschperitsa:
        init_yaschperitsa_components(entity);
        break;
    case EntityType::player:
        init_player_components(entity);
        break;
    case EntityType::ammunition:
        init_ammunition_components(entity);
        break;
    default:
        break;
    }
}

void EntityCreator::init_yaschperitsa_components(EntitySPtr& entity)
{
    entity->get_component<components::SpriteComponent>()
        ->set_sprite_settings(2, 100);
    entity->add_component<ecs::components::FireComponent>(60);
}

void EntityCreator::init_player_components(EntitySPtr& entity)
{
    entity->add_component<components::KeyboardController>();
    entity->add_component<components::MouseController>();
    entity->add_component<components::FireComponent>(8);
}

void EntityCreator::init_ammunition_components(EntitySPtr& entity) {}

}; // namespace yaschperitsy::ecs
