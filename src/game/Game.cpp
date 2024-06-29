#include "Game.h"

#include "UILayer.h"

namespace yaschperitsy::game
{

const resource::ResourceMap textures = {
    // clang-format off
    {"player"        , "assets/player/player.png"},
    {"player_bullet" , "assets/player/player_bullet.png"},

    {"yaschperitsa_1"        , "assets/yaschperitsy/yaschperitsa_1.png"},
    {"yaschperitsa_2"        , "assets/yaschperitsy/yaschperitsa_2.png"},
    {"yaschperitsy_fireball" , "assets/yaschperitsy/yaschperitsy_fireball.png"},

    {"background" , "assets/background.png"}
    // clang-format on
};

const resource::ResourceMap fonts = {
    {"alegreya", "assets/fonts/alegreya.ttf"}};

Game::Game()
{
    push_layer(std::make_shared<UILayer>());
    load_assets(textures);
    load_fonts(fonts);
}

Game::~Game() {}

}; // namespace yaschperitsy::game
