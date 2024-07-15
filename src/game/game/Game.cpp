#include "Game.hpp"
#include "game/game/main_menu/SettingsMenu.hpp"
#include "main_menu/MainMenu.hpp"

#include <core/Logger.hpp>
#include <memory>

namespace yaschperitsy::game
{

Game::Game()
{
    yaschperitsy::core::logging::Logger::get_logger()->info("Game");

    // Make Main Menu Layer
    auto main_menu_layer = std::make_shared<ui::main_menu::MainMenuLayer>();
    yaschperitsy::core::LayerStack layer_stack;
    layer_stack.push_layer(main_menu_layer);
    _main_menu_scene =
        std::make_unique<yaschperitsy::core::renderer::Scene>(layer_stack);
    set_scene(_main_menu_scene);

    // Make Settings Menu Layer
    auto settings_layer = std::make_shared<ui::main_menu::SettingsMenuLayer>();
    yaschperitsy::core::LayerStack settings_layer_stack;
    settings_layer_stack.push_layer(settings_layer);
    _settings_menu_scene =
        std::make_unique<yaschperitsy::core::renderer::Scene>(
            settings_layer_stack);
    // set_scene(_settings_menu_scene);
}

Game::~Game()
{
    yaschperitsy::core::logging::Logger::get_logger()->info("~Game");
}

}; // namespace yaschperitsy::game
