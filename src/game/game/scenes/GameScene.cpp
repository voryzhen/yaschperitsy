#include "GameScene.hpp"

namespace yaschperitsy::game::scenes
{

void GameScene::init_entites()
{
    _manager.add_entity<Organism>(ecs::EntityType::player, 640, 360,
                                  _game_settings._player_speed,
                                  assets::Assets::player());
}

}; // namespace yaschperitsy::game::scenes
