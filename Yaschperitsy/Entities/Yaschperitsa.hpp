#pragma once

#include "ECS/Entity.hpp"
#include "ECS/TypesID.hpp"

class Yaschperitsa : public Entity
{
    public:
        Yaschperitsa() : Entity(get_entity_typeID<Yaschperitsa>()) {}
};
