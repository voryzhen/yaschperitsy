#pragma once

#include "GameSettings.hpp"
#include "ecs/Manager.hpp"

namespace yaschperitsy::game::YaschperitsyController
{

class YaschperitsyController
{
    public:
        YaschperitsyController(ecs::Manager& man, GameInfo& info)
            : _man(man), _info(info)
        {
        }

        void spawn_yaschperitsy();
        void update();

    private:
        void update_direction();
        void fire();

        ecs::Manager& _man;
        GameInfo& _info;

        int yaschperitsy_spawn_timer{0};
};

}; // namespace yaschperitsy::game::YaschperitsyController
