#pragma once

#include "ecs/Entity.h"
#include <ecs/components/Components.h>

namespace yaschperitsy::game
{

enum class AmmunitionType
{
    yaschperitsy_fireball = 0,
    plasma_shot
};

class Ammunition : public yaschperitsy::ecs::Entity
{
    public:
        Ammunition(AmmunitionType ammo_type)
            : Entity(ecs::EntityType::ammunition), _ammo_type(ammo_type)
        {
        }

        int damage() const { return _damage; }

        AmmunitionType ammo_type() const { return _ammo_type; }

    private:
        int _damage = 1;
        AmmunitionType _ammo_type;
};

}; // namespace yaschperitsy::game
