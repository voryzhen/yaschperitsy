#pragma once

#include "ECS/Entity.hpp"
#include "ECS/TypesID.hpp"
#include <cstdint>

enum class AmmoType : uint8_t
{
    PlayerBuller = 0,
    YaschperitsaFireball
};

class Ammo : public Entity
{
    public:
        explicit Ammo(AmmoType type)
            : Entity(get_entity_typeID<Ammo>()), type_(type)
        {
        }

        AmmoType type() const { return type_; }

    private:
        AmmoType type_ { AmmoType::PlayerBuller };
};
