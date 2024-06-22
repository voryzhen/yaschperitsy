#pragma once

#include "app/ResourceManager.h"
#include <ecs/Entity.h>
#include <memory>

namespace yaschperitsy::ecs
{

class EntityCreator
{
    public:
        static EntitySPtr create_player(float x_pox, float y_pox,
                                        int speed,
                                        resource::TextureSPtr texture);
        static EntitySPtr create_enemy(float x_pox, float y_pox,
                                       int speed,
                                       resource::TextureSPtr texture);
        static EntitySPtr create_ebullet(float x_pox, float y_pox,
                                         int speed,
                                         resource::TextureSPtr texture);
        static EntitySPtr create_pbullet(float x_pox, float y_pox,
                                         int speed,
                                         resource::TextureSPtr texture);

    private:
        static EntitySPtr create_entity(EntityType type, float x_pox,
                                        float y_pox, int speed,
                                        resource::TextureSPtr texture);
};

}; // namespace yaschperitsy::ecs
