#pragma once

#include "GameSettings.hpp"
#include "ecs/Manager.hpp"

namespace yaschperitsy::game::YaschperitsyController
{

class YaschperitsyController
{
    public:
        YaschperitsyController(ecs::Manager& man, GameSettings& settings)
            : _man(man), _settings(settings)
        {
        }

        void spawn_yaschperitsy();
        void update();

    private:
        void update_direction();
        void fire();

        ecs::Manager& _man;
        GameSettings& _settings;

        int yaschperitsy_spawn_timer{0};
};

}; // namespace yaschperitsy::game::YaschperitsyController
