#include "GameScene.hpp"

namespace yaschperitsy::game::scenes
{

void GameScene::update_yaschperitsy()
{
    yash_ctrl.spawn_yaschperitsy();
    // spawn_yaschperitsy(manager);
    // fire_yaschperitsy();
    // update_yaschperitsy_direction();
};

void GameScene::update()
{
    Scene::update();

    _manager.refresh();
    _manager.update({}); // SDL_Event refactor

    update_yaschperitsy();
    destroy_objects();
}

void GameScene::init_entites()
{
    _manager.add_entity<Organism>(ecs::EntityType::player, 640, 360,
                                  _game_settings._player_speed,
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
        auto sprite_component =
            e->get_component<ecs::components::SpriteComponent>();
        auto pos = sprite_component->texture_rect();
        auto x = pos.x;
        auto y = pos.y;

        // Relating to rad of yaschperitsy generation
        if (x < -1000 || x > 2300 || y < -1000 || y > 1900)
        {
            e->destroy();
        }
    }
    // bullet_hit();
}

}; // namespace yaschperitsy::game::scenes
