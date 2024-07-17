#pragma once

#include "core/resource_manager/ResourceManager.hpp"
#include "ecs/components/FireComponent.hpp"
#include "ecs/components/KeyboardController.hpp"
#include "ecs/components/MouseController.hpp"
#include "ecs/components/SpriteComponent.hpp"
#include "ecs/components/TransformComponent.hpp"
#include "ecs/entities/Ammunition.hpp"
#include "ecs/entities/Organism.hpp"
#include <ecs/Entity.hpp>
#include <memory>
#include <utility>

namespace yaschperitsy::ecs
{

class EntityCreator
{
    public:
        template <typename T, typename Type, typename... TArgs>
        static EntitySPtr create_entity(Type type, TArgs&&... args)
        {
            auto entity = std::shared_ptr<T>(new T(type));

            int args_size = sizeof...(args);
            if (args_size > 0)
            {
                init_components(entity, std::forward<TArgs>(args)...);
            }

            return entity;
        }

    private:
        static void init_components(EntitySPtr entity, float x_pox, float y_pox,
                                    int speed,
                                    core::resources::TextureSPtr texture)
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

        static void init_yaschperitsa_components(EntitySPtr& entity)
        {
            entity->get_component<components::SpriteComponent>()
                ->set_sprite_settings(2, 100);
            entity->add_component<ecs::components::FireComponent>(60);
        }

        static void init_player_components(EntitySPtr& entity)
        {
            entity->add_component<components::KeyboardController>();
            entity->add_component<components::MouseController>();
            entity->add_component<components::FireComponent>(8);
        }

        static void init_ammunition_components(EntitySPtr& entity) {}
};

}; // namespace yaschperitsy::ecs
