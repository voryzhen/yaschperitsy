#include "YaschperitsyController.hpp"

#include <cmath>
#include <numbers>

#include "core/utility/Utility.h"
#include "core/utility/Vector2D.h"

#include "ecs/Entity.hpp"
#include "game/game/Assets.hpp"

namespace
{

// TODO: refactor with on_event
float half_width = 640;
float half_height = 360;

float rad2 = (half_width * half_width + half_height * half_height);
float rad = sqrt(rad2);

Vector2D<float> generate_start_position()
{
    auto random_angle = get_random<float>(360);
    auto x = rad * cos(random_angle) + half_width;
    auto y = rad * sin(random_angle) + half_height;

    return {x, y};
};

Vector2D<float> velocity_direction(Vector2D<float> pos,
                                   Vector2D<float> aim = {half_width,
                                                          half_height})
{
    auto dx = aim.x() - pos.x();
    auto dy = aim.y() - pos.y();

    auto d2 = dy * dy + dx * dx;
    auto d = sqrt(d2);

    return {dx / d, dy / d};
}

float angle(Vector2D<float> vec)
{
    float rad = 180. / std::numbers::pi_v<float>;
    float angle = 180.f + atan2(vec.y(), vec.x()) * rad;
    return angle;
}

}; // namespace

namespace yaschperitsy::game::YaschperitsyController
{

void YaschperitsyController::spawn_yaschperitsy()
{
    if (--yaschperitsy_spawn_timer < 0) //  && _stat->_yaschperitsy_num > 0)
    {
        // _stat->_yaschperitsy_num--;

        // Yaschperitsy texture randomizer
        // 2 different yaschperitsy
        const auto name =
            (get_random<int>(2) == 1) ? "yaschperitsa_1" : "yaschperitsa_2";

        Vector2D<float> pos = generate_start_position();

        auto yaschperitsa = _man.add_entity<Organism>(
            ecs::EntityType::yaschperitsa, pos.x(), pos.y(),
            _settings._yaschperitsy_speed, assets::Assets::texture(name));

        auto vel = velocity_direction(pos);

        auto transform_comp =
            yaschperitsa->get_component<ecs::components::TransformComponent>();

        transform_comp->set_velocity(vel);

        yaschperitsy_spawn_timer =
            _settings._yaschperitsy_spawn_freq *
            static_cast<int>(60 * get_random<double>(2.0));
    }
}

void YaschperitsyController::update()
{
    spawn_yaschperitsy();
    update_direction();
    fire();
}

void YaschperitsyController::fire()
{
    for (auto& e : _man.get_entities(ecs::EntityType::yaschperitsa))
    {
        const auto fire_component =
            e->get_component<ecs::components::FireComponent>();

        if (fire_component->reloaded())
        {
            fire_component->shot();

            const auto transform =
                e->get_component<ecs::components::TransformComponent>();
            const auto yaschperitsa_pos = transform->position();

            auto bullet = _man.add_entity<Ammunition>(
                AmmunitionType::yaschperitsy_fireball, yaschperitsa_pos.x(),
                yaschperitsa_pos.y(), _settings._bullet_speed,
                assets::Assets::texture("fireball"));

            auto bullet_transform =
                bullet->get_component<ecs::components::TransformComponent>();

            bullet_transform->set_velocity(transform->velocity());
            // There is no angle because texture has round symmetry
        }
    }
}

void YaschperitsyController::update_direction()
{
    auto player = _man.get_entities(ecs::EntityType::player).front();
    auto player_pos =
        player->get_component<ecs::components::TransformComponent>()
            ->position();

    for (auto& e : _man.get_entities(ecs::EntityType::yaschperitsa))
    {
        auto transform =
            e->get_component<ecs::components::TransformComponent>();

        auto vel = velocity_direction(transform->position(), player_pos);

        transform->set_velocity(vel);
        transform->set_angle(angle(vel));
    }
}

}; // namespace yaschperitsy::game::YaschperitsyController
