#include <cmath>
#include <game/game.h>

#include "ecs/components/transform_component.h"
#include "numbers"

#include "utility/utility.h"
#include "utility/vector2D.h"

#include "ecs/components/components.h"

namespace
{

Vector2D<float> get_updated_direction(Vector2D<float> aim,
                                      Vector2D<float> pos, int& angle)
{
    int dy = aim.y() - pos.y();
    int dx = aim.x() - pos.x();

    angle = 180.0 + atan2(dy, dx) * (180 / std::numbers::pi);
    if (angle > 360.0)
    {
        angle -= 360.0;
    }

    auto d2 = dy * dy + dx * dx;
    auto d = sqrt(d2);

    auto xx = dx / d;
    auto yy = dy / d;

    return Vector2D<float>(xx, yy);
}

Vector2D<float> get_enemies_velocity(Vector2D<int> pos)
{
    Vector2D<int> center = {640, 360};

    int dy = center.y() - pos.y();
    int dx = center.x() - pos.x();

    // float _angle = -90.0f + atan2(dy, dx) * (180 / std::numbers::pi);

    // _transform_component->set_angle(_angle +
    // static_cast<float>(90.0));

    auto d2 = dy * dy + dx * dx;
    auto d = sqrt(d2);

    auto xx = dx / d;
    auto yy = dy / d;

    return Vector2D<float>(xx, yy);
}

// TODO: refactor very very
constexpr int rad2 = (640 * 640 + 360 * 360);
const int rad = static_cast<int>(sqrt(rad2));

Vector2D<int>
get_enemies_position(int& random_angle) // very bad but I am lazy
{
    random_angle = get_random<int>(360);
    int x = rad * cos(random_angle) + 640;
    int y = rad * sin(random_angle) + 360;

    return {x, y};
};

}; // namespace

namespace yaschperitsy::game
{

void Game::compose_player()
{
    _player->add_component<ecs::components::TransformComponent>(
        100, 100, _game_settings._player_speed);
    _player->add_component<ecs::components::SpriteComponent>(
        _rm->get_texture("player"));
    _player->add_component<ecs::components::KeyboardController>();
    _player->add_component<ecs::components::MouseController>();
    _player->add_component<ecs::components::FireComponent>(8);
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
    update_enemies_direction();
}

void Game::update_enemies_direction()
{
    for (auto& e : _manager.get_entities_by_name("enemy"))
    {
        auto transform_comp =
            e->get_component<ecs::components::TransformComponent>();
        auto pos = transform_comp->position();

        int angle{0};
        Vector2D<float> dir = get_updated_direction(
            _player
                ->get_component<ecs::components::TransformComponent>()
                ->position(),
            pos, angle);

        transform_comp->set_velocity(dir);
        transform_comp->set_direction(dir);
        transform_comp->set_angle(angle);
    }
}

void Game::spawn_enemies()
{
    if (--enemy_spawn_timer <= 0)
    {
        // TODO: Create a fabric for different entities
        auto enemy = _manager.add_entity("enemy");
        enemy->add_component<ecs::components::TransformComponent>(
            _game_field.w, 0, _game_settings._enemy_speed);

        // Enemy texture randomizer
        const auto random = get_random<int>(2);
        const auto name = (random == 1) ? "enemy" : "enemy2";
        enemy->add_component<ecs::components::SpriteComponent>(
            _rm->get_texture(name), 2, 100);

        // const auto enemy_rect =
        // enemy->get_component<ecs::components::SpriteComponent>()
        // ->texture_rect();

        int angle{0};
        Vector2D<int> enemies_pos = get_enemies_position(angle);
        auto enemy_transform_comp =
            enemy->get_component<ecs::components::TransformComponent>();

        enemy_transform_comp->set_position(enemies_pos.x(),
                                           enemies_pos.y());
        enemy_transform_comp->set_angle(angle *
                                        (180 / std::numbers::pi));

        // get velocity aimed to the center
        Vector2D<float> vel = get_enemies_velocity(enemies_pos);
        enemy_transform_comp->set_velocity(vel);
        enemy_transform_comp->set_direction(vel);
        enemy->add_component<ecs::components::FireComponent>(60);

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
            e->get_component<ecs::components::FireComponent>();
        if (fire_component->reloaded())
        {
            fire_component->shot();

            const auto enemy_trasnsform_component =
                e->get_component<ecs::components::TransformComponent>();
            const auto enemy_pos =
                enemy_trasnsform_component->position();

            auto bullet = _manager.add_entity("enemy_bullet");

            auto transform_comp = bullet->add_component<
                ecs::components::TransformComponent>(enemy_pos.x(),
                                                     enemy_pos.y());

            bullet->add_component<ecs::components::SpriteComponent>(
                _rm->get_texture("enemy_bullet"));

            transform_comp->set_velocity(
                enemy_trasnsform_component->direction() *
                (_game_settings._bullet_speed));
        }
    }
}

void Game::destroy_objects()
{
    for (auto& e : _manager.get_entities())
    {
        if (e->name() == "player")
        {
            continue;
        }
        auto sprite_component =
            e->get_component<ecs::components::SpriteComponent>();
        auto pos = sprite_component->texture_rect();
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
        _player->get_component<ecs::components::FireComponent>();

    if (fire_component->reloaded())
    {
        if ((_event.type == SDL_KEYDOWN &&
             _event.key.keysym.sym == SDLK_f) ||
            (_event.type == SDL_MOUSEBUTTONDOWN &&
             _event.button.button == SDL_BUTTON_LEFT))
        {
            fire_component->shot();

            const auto trasnsform_component = _player->get_component<
                ecs::components::TransformComponent>();
            const auto pos = trasnsform_component->position();

            auto bullet = _manager.add_entity("player_bullet");

            bullet->add_component<ecs::components::TransformComponent>(
                pos.x() + 80, pos.y(), _game_settings._bullet_speed,
                trasnsform_component->angle());
            bullet->add_component<ecs::components::SpriteComponent>(
                _rm->get_texture("player_bullet"));

            bullet->get_component<ecs::components::TransformComponent>()
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

    // player
    const auto p_rect =
        _player->get_component<ecs::components::SpriteComponent>()
            ->texture_rect();

    // enemies strike
    for (const auto& b : enemies_bullets)
    {
        const auto rect =
            b->get_component<ecs::components::SpriteComponent>()
                ->texture_rect();
        if (intersect(p_rect, rect))
        {
            // reset_state();
        }
    }

    // enemies bite
    for (const auto& b : enemies)
    {
        const auto rect =
            b->get_component<ecs::components::SpriteComponent>()
                ->texture_rect();
        if (intersect(p_rect, rect))
        {
            // reset_state();
        }
    }

    const auto player_bullets =
        _manager.get_entities_by_name("player_bullet");

    for (const auto& pb : player_bullets)
    {
        for (const auto& e : enemies)
        {
            const auto b_rect =
                pb->get_component<ecs::components::SpriteComponent>()
                    ->texture_rect();
            const auto e_rect =
                e->get_component<ecs::components::SpriteComponent>()
                    ->texture_rect();
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
        if (e->name() == "player")
        {
            e->get_component<ecs::components::TransformComponent>()
                ->set_position(100, 100);
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
