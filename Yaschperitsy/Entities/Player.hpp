#pragma once

#include "ECS/Entity.hpp"
#include "ECS/TypesID.hpp"

class Player : public Entity
{
    public:
        Player() : Entity(get_entity_typeID<Player>()) {}
};
