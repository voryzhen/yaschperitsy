#include "Game.hpp"

#include "core/scene/LayerStack.hpp"
#include "game/game/Assets.hpp"
#include "game/game/layers/GameEndLayer.hpp"
#include "game/game/layers/MainMenuLayer.hpp"
#include "game/game/layers/PauseMenuLayer.hpp"
#include "game/game/layers/SettingsMenuLayer.hpp"
#include "game/game/scenes/GameScene.hpp"

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

void Game::create_game_scene()
{
    _game_scene = std::make_shared<scenes::GameScene>(
        "game", [this](const yaschperitsy::core::events::EventSPtr& event)
        { on_game_event(event); });
}

void Game::create_game_end_scene()
{
    auto layer = std::make_shared<layers::GameEndLayer>(
        [this](const yaschperitsy::core::events::EventSPtr& event)
        { on_button_event(event); });
    yaschperitsy::core::LayerStack stack;
    stack.push_layer(layer);
    _game_end_scene =
        std::make_shared<yaschperitsy::core::scenes::Scene>("game_end", stack);
}

void Game::create_pause_menu_scene()
{
    auto pause_layer = std::make_shared<layers::PauseMenuLayer>(
        [this](const yaschperitsy::core::events::EventSPtr& event)
        { on_button_event(event); });
    yaschperitsy::core::LayerStack pause_layer_stack;
    pause_layer_stack.push_layer(pause_layer);
    _pause_menu_scene = std::make_shared<yaschperitsy::core::scenes::Scene>(
        "pause", pause_layer_stack);
}

void Game::create_settings_scene()
{
    auto settings_layer = std::make_shared<layers::SettingsMenuLayer>(
        [this](const yaschperitsy::core::events::EventSPtr& event)
        { on_button_event(event); });
    yaschperitsy::core::LayerStack settings_layer_stack;
    settings_layer_stack.push_layer(settings_layer);
    _settings_menu_scene = std::make_shared<yaschperitsy::core::scenes::Scene>(
        "settings", settings_layer_stack);
}

void Game::create_main_menu_scene()
{
    auto main_menu_layer = std::make_shared<layers::MainMenuLayer>(
        [this](const yaschperitsy::core::events::EventSPtr& event)
        { on_button_event(event); });
    yaschperitsy::core::LayerStack layer_stack;
    layer_stack.push_layer(main_menu_layer);
    _main_menu_scene = std::make_shared<yaschperitsy::core::scenes::Scene>(
        "main menu", layer_stack);
}

Game::~Game()
{
    yaschperitsy::core::logging::Logger::get_logger()->info("~Game");
    assets::Assets::clean();
}

void Game::on_game_event(const yaschperitsy::core::events::EventSPtr& /*event*/)
{
    // core::logging::Logger::get_logger()->info("win");
    set_scene(_game_end_scene);
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
    {
        set_scene(_game_scene);
        break;
    }
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
    case 5:
    {
        set_scene(_game_scene);
        break;
    }
    }

    return true;
}

}; // namespace yaschperitsy::game
