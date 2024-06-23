#pragma once

#include "ecs/Entity.h"
#include <ecs/components/Components.h>

namespace yaschperitsy::game
{

class Organism : public yaschperitsy::ecs::Entity
{
    public:
        Organism(ecs::EntityType type) : Entity(type) {}

        int health() const { return _health; }

        void damage(int damage) { _health -= damage; }

        void heal(int health) { _health += health; }

        void reset_state()
        {
            _health = 100;
            auto transform_comp =
                get_component<ecs::components::TransformComponent>();

            transform_comp->set_position(640, 360);
            transform_comp->set_velocity({0.0, 0.0});
        }

    private:
        int _health = 100;
};

}; // namespace yaschperitsy::game
