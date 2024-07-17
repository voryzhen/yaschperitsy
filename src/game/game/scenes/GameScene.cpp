#include "GameScene.hpp"
#include "SDL_scancode.h"
#include "core/input/Input.hpp"
#include "ecs/components/TransformComponent.hpp"
#include "ecs/entities/Ammunition.hpp"
#include "ecs/entities/Organism.hpp"
#include "game/game/Assets.hpp"
#include "game/game/layers/BackgroundLayer.hpp"
#include "game/game/layers/StateInfoLayer.hpp"
#include <memory>

namespace yaschperitsy::game::scenes
{

void GameScene::update()
{
    Scene::update();

    _manager.refresh();
    _manager.update({}); // SDL_Event refactor

    yash_ctrl.update();
    player_update();

    destroy_objects();
}

GameScene::GameScene(std::string name, const core::LayerStack& layers)
    : Scene(std::move(name), layers)
{
    push_layer(std::make_shared<layers::BackgroundLayer>());
    push_layer(std::make_shared<layers::StateInfoLayer>(_game_info.statistics));

    _manager.add_entity<Organism>(ecs::EntityType::player, 640, 360,
                                  _game_info.settings._player_speed,
                                  assets::Assets::player());
}

void GameScene::destroy_objects()
{
    for (auto& e : _manager.get_entities())
    {
        if (e->type() == ecs::EntityType::player)
        {
            continue;
        }

        auto pos =
            e->get_component<ecs::components::TransformComponent>()->position();

        auto x = pos.x();
        auto y = pos.y();

        // Relating to rad of yaschperitsy generation
        if (x < -1000 || x > 2300 || y < -1000 || y > 1900)
        {
            e->destroy();
        }
    }
    bullet_hit();
}

void GameScene::player_update()
{
    player_fire();

    auto player = _manager.get_entities(ecs::EntityType::player).front();
    _game_info.statistics._curr_hp =
        std::static_pointer_cast<Organism>(player)->health();
}

void GameScene::player_fire()
{
    auto player = _manager.get_entities(ecs::EntityType::player).front();

    const auto fire_comp =
        player->get_component<ecs::components::FireComponent>();

    if (fire_comp->reloaded())
    {
        bool is_fire = core::input::Input::is_key_pressed(SDL_SCANCODE_F) ||
                       core::input::Input::is_mouse_button_pressed(
                           core::input::MOUSE_BUTTON::left);

        if (is_fire)
        {
            fire_comp->shot();

            const auto player_transform =
                player->get_component<ecs::components::TransformComponent>();

            const auto pos = player_transform->position();

            auto bullet = _manager.add_entity<Ammunition>(
                AmmunitionType::plasma_shot, pos.x(), pos.y(),
                _game_info.settings._bullet_speed,
                assets::Assets::texture("player_bullet"));

            auto bullet_trans_comp =
                bullet->get_component<ecs::components::TransformComponent>();

            bullet_trans_comp->set_angle(player_transform->angle());
            bullet_trans_comp->set_velocity(player_transform->direction());
        }
    }
}

namespace
{

bool intersect(SDL_Rect r1, SDL_Rect r2)
{
    if (r1.x > r2.x + r2.w)
    {
        return false;
    }
    if (r1.x + r1.w < r2.x)
    {
        return false;
    }
    if (r1.y > r2.y + r2.h)
    {
        return false;
    }
    if (r1.y + r1.w < r2.y)
    {
        return false;
    }

    return true;
}

bool intersect(const ecs::EntitySPtr& ent1, const ecs::EntitySPtr& ent2)
{
    const auto rect1 =
        ent1->get_component<ecs::components::SpriteComponent>()->texture_rect();
    const auto rect2 =
        ent2->get_component<ecs::components::SpriteComponent>()->texture_rect();
    return intersect(rect1, rect2);
}

}; // namespace

void GameScene::bullet_hit()
{
    const auto bullets = _manager.get_entities(ecs::EntityType::ammunition);
    const auto yaschperitsy =
        _manager.get_entities(ecs::EntityType::yaschperitsa);
    const auto player = std::static_pointer_cast<Organism>(
        _manager.get_entities(ecs::EntityType::player).front());

    // strike
    for (const auto& bullet : bullets)
    {
        if (intersect(player, bullet))
        {
            auto ammunition = std::static_pointer_cast<Ammunition>(bullet);

            if (ammunition->ammo_type() ==
                AmmunitionType::yaschperitsy_fireball)
            {
                player->damage(ammunition->damage());

                if (player->health() < 1)
                {
                    //             reset_state();
                }
                ammunition->destroy();
            }
        }

        for (const auto& yaschperitsa : yaschperitsy)
        {
            if (!intersect(yaschperitsa, bullet))
            {
                continue;
            }
            auto type =
                std::static_pointer_cast<Ammunition>(bullet)->ammo_type();

            // Immune to their own fireballs
            if (type == AmmunitionType::plasma_shot)
            {
                yaschperitsa->destroy();
                bullet->destroy();
                _game_info.statistics._score++;
                if (_game_info.statistics._score >
                    _game_info.statistics._max_score)
                {
                    _game_info.statistics._max_score++;
                }
            }
        }
    }

    // // yaschperitsy bite
    // for (const auto& yaschperitsa : yaschperitsy)
    // {
    //     if (intersect(_player, yaschperitsa))
    //     {
    //         // reset_state();
    //     }
    // }
}

}; // namespace yaschperitsy::game::scenes
