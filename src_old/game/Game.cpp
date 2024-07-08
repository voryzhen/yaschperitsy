#include "Game.h"

#include "core/ResourceManager.h"
#include "core/resource_management/Resource.h"
#include "core/resource_management/ResourceManager.h"
#include "game/ui/UILayer.h"
#include "old_game/Background.h"
#include "ui/UIButton.h"
#include <memory>
#include <string_view>

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

SDL_Color free_color = {50, 150, 150, 255};
SDL_Color press_color = {50, 150, 200, 255};
SDL_Color hover_color = {50, 150, 255, 255};

std::shared_ptr<ui::UIButton>
create_button(int x, int y, const std::string_view& name,
              resource_management::FontSPtr font,
              const SDL_RendererUPtr& ren)
{
    auto text1 = resource_management::ResourceManager::get_rm()
                     ->load<resource_management::Texture,
                            resource_management::TextTextureLoader>(
                         std::string(name.data()) + "Free", name, font,
                         ren, free_color);

    auto text2 = resource_management::ResourceManager::get_rm()
                     ->load<resource_management::Texture,
                            resource_management::TextTextureLoader>(
                         std::string(name.data()) + "Pressed", name,
                         font, ren, press_color);

    auto text3 = resource_management::ResourceManager::get_rm()
                     ->load<resource_management::Texture,
                            resource_management::TextTextureLoader>(
                         std::string(name.data()) + "Hover", name, font,
                         ren, hover_color);

    return std::make_shared<ui::UIButton>(x, y, name, text1, text2,
                                          text3);
}

Game::Game()
{
    resource_management::ResourceManager::init();

    auto font = resource_management::ResourceManager::get_rm()
                    ->load<resource_management::Font,
                           resource_management::FontLoader>(
                        "font", "assets/fonts/alegreya.ttf", 28);

    std::vector<std::shared_ptr<ui::UIButton>> btns;
    btns.push_back(create_button(50, 50, "New Game", font, renderer()));
    btns.push_back(
        create_button(50, 100, "Settings", font, renderer()));
    btns.push_back(create_button(50, 150, "Exit", font, renderer()));

    push_layer(std::make_shared<UILayer>(btns));

    load_assets(textures);
    load_fonts(fonts);
}

Game::~Game() {}

}; // namespace yaschperitsy::game
