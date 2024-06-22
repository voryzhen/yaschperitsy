#include "ecs/Entity.h"
#include "ecs/components/FireComponent.h"
#include "ecs/components/KeyboardController.h"
#include "ecs/components/MouseController.h"
#include "ecs/components/SpriteComponent.h"
#include "ecs/components/TransformComponent.h"
#include <ecs/EntityCreator.h>

#include <memory>
#include <utility>

namespace yaschperitsy::ecs
{

EntitySPtr EntityCreator::create_entity(EntityType type, float x_pox,
                                        float y_pox, int speed,
                                        resource::TextureSPtr texture)
{
    auto entity = std::make_shared<Entity>(type);
    entity->add_component<components::TransformComponent>(x_pox, y_pox,
                                                          speed);
    entity->add_component<components::SpriteComponent>(texture);
    return entity;
}

EntitySPtr EntityCreator::create_player(float x_pox, float y_pox,
                                        int speed,
                                        resource::TextureSPtr texture)
{
    auto entity = create_entity(EntityType::player, x_pox, y_pox, speed,
                                std::move(texture));
    entity->add_component<components::KeyboardController>();
    entity->add_component<components::MouseController>();
    entity->add_component<components::FireComponent>(8);
    return entity;
}

EntitySPtr EntityCreator::create_enemy(float x_pox, float y_pox,
                                       int speed,
                                       resource::TextureSPtr texture)
{
    auto entity = create_entity(EntityType::enemy, x_pox, y_pox, speed,
                                std::move(texture));
    entity->get_component<components::SpriteComponent>()
        ->set_sprite_settings(2, 100);
    entity->add_component<ecs::components::FireComponent>(60);
    return entity;
}

EntitySPtr EntityCreator::create_ebullet(float x_pox, float y_pox,
                                         int speed,
                                         resource::TextureSPtr texture)
{
    auto entity = create_entity(EntityType::ebullet, x_pox, y_pox,
                                speed, std::move(texture));
    return entity;
}

EntitySPtr EntityCreator::create_pbullet(float x_pox, float y_pox,
                                         int speed,
                                         resource::TextureSPtr texture)
{
    auto entity = create_entity(EntityType::pbullet, x_pox, y_pox,
                                speed, std::move(texture));
    return entity;
}

}; // namespace yaschperitsy::ecs
