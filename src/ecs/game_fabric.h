#pragma once

#include "app/resource_manager.h"
#include <ecs/entity.h>
#include <memory>

namespace yaschperitsy::ecs
{

class GameFabric
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

using GameFabricUPtr = std::unique_ptr<GameFabric>;

}; // namespace yaschperitsy::ecs
