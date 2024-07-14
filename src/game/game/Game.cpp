#include "Game.hpp"
#include "main_menu/MainMenu.hpp"

#include <core/Logger.hpp>

namespace yaschperitsy::game
{

Game::Game()
{
    yaschperitsy::core::logging::Logger::get_logger()->info("Game");

    // Make example layer
    auto main_menu_layer = std::make_shared<ui::main_menu::MainMenuLayer>();
    yaschperitsy::core::LayerStack layer_stack;
    layer_stack.push_layer(main_menu_layer);
    _scene = std::make_unique<yaschperitsy::core::renderer::Scene>(layer_stack);
    set_scene(_scene);
}

Game::~Game()
{
    yaschperitsy::core::logging::Logger::get_logger()->info("~Game");
}

}; // namespace yaschperitsy::game
