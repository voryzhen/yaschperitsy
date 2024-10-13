#include "YaschperitsyController.hpp"

#include "ECS/Components/FireComponent.hpp"
#include "ECS/Components/SpriteComponent.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "Entities/Ammo.hpp"
#include "Entities/Player.hpp"
#include "Entities/Yaschperitsa.hpp"
#include "GraphicEngine/Types.hpp"
#include "Logger/Logger.hpp"
#include "Utility/Vector.hpp"

#include <random>

namespace
{
Vector2D<float> calculate_bullet_pos(const EntityPtr& shooter)
{
    auto pos = shooter->get_component<TransformComponent>()->position();
    auto dir = shooter->get_component<TransformComponent>()->view_direction();
    auto region = shooter->get_component<SpriteComponent>()->render_data();

    Vector2D<float> shoter_center = { .x = pos.x + region.w / 2,
                                      .y = pos.y + region.h / 2 };

    return shoter_center + dir * 100;
}

template <typename T>
T get_random(T max)
{
    std::random_device rd;
    std::mt19937 mt(rd());

    std::uniform_real_distribution<double> dist(0, max);
    return static_cast<T>(dist(mt));
}

Vector2D<float> generate_random_pos(int win_width, int win_height)
{
    const int perimeter = 2 * (win_width + win_height);
    int pos_factor = get_random<int>(perimeter);

    // Window vertices factors
    int vf1 = win_width;
    int vf2 = win_width + win_height;
    int vf3 = (2 * win_width) + win_height;

    if (pos_factor < vf1)
    {
        return { .x = static_cast<float>(pos_factor), .y = 0 };
    }
    if (pos_factor > vf1 && pos_factor < vf2)
    {
        return { .x = static_cast<float>(win_width),
                 .y = static_cast<float>(pos_factor - vf1) };
    }
    if (pos_factor > vf2 && pos_factor < vf3)
    {
        return { .x = static_cast<float>(pos_factor - vf2),
                 .y = static_cast<float>(win_height) };
    }
    return { .x = 0, .y = static_cast<float>(pos_factor - vf3) };
}

Vector2D<float> velocity_direction(Vector2D<float> pos, Vector2D<float> aim)
{
    auto vec = aim - pos;
    vec.normalize();
    return vec;
}

} // namespace

void YaschperitsyController::spawn_yaschperitsy()
{
    if (--yaschperitsy_spawn_timer_ < 0 &&
        game_info_.statistics_._yaschperitsy_num > 0)
    {
        game_info_.statistics_._yaschperitsy_num--;

        // Yaschperitsy texture randomizer
        // 2 different yaschperitsy
        const RenderData yasch_texture =
            (get_random<int>(2) == 1) ? yaschperitsa_1_ : yaschperitsa_2_;

        Vector2D<float> pos = generate_random_pos(win_width_, win_height_);
        Vector2D<float> vel = velocity_direction(
            pos, { .x = static_cast<float>(win_width_) / 2,
                   .y = static_cast<float>(win_height_) / 2 });

        EntityPtr yaschperitsa = std::make_shared<Yaschperitsa>();
        yaschperitsa->add_component<TransformComponent>(pos.x, pos.y);
        yaschperitsa->add_component<SpriteComponent>(yasch_texture);
        yaschperitsa->add_component<FireComponent>();
        yaschperitsa->get_component<TransformComponent>()->set_direction(vel);
        yaschperitsa->get_component<TransformComponent>()->set_view_direction(
            vel);
        man_->add_entity(yaschperitsa);

        yaschperitsy_spawn_timer_ =
            game_info_.settings_.yaschperitsy_spawn_freq_ *
            static_cast<int>(60 * get_random<double>(2.0));
    }
}

void YaschperitsyController::update_direction()
{
    auto player = man_->get_entities<Player>().front();
    auto player_pos = player->get_component<TransformComponent>()->position();

    for (auto& Yaschperitsa : man_->get_entities<Yaschperitsa>())
    {
        auto transform = Yaschperitsa->get_component<TransformComponent>();

        auto vel = velocity_direction(transform->position(), player_pos);

        transform->set_direction(vel);
        transform->set_view_direction(vel);
    }
}

void YaschperitsyController::fire()
{
    for (auto& yaschperitsa : man_->get_entities<Yaschperitsa>())
    {
        const auto fire_component =
            yaschperitsa->get_component<FireComponent>();

        if (fire_component && fire_component->reloaded())
        {
            fire_component->shot();

            const auto yaschperitsa_dir =
                yaschperitsa->get_component<TransformComponent>()->direction();

            auto bullet_pos = calculate_bullet_pos(yaschperitsa);

            EntityPtr yaschperitsa_fire =
                std::make_shared<Ammo>(AmmoType::YaschperitsaFireball);

            yaschperitsa_fire->add_component<TransformComponent>(bullet_pos,
                                                                 5.0);

            yaschperitsa_fireball_.x = bullet_pos.x;
            yaschperitsa_fireball_.y = bullet_pos.y;

            yaschperitsa_fire->add_component<SpriteComponent>(
                yaschperitsa_fireball_);

            yaschperitsa_fire->get_component<TransformComponent>()
                ->set_direction(yaschperitsa_dir);

            man_->add_entity(yaschperitsa_fire);

            // There is no angle because texture has round symmetry
        }
    }
}

void YaschperitsyController::update()
{
    spawn_yaschperitsy();
    update_direction();

    // auto player = man_->get_entities<Player>();
    // auto yaschperitsy = man_->get_entities<Yaschperitsa>();
    // Logger().info("Players num: {}, yaschperitsy num: {}", player.size(),
    //               yaschperitsy.size());

    fire();
}
