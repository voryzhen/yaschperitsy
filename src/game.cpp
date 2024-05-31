#include <game.h>

#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_rect.h"
#include "SDL_timer.h"

#include "SDL_render.h"
#include "ecs/components.h"
#include <SDL_image.h>
#include <string>

#include "utility.h"

Game::Game(int field_width, int field_height, SDL_Renderer* renderer)
    : _renderer(renderer), _rm(_renderer),
      _player(_manager.add_entity("player")),
      _background(std::make_unique<Background>(
          _rm.get_texture("background"), _rm.get_texture("explosion"),
          field_width, field_height)),
      _topbar(std::make_unique<Topbar>(_rm.get_font(), _stat)),
      _field(field_width, field_height)
{
    _player.add_component<TransformComponent>(100, 100);
    _player.add_component<SpriteComponent>(_rm.get_texture("player"));
    _player.add_component<KeyboardController>();
    _player.add_component<MouseController>();
    _player.add_component<FireReloadComponent>(8);
}

int Game::run_game()
{
    Uint32 frame_start{0};
    Uint32 frame_time{0};

    while (!_quit)
    {
        frame_start = SDL_GetTicks();

        handle_events();
        update();
        render();

        frame_time = SDL_GetTicks() - frame_start;

        if (_frame_delay > frame_time)
        {
            SDL_Delay(_frame_delay - frame_time);
        }
    }

    return 0;
}

void Game::handle_events()
{
    SDL_PollEvent(&_event);
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

void Game::render()
{
    SDL_RenderClear(_renderer);

    _background->render(_renderer);
    _manager.render(_renderer);

    _topbar->render(_renderer);

    SDL_RenderPresent(_renderer);
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
        enemy.add_component<TransformComponent>(_field.w, 0);
        enemy.add_component<SpriteComponent>(_rm.get_texture("enemy"));

        const auto enemy_rect =
            enemy.get_component<SpriteComponent>()->get_texture_rect();
        enemy.get_component<TransformComponent>()->set_position(
            _field.w, get_random_int(_field.h - enemy_rect.h));

        enemy.get_component<TransformComponent>()->set_x_velocity(-1);
        enemy.add_component<FireReloadComponent>(60);

        // frame rate is 60 and every second
        enemy_spawn_timer = enemy_spawn_freq * _fps;
    }
}

void Game::fire_enemies()
{
    for (auto& e : _manager.get_entities_by_name("enemy"))
    {
        const auto fire_component =
            e->get_component<FireReloadComponent>();
        if (fire_component->is_reloaded())
        {
            fire_component->shot();

            const auto trasnsform_component =
                e->get_component<TransformComponent>()->position();

            auto& bullet = _manager.add_entity("enemy_bullet");
            bullet.add_component<TransformComponent>(
                trasnsform_component.x(), trasnsform_component.y());
            bullet.add_component<SpriteComponent>(
                _rm.get_texture("enemy_bullet"));
            bullet.get_component<TransformComponent>()->set_x_velocity(
                -3); // TODO: bullet speed;
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
        auto sprite_component = e->get_component<SpriteComponent>();
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
        _player.get_component<FireReloadComponent>();

    if (fire_component->is_reloaded())
    {
        if ((_event.type == SDL_KEYDOWN &&
             _event.key.keysym.sym == SDLK_f) ||
            (_event.type == SDL_MOUSEBUTTONDOWN &&
             _event.button.button == SDL_BUTTON_LEFT))
        {
            fire_component->shot();

            const auto trasnsform_component =
                _player.get_component<TransformComponent>();
            const auto pos = trasnsform_component->position();

            auto& bullet = _manager.add_entity("player_bullet");
            bullet.add_component<TransformComponent>(
                pos.x() + 80, pos.y(), trasnsform_component->angle());
            bullet.add_component<SpriteComponent>(
                _rm.get_texture("player_bullet"));

            bullet.get_component<TransformComponent>()->set_velocity(
                trasnsform_component->direction() *
                3); // TODO: bullet speed;
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
    const auto p_rect =
        _player.get_component<SpriteComponent>()->get_texture_rect();

    for (const auto& b : enemies_bullets)
    {
        const auto rect =
            b->get_component<SpriteComponent>()->get_texture_rect();
        if (intersect(p_rect, rect))
        {
            reset_state();
        }
    }

    for (const auto& pb : player_bullets)
    {
        for (const auto& e : enemies)
        {
            const auto b_rect = pb->get_component<SpriteComponent>()
                                    ->get_texture_rect();
            const auto e_rect =
                e->get_component<SpriteComponent>()->get_texture_rect();
            if (intersect(b_rect, e_rect))
            {
                e->destroy();
                _stat._score++;
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
            e->get_component<TransformComponent>()->set_position(100,
                                                                 100);
        }
        else
        {
            e->destroy();
        }
    }
    _stat._max_score = std::max(_stat._max_score, _stat._score);
    _stat._score = 0;
}
