#include <functional>
#include <game.h>

#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_timer.h"

#include "SDL_render.h"
#include "ecs/components.h"
#include <SDL_image.h>

#include "utility.h"

namespace
{

const auto enemy_deleter = [](const std::reference_wrapper<Entity> e)
{
    auto sprite_component = e.get().get_component<SpriteComponent>();
    if (sprite_component == nullptr)
    {
        e.get().destroy();
        return true;
    }

    auto rect = sprite_component->get_texture_rect();

    if (rect.x < -rect.w)
    {
        e.get().destroy();
        return true;
    }
    else
    {
        return false;
    }
};

const auto enemy_bullet_deleter =
    [](const std::reference_wrapper<Entity> e)
{
    auto sprite_component = e.get().get_component<SpriteComponent>();
    if (sprite_component == nullptr)
    {
        e.get().destroy();
        return true;
    }

    auto rect = sprite_component->get_texture_rect();

    if (rect.x < -rect.w)
    {
        e.get().destroy();
        return true;
    }
    else
    {
        return false;
    }
};

const auto player_bullet_deleter =
    [](const std::reference_wrapper<Entity> e)
{
    auto sprite_component = e.get().get_component<SpriteComponent>();
    if (sprite_component == nullptr)
    {
        e.get().destroy();
        return true;
    }

    auto rect = sprite_component->get_texture_rect();

    if (rect.x > rect.w + 1280)
    {
        e.get().destroy();
        return true;
    }
    else
    {
        return false;
    }
};

} // namespace

Game::Game(int field_width, int field_height, SDL_Renderer* renderer)
    : _renderer(renderer), _rm(_renderer),
      _player(_manager.add_entity("player")),
      _background(std::make_unique<Background>(
          _rm.get_texture("background"), _rm.get_texture("explosion"),
          field_width, field_height)),
      _topbar(std::make_unique<Topbar>(_rm.get_font())),
      _field(field_width, field_height)
{
    _player.add_component<TransformComponent>(100, 100);
    _player.add_component<SpriteComponent>(_rm.get_texture("player"));
    _player.add_component<KeyboardController>();
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
    game_update_bullets();
    game_update_player();

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
    destroy_objects(_enemies, enemy_deleter);
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

        _enemies.emplace_back(enemy);

        // frame rate is 60 and every second
        enemy_spawn_timer = enemy_spawn_freq * _fps;
    }
}

void Game::fire_enemies()
{
    for (auto& e : _enemies)
    {
        const auto fire_component =
            e.get().get_component<FireReloadComponent>();
        if (fire_component->is_reloaded())
        {
            fire_component->shot();

            const auto trasnsform_component =
                e.get().get_component<TransformComponent>()->position();

            auto& bullet = _manager.add_entity("enemy_bullet");
            bullet.add_component<TransformComponent>(
                trasnsform_component.x(), trasnsform_component.y());
            bullet.add_component<SpriteComponent>(
                _rm.get_texture("enemy_bullet"));
            bullet.get_component<TransformComponent>()->set_x_velocity(
                -3); // TODO: bullet speed;

            _enemies_bullets.emplace_back(bullet);
        }
    }
}

void Game::game_update_bullets()
{
    destroy_objects(_enemies_bullets, enemy_bullet_deleter);
    destroy_objects(_player_bullets, player_bullet_deleter);
}

void Game::game_update_player()
{
    const auto fire_component =
        _player.get_component<FireReloadComponent>();

    if (fire_component->is_reloaded())
    {
        if (_event.type == SDL_KEYDOWN &&
            _event.key.keysym.sym == SDLK_f)
        {
            fire_component->shot();

            const auto trasnsform_component =
                _player.get_component<TransformComponent>()->position();

            auto& bullet = _manager.add_entity("player_bullet");
            bullet.add_component<TransformComponent>(
                trasnsform_component.x(), trasnsform_component.y());
            bullet.add_component<SpriteComponent>(
                _rm.get_texture("player_bullet"));
            bullet.get_component<TransformComponent>()->set_x_velocity(
                3); // TODO: bullet speed;

            _player_bullets.emplace_back(bullet);
        }
    }
}

template <typename Deleter>
void Game::destroy_objects(
    std::vector<std::reference_wrapper<Entity>> entities,
    Deleter deleter)
{
    if (entities.empty())
    {
        return;
    }

    const auto remained_entities =
        std::remove_if(entities.begin(), entities.end(), deleter);

    if (remained_entities - entities.begin() < entities.size())
    {
        entities.erase(remained_entities, entities.end());
    }
}

/*

void Game::bullet_hit_enemy()
{
    for (auto& e : _enemies)
    {
        for (auto& b : _bullets)
        {
            auto col = collision(&e, &b);
            if (col)
            {
                e._x = -2 * e._w;
                b._x = _field_width + b._w;
                _score++;
            }
        }
    }
}

void Game::reset_state()
{
    _player->reset_player();
    _bullets.erase(_bullets.begin(), _bullets.end());
    _enemies.erase(_enemies.begin(), _enemies.end());
    _enemy_bullets.erase(_enemy_bullets.begin(),
_enemy_bullets.end()); _max_score = std::max(_max_score,
_score); _score = 0;
}

void Game::bullet_hit_player()
{
    for (const auto& b : _enemy_bullets)
    {
        auto col = collision(&b, _player.get());
        if (col)
        {
            reset_state();
        }
    }
}

void Game::player_logic()
{
    if (_player->_reload > 0)
    {
        _player->_reload--;
    }

    if (_keyboard[SDL_SCANCODE_F] == 1 && _player->_reload == 0)
    {
        fire_bullet();
    }

    // Check out of field
    if (_player->_x + _player->_dx < 0 ||
        _player->_x + _player->_dx > _field_width - _player->_w)
    {
        _player->_dx = 0;
    }
    if (_player->_y + _player->_dy < 0 ||
        _player->_y + _player->_dy > _field_height -
_player->_h)
    {
        _player->_dy = 0;
    }

    _player->_x += _player->_dx;
    _player->_y += _player->_dy;
}

void Game::fire_bullet()
{
    _bullets.emplace_back(_player->_x, _player->_y,
BULLET_SPEED, 0, _rm.get_texture("bullet"));

    _player->_reload = _player->_default_reload;
}

*/