#include "Game.hpp"
#include "game/game/Assets.hpp"
#include "game/game/main_menu/SettingsMenu.hpp"
#include "main_menu/MainMenu.hpp"

#include <core/Logger.hpp>
#include <memory>

namespace yaschperitsy::game
{

using EventCallbackFn =
    std::function<void(const yaschperitsy::core::events::EventSPtr&)>;

Game::Game()
{
    yaschperitsy::core::logging::Logger::get_logger()->info("Game");

    assets::Assets::init();

    create_scenes();
    set_scene(_main_menu_scene);
}

void Game::create_game_scene() {}

void Game::create_settings_scene()
{
    auto settings_layer = std::make_shared<ui::main_menu::SettingsMenuLayer>(
        [this](const yaschperitsy::core::events::EventSPtr& event)
        { on_button_event(event); });
    yaschperitsy::core::LayerStack settings_layer_stack;
    settings_layer_stack.push_layer(settings_layer);
    _settings_menu_scene =
        std::make_shared<yaschperitsy::core::renderer::Scene>(
            settings_layer_stack);
}

void Game::create_main_menu_scene()
{
    auto main_menu_layer = std::make_shared<ui::main_menu::MainMenuLayer>(
        [this](const yaschperitsy::core::events::EventSPtr& event)
        { on_button_event(event); });
    yaschperitsy::core::LayerStack layer_stack;
    layer_stack.push_layer(main_menu_layer);
    _main_menu_scene =
        std::make_shared<yaschperitsy::core::renderer::Scene>(layer_stack);
}

Game::~Game()
{
    yaschperitsy::core::logging::Logger::get_logger()->info("~Game");
}

void Game::on_button_event(const yaschperitsy::core::events::EventSPtr& event)
{
    yaschperitsy::core::events::EventDispatcher dispatcher(event);

    dispatcher.dispatch<events::UIEvent>(
        [this](const events::UIEventSPtr& event)
        { return on_button_click(event); });
}

bool Game::on_button_click(const events::UIEventSPtr& event)
{
    switch (event->code())
    {
    case 1:
        core::logging::Logger::get_logger()->info("btn New game is pressed");
        break;
    case 2:
    {
        set_scene(_settings_menu_scene);
        break;
    }
    case 3:
    {
        shutdown();
        break;
    }
    case 4:
    {
        set_scene(_main_menu_scene);
        break;
    }
    }

    return true;
}

}; // namespace yaschperitsy::game
