#pragma once

#include "GameSettings.hpp"
#include "core/utility/Utility.h"
#include "ecs/Manager.hpp"
#include "game/game/Assets.hpp"

namespace yaschperitsy::game::YaschperitsyController
{

class YaschperitsyController
{
    public:
        YaschperitsyController(ecs::Manager& man, GameSettings& settings)
            : _man(man), _settings(settings)
        {
        }

        void spawn_yaschperitsy()
        {
            if (--yaschperitsy_spawn_timer < 0)
            {
                // Yaschperitsy texture randomizer
                // 2 different yaschperitsy
                const auto name = (get_random<int>(2) == 1) ? "yaschperitsa_1"
                                                            : "yaschperitsa_2";

                auto yaschperitsa = _man.add_entity<Organism>(
                    ecs::EntityType::yaschperitsa, 740, 200,
                    _settings._yaschperitsy_speed,
                    assets::Assets::texture(name));

                auto transform_comp =
                    yaschperitsa
                        ->get_component<ecs::components::TransformComponent>();

                transform_comp->set_velocity({-1., 0.});

                yaschperitsy_spawn_timer =
                    _settings._yaschperitsy_spawn_freq *
                    static_cast<int>(60 * get_random<double>(2.0));
            }
        }

    private:
        ecs::Manager& _man;
        GameSettings& _settings;

        int yaschperitsy_spawn_timer{0};
};

}; // namespace yaschperitsy::game::YaschperitsyController
