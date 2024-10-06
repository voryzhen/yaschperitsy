#include "Game.hpp"

#include "Events/UIEvent.hpp"
#include "Logger/Logger.hpp"
#include "Scenes/GameEndScene/GameEndScene.hpp"
#include "Scenes/GameScene/GameScene.hpp"
#include "Scenes/MainMenuScene/MainMenuScene.hpp"
#include <memory>
#include <string_view>

Game::Game()
{
    get_rm().load_font("Assets/Fonts/alegreya.ttf", 40);

    scene_man_ = std::make_shared<SceneManager>();
    init_game_scene();
    init_main_menu_scene();
    init_game_end_scene();

    set_scene(scene_man_->get_scene("main_menu"));
}

void Game::init_game_scene()
{
    auto [h, w] = get_window_size();
    scene_man_->add_scene("game_scene",
                          std::make_shared<GameScene>(
                              get_rm(), [this](const EventSPtr& event)
                              { on_event(event); }, w, h));
}

void Game::init_main_menu_scene()
{
    auto [h, w] = get_window_size();
    scene_man_->add_scene("main_menu",
                          std::make_shared<MainMenuScene>(
                              get_rm(), [this](const EventSPtr& event)
                              { on_event(event); }, w, h));
}

void Game::init_game_end_scene()
{
    auto [h, w] = get_window_size();
    scene_man_->add_scene("game_end",
                          std::make_shared<GameEndScene>(
                              get_rm(), [this](const EventSPtr& event)
                              { on_event(event); }, w, h));
}

void Game::on_event(const EventSPtr& event)
{
    EventDispatcher event_dispatcher(event);
    event_dispatcher.dispatch<UIEvent>(
        [this](const UIEventSPtr& event)
        {
            switch (event->code())
            {
                case UIEventCode::NewGame:
                    set_scene(scene_man_->get_scene("game_scene"));
                    break;
                case UIEventCode::Exit:
                    shutdown();
                    break;
                case UIEventCode::GameWin:
                    set_scene(scene_man_->get_scene("game_end"));
                    break;
                default:
                    break;
            }
            return true;
        });
}
