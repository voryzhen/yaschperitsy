#pragma once

#include <algorithm>
#include <app/resource_manager.h>
#include <ecs/entity.h>
#include <ecs/game_fabric.h>
#include <iterator>
#include <utility>

namespace yaschperitsy::ecs
{

class Manager
{
    public:
        void update(const SDL_Event& event)
        {
            std::for_each(_entities.begin(), _entities.end(),
                          [&](auto& e) { e->update(event); });
        }

        void render(const app::SDL_RendererUPtr& renderer)
        {
            std::for_each(_entities.begin(), _entities.end(),
                          [&](auto& e) { e->render(renderer); });
        }

        void refresh()
        {
            const auto& remove_it = std::remove_if(
                _entities.begin(), _entities.end(),
                [](const auto& e) { return !e->is_active(); });

            _entities.erase(remove_it, _entities.end());
        }

        EntitySPtr add_entity(EntityType type, float x_pox, float y_pox,
                              int speed,
                              const resource::TextureSPtr& texture)
        {
            switch (type)
            {
            case EntityType::player:
                _entities.emplace_back(
                    yaschperitsy::ecs::EntityCreator::create_player(
                        x_pox, y_pox, speed, texture));
                break;
            case EntityType::enemy:
                _entities.emplace_back(
                    yaschperitsy::ecs::EntityCreator::create_enemy(
                        x_pox, y_pox, speed, texture));
                break;
            case EntityType::pbullet:
                _entities.emplace_back(
                    yaschperitsy::ecs::EntityCreator::create_pbullet(
                        x_pox, y_pox, speed, texture));
                break;
            case EntityType::ebullet:
                _entities.emplace_back(
                    yaschperitsy::ecs::EntityCreator::create_ebullet(
                        x_pox, y_pox, speed, texture));
                break;
            default:
                break;
            };

            return _entities.back();
        }

        const SEntityVector& get_entities() const { return _entities; }

        // TODO: delete
        SEntityVector get_entities(EntityType type)
        {
            SEntityVector res;
            std::copy_if(_entities.begin(), _entities.end(),
                         std::back_inserter(res),
                         [&](const EntitySPtr& e)
                         { return e->type() == type; });
            return res;
        }

    private:
        SEntityVector _entities;
};

}; // namespace yaschperitsy::ecs
