#include <game/game.h>

#include "SDL_render.h"
#include "SDL_video.h"
#include "game/utility.h"
#include "game/vector2D.h"

namespace yaschperitsy::game
{

void Game::compose_player()
{
    _player.add_component<ecs::TransformComponent>(
        100, 100, _game_settings._player_speed);
    _player.add_component<ecs::SpriteComponent>(
        _rm->get_texture("player"));
    _player.add_component<ecs::KeyboardController>();
    _player.add_component<ecs::MouseController>();
    _player.add_component<ecs::FireReloadComponent>(8);
}

Game::Game(const resource::ResourceManagerUPtr& rm)
    : _rm(rm), _player(_manager.add_entity("player")),
      _background(std::make_unique<Background>(
          _rm->get_texture("background"), _game_field)),
      _topbar(std::make_unique<Topbar>(_rm->get_font("lazy"), _stat))

{

    _game_field = GameField(1280, 720); // TODO:
    _background->set_game_field(_game_field);

    compose_player();
}

void Game::handle_events(const SDL_Event& event)
{
    // SDL_PollEvent(&_event);
    _event = event;
    switch (_event.type)
    {
    case SDL_QUIT:
        _quit = true;
        break;

    default:
        break;
    }
}

void Game::update()
{
    game_update_enemies();
    game_update_player();
    destroy_objects();

    _manager.refresh();
    _manager.update(_event);
}

void Game::render(const SDL_RendererUPtr& renderer)
{
    // SDL_RenderClear(_renderer.get());

    _background->render(renderer);
    _manager.render(renderer);

    _topbar->render(renderer);

    // SDL_RenderPresent(_renderer.get());
}

void Game::game_update_enemies()
{
    spawn_enemies();
    fire_enemies();
}

void Game::spawn_enemies()
{
    if (--enemy_spawn_timer <= 0)
    {
        auto& enemy = _manager.add_entity("enemy");
        enemy.add_component<ecs::TransformComponent>(
            _game_field.w, 0, _game_settings._enemy_speed);

        // Enemy texture randomizer
        const auto random = get_random<int>(2);
        const auto name = (random == 1) ? "enemy" : "enemy2";
        enemy.add_component<ecs::SpriteComponent>(
            _rm->get_texture(name), 2, 100);

        const auto enemy_rect =
            enemy.get_component<ecs::SpriteComponent>()
                ->get_texture_rect();
        enemy.get_component<ecs::TransformComponent>()->set_position(
            _game_field.w,
            get_random<int>(_game_field.h - enemy_rect.h));

        enemy.get_component<ecs::TransformComponent>()->set_x_velocity(
            -1);
        enemy.add_component<ecs::FireReloadComponent>(60);

        // frame rate is 60 fps and every second with random factor
        // TODO: do I need _enemy_spawn_freq ?
        enemy_spawn_timer =
            _game_settings._enemy_spawn_freq *
            static_cast<int>(_fps * get_random<double>(2.0));
    }
}

void Game::fire_enemies()
{
    for (auto& e : _manager.get_entities_by_name("enemy"))
    {
        const auto fire_component =
            e->get_component<ecs::FireReloadComponent>();
        if (fire_component->is_reloaded())
        {
            fire_component->shot();

            const auto trasnsform_component =
                e->get_component<ecs::TransformComponent>()->position();

            auto& bullet = _manager.add_entity("enemy_bullet");
            bullet.add_component<ecs::TransformComponent>(
                trasnsform_component.x(), trasnsform_component.y());
            bullet.add_component<ecs::SpriteComponent>(
                _rm->get_texture("enemy_bullet"));
            bullet.get_component<ecs::TransformComponent>()
                ->set_velocity(Vector2D{-1, 0} *
                               (_game_settings._bullet_speed));
        }
    }
}

void Game::destroy_objects()
{
    for (auto& e : _manager.get_entities())
    {
        if (e->_name == "player")
        {
            continue;
        }
        auto sprite_component =
            e->get_component<ecs::SpriteComponent>();
        auto pos = sprite_component->get_texture_rect();
        auto x = pos.x;
        auto y = pos.y;

        if (x < -100 || x > 1580 || y < -100 || y > 900)
        {
            e->destroy();
        }
    }
    bullet_hit();
}

void Game::game_update_player()
{
    const auto fire_component =
        _player.get_component<ecs::FireReloadComponent>();

    if (fire_component->is_reloaded())
    {
        if ((_event.type == SDL_KEYDOWN &&
             _event.key.keysym.sym == SDLK_f) ||
            (_event.type == SDL_MOUSEBUTTONDOWN &&
             _event.button.button == SDL_BUTTON_LEFT))
        {
            fire_component->shot();

            const auto trasnsform_component =
                _player.get_component<ecs::TransformComponent>();
            const auto pos = trasnsform_component->position();

            auto& bullet = _manager.add_entity("player_bullet");
            bullet.add_component<ecs::TransformComponent>(
                pos.x() + 80, pos.y(), trasnsform_component->angle());
            bullet.add_component<ecs::SpriteComponent>(
                _rm->get_texture("player_bullet"));

            bullet.get_component<ecs::TransformComponent>()
                ->set_velocity(trasnsform_component->direction() *
                               _game_settings._bullet_speed);
        }
    }
}

namespace
{

bool intersect(SDL_Rect r1, SDL_Rect r2)
{
    if (r1.x > r2.x + r2.w)
    {
        return false;
    }
    if (r1.x + r1.w < r2.x)
    {
        return false;
    }
    if (r1.y > r2.y + r2.h)
    {
        return false;
    }
    if (r1.y + r1.w < r2.y)
    {
        return false;
    }

    return true;
}

} // namespace

void Game::bullet_hit()
{
    const auto enemies = _manager.get_entities_by_name("enemy");
    // const auto enemies = _manager.get_entities_by_name("enemy");
    const auto enemies_bullets =
        _manager.get_entities_by_name("enemy_bullet");
    const auto player_bullets =
        _manager.get_entities_by_name("player_bullet");

    // player
    const auto p_rect = _player.get_component<ecs::SpriteComponent>()
                            ->get_texture_rect();

    for (const auto& b : enemies_bullets)
    {
        const auto rect = b->get_component<ecs::SpriteComponent>()
                              ->get_texture_rect();
        if (intersect(p_rect, rect))
        {
            reset_state();
        }
    }

    for (const auto& pb : player_bullets)
    {
        for (const auto& e : enemies)
        {
            const auto b_rect =
                pb->get_component<ecs::SpriteComponent>()
                    ->get_texture_rect();
            const auto e_rect = e->get_component<ecs::SpriteComponent>()
                                    ->get_texture_rect();
            if (intersect(b_rect, e_rect))
            {
                e->destroy();
                _stat->_score++;
            }
        }
    }
}

void Game::reset_state()
{
    for (auto& e : _manager.get_entities())
    {
        if (e->_name == "player")
        {
            e->get_component<ecs::TransformComponent>()->set_position(
                100, 100);
        }
        else
        {
            e->destroy();
        }
    }
    _stat->_max_score = std::max(_stat->_max_score, _stat->_score);
    _stat->_score = 0;
}

} // namespace yaschperitsy::game
