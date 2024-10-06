#pragma once

#include "ECS/Components/FireComponent.hpp"
#include "ECS/Components/KeyboardController.hpp"
#include "ECS/Components/MouseController.hpp"
#include "ECS/Components/SpriteComponent.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Entity.hpp"
#include "ECS/Manager.hpp"
#include "Entities/Ammo.hpp"
#include "Entities/Player.hpp"
#include "GraphicEngine/ResourceManager/ResourceManager.hpp"
#include "GraphicEngine/Types.hpp"
#include "Scenes/GameScene/GameSettings.hpp"
#include "Utility/Vector.hpp"
#include <cmath>
#include <memory>

const static auto* player_asset = "Assets/Player/player.png";
const static auto* player_bullet_asset = "Assets/Player/player_bullet.png";

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
}; // namespace

class PlayerController
{
    public:
        PlayerController(ManagerPtr& man, const ResourceManager& rm,
                         int win_width, int win_height)
            : man_(man), rm_(rm)
        {
            player_ = rm_.load_texture(player_asset);
            player_bullet_ = rm_.load_texture(player_bullet_asset);

            // Init player
            EntityPtr player = std::make_shared<Player>();

            auto player_texture_data = rm_.load_texture(player_asset);
            auto player_x_init_pos = (win_width - player_texture_data.w) * 0.5;
            auto player_y_init_pos = (win_height - player_texture_data.h) * 0.5;

            player->add_component<TransformComponent>(player_x_init_pos,
                                                      player_y_init_pos);
            player->add_component<KeyboardController>();
            player->add_component<MouseController>();
            player->add_component<SpriteComponent>(player_texture_data);
            player->add_component<FireComponent>(8);

            man_->add_entity(player);
        }

        void update() { fire(); }

    private:
        void fire()
        {
            auto player = man_->get_entities<Player>().front();
            if (!player)
            {
                return;
            }

            const auto fire_comp = player->get_component<FireComponent>();
            if (!fire_comp)
            {
                return;
            }

            if (fire_comp->reloaded())
            {
                bool is_fire =
                    Input::is_key_pressed(KEYS::F) ||
                    Input::is_mouse_button_pressed(MOUSE_BUTTON::Left);

                if (is_fire)
                {
                    fire_comp->shot();

                    const auto player_transform =
                        player->get_component<TransformComponent>();

                    auto bullet_pos = calculate_bullet_pos(player);

                    player_bullet_.x = bullet_pos.x;
                    player_bullet_.y = bullet_pos.y;

                    EntityPtr player_bullet =
                        std::make_shared<Ammo>(AmmoType::PlayerBuller);
                    player_bullet->add_component<TransformComponent>(bullet_pos,
                                                                     10);
                    player_bullet->get_component<TransformComponent>()
                        ->set_direction(player_transform->view_direction());
                    player_bullet->get_component<TransformComponent>()
                        ->set_view_direction(
                            player_transform->view_direction());
                    player_bullet->add_component<SpriteComponent>(
                        player_bullet_);

                    man_->add_entity(player_bullet);
                }
            }
        }

        ManagerPtr& man_;
        const ResourceManager& rm_;

        RenderData player_;
        RenderData player_bullet_;
};
using PlayerControllerPtr = std::shared_ptr<PlayerController>;
