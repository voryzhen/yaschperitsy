#include "GameScene.hpp"
#include "ECS/Components/KeyboardController.hpp"
#include "ECS/Components/MouseController.hpp"
#include "ECS/Components/SpriteComponent.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/TypesID.hpp"
#include "Entities/Ammo.hpp"
#include "Entities/Player.hpp"
#include "Entities/Yaschperitsa.hpp"
#include "Events/UIEvent.hpp"
#include "GraphicEngine/Types.hpp"
#include "Logger/Logger.hpp"
#include "Scenes/GameScene/PlayerController.hpp"
#include "Scenes/GameScene/UIController.hpp"
#include "Scenes/GameScene/YaschperitsyController.hpp"
#include "Yaschperitsy/Style.hpp"
#include <memory>

GameScene::GameScene(const ResourceManager& rm, EventCallbackFn callback,
                     int win_width, int win_height)
    : rm_(rm), callback_(std::move(callback)), win_width_(win_width),
      win_height_(win_height)
{
    ui_ = std::make_shared<UIController>(man_, rm_, game_info_, win_width,
                                         win_height);

    yasch_ = std::make_shared<YaschperitsyController>(man_, rm_, game_info_,
                                                      win_width, win_height);
    player_ =
        std::make_shared<PlayerController>(man_, rm_, win_width, win_height);
}

void GameScene::on_event(const EventSPtr& event) { Scene::on_event(event); }

void GameScene::events() { Scene::events(); }

void GameScene::update()
{
    Scene::update();

    man_->refresh();

    yasch_->update();
    player_->update();
    ui_->update();

    bullet_hit();
    destroy_objects();

    // Logger().info("Entity nums: {}", man_->get_entities().size());
}

void GameScene::render(const Renderer& ren) { Scene::render(ren); }

void GameScene::destroy_objects()
{
    for (auto& entity : man_->get_entities<Ammo>())
    {
        auto entity_position =
            entity->get_component<TransformComponent>()->position();

        if (outfield(entity_position))
        {
            entity->destroy();
        }
    }
}

bool GameScene::outfield(const Vector2D<float>& position)
{
    int offset = 100;
    if (position.x < -offset)
    {
        return true;
    }
    if (position.x > win_width_ + offset)
    {
        return true;
    }
    if (position.y < -offset)
    {
        return true;
    }
    if (position.y > win_height_ + offset)
    {
        return true;
    }

    return false;
}

void GameScene::bullet_hit()
{
    const auto& bullets = man_->get_entities<Ammo>();
    const auto& player = man_->get_entities<Player>();
    const auto& yaschperitsy = man_->get_entities<Yaschperitsa>();

    for (const auto& bullet : bullets)
    {
        // Strike
        if (player.front()->is_intersect(bullet))
        {
            bullet->destroy();
            game_info_.statistics._curr_hp--;
            // player - hp
            // player->damage(ammunition->damage());
        }

        for (const auto& yaschperitsa : yaschperitsy)
        {
            // Yasch immune to their own fireballs
            if (auto ammo = std::static_pointer_cast<Ammo>(bullet);
                ammo->type() != AmmoType::YaschperitsaFireball)
            {
                if (yaschperitsa->is_intersect(bullet))
                {
                    yaschperitsa->destroy();
                    bullet->destroy();
                    game_info_.statistics._score++;
                    // if (game_info_.statistics._yaschperitsy_num > 0)
                    // {
                    //     game_info_.statistics._yaschperitsy_num--;
                    // }
                }
            }
        }
    }
    if (game_info_.statistics._score == 10)
    {
        reset_state();
        callback_(std::make_shared<UIEvent>(UIEventCode::GameWin));
    }
    // Add yaschperitsy bite
}

void GameScene::reset_state()
{
    for (auto& e : man_->get_entities<Yaschperitsa>())
    {
        e->destroy();
    }

    for (auto& e : man_->get_entities<Ammo>())
    {
        e->destroy();
    }

    game_info_.statistics._max_score = std::max(
        game_info_.statistics._max_score, game_info_.statistics._score);

    game_info_.statistics._score = 0;

    game_info_.statistics._yaschperitsy_num =
        game_info_.statistics._yaschperitsy_total_num;

    game_info_.statistics._curr_hp = 100;
}
