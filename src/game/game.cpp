#include <cmath>
#include <game/game.h>

#include "ecs/components/fire_component.h"
#include "ecs/components/sprite_component.h"
#include "ecs/components/transform_component.h"
#include "ecs/entity.h"
#include "numbers"

#include "utility/utility.h"
#include "utility/vector2D.h"

// Main Game functions
namespace yaschperitsy::game
{

Game::Game(const resource::ResourceManagerUPtr& rm)
    : _rm(rm),
      _player(_manager.add_entity(ecs::EntityType::player, 640, 360,
                                  _game_settings._player_speed,
                                  _rm->get_texture("player"))),
      // Refactor as Component ?
      _background(std::make_unique<Background>(
          _rm->get_texture("background"), _game_field)),
      _topbar(std::make_unique<Topbar>(_rm->get_font("lazy"), _stat))

{
    _game_field = GameField(1280, 720); // TODO:
    _background->set_game_field(_game_field);
}

void Game::handle_events(const SDL_Event& event)
{
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
    update_enemies();
    update_player();
    destroy_objects();

    _manager.refresh();
    _manager.update(_event); // refactor
}

void Game::render(const SDL_RendererUPtr& renderer)
{
    _background->render(renderer);
    _manager.render(renderer);
    _topbar->render(renderer);
}

}; // namespace yaschperitsy::game

namespace
{

Vector2D<float> get_updated_direction(Vector2D<float> aim,
                                      Vector2D<float> pos, int& angle)
{
    int dy = static_cast<int>(aim.y() - pos.y());
    int dx = static_cast<int>(aim.x() - pos.x());

    angle = static_cast<int>(180.0 +
                             atan2(dy, dx) * (180 / std::numbers::pi));
    angle = angle % 360;

    auto d2 = dy * dy + dx * dx;
    auto d = sqrt(d2);

    auto xx = static_cast<float>(dx / d);
    auto yy = static_cast<float>(dy / d);

    return {xx, yy};
}

Vector2D<float> get_enemies_velocity(Vector2D<int> pos)
{
    Vector2D<int> center = {640, 360};

    int dy = center.y() - pos.y();
    int dx = center.x() - pos.x();

    auto d2 = dy * dy + dx * dx;
    auto d = sqrt(d2);

    auto xx = static_cast<float>(dx / d);
    auto yy = static_cast<float>(dy / d);

    return {xx, yy};
}

// TODO: refactor very very
constexpr int rad2 = (640 * 640 + 360 * 360);
const int rad = static_cast<int>(sqrt(rad2));

Vector2D<int>
get_enemies_position(int& random_angle) // very bad but I am lazy
{
    random_angle = get_random<int>(360);
    int x = static_cast<int>(rad * cos(random_angle) + 640);
    int y = static_cast<int>(rad * sin(random_angle) + 360);

    return {x, y};
};

}; // namespace

// Player functions
namespace yaschperitsy::game
{

void Game::update_player()
{
    const auto fire_component =
        _player->get_component<ecs::components::FireComponent>();

    if (fire_component->reloaded())
    {
        // refactor with FireComponent Update
        if ((_event.type == SDL_KEYDOWN &&
             _event.key.keysym.sym == SDLK_f) ||
            (_event.type == SDL_MOUSEBUTTONDOWN &&
             _event.button.button == SDL_BUTTON_LEFT))
        {
            fire_component->shot();

            const auto p_tran_comp = _player->get_component<
                ecs::components::TransformComponent>();
            const auto pos = p_tran_comp->position();

            auto bullet = _manager.add_entity(
                ecs::EntityType::pbullet, pos.x() + 80, pos.y(),
                _game_settings._bullet_speed,
                _rm->get_texture("player_bullet"));

            auto bullet_trans_comp = bullet->get_component<
                ecs::components::TransformComponent>();

            bullet_trans_comp->set_angle(p_tran_comp->angle());

            bullet_trans_comp->set_velocity(
                p_tran_comp->direction() *
                _game_settings._bullet_speed);
        }
    }
}

}; // namespace yaschperitsy::game

// Enemy function
namespace yaschperitsy::game
{

void Game::update_enemies()
{
    spawn_enemies();
    fire_enemies();
    update_enemies_direction();
}

void Game::update_enemies_direction()
{
    for (auto& e : _manager.get_entities(ecs::EntityType::enemy))
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
        transform_comp->set_angle(static_cast<float>(angle));
    }
}

void Game::spawn_enemies()
{
    if (--enemy_spawn_timer <= 0 && _stat->_enemies_num > 0)
    {
        _stat->_enemies_num--;

        // TODO: Create a fabric for different entities
        // Enemy texture randomizer
        const auto random = get_random<int>(2);
        // 2 different enemies
        const auto name = (random == 1) ? "enemy" : "enemy2";

        auto enemy = _manager.add_entity(
            ecs::EntityType::enemy, static_cast<float>(_game_field.w),
            0., _game_settings._enemy_speed, _rm->get_texture(name));

        int angle{0};
        Vector2D<int> enemies_pos = get_enemies_position(angle);
        auto enemy_transform_comp =
            enemy->get_component<ecs::components::TransformComponent>();

        enemy_transform_comp->set_position(
            static_cast<float>(enemies_pos.x()),
            static_cast<float>(enemies_pos.y()));

        enemy_transform_comp->set_angle(
            static_cast<float>(angle * (180 / std::numbers::pi)));

        // get velocity aimed to the center
        Vector2D<float> vel = get_enemies_velocity(enemies_pos);
        enemy_transform_comp->set_velocity(vel);
        enemy_transform_comp->set_direction(vel);

        // frame rate is 60 fps and every second with random factor
        // TODO: do I need _enemy_spawn_freq ?
        enemy_spawn_timer =
            _game_settings._enemy_spawn_freq *
            static_cast<int>(_fps * get_random<double>(2.0));
    }
}

void Game::fire_enemies()
{
    for (auto& e : _manager.get_entities(ecs::EntityType::enemy))
    {
        const auto fire_component =
            e->get_component<ecs::components::FireComponent>();
        if (fire_component->reloaded())
        {
            fire_component->shot();

            const auto enemy_trans_comp =
                e->get_component<ecs::components::TransformComponent>();
            const auto enemy_pos = enemy_trans_comp->position();

            auto bullet = _manager.add_entity(
                ecs::EntityType::ebullet, enemy_pos.x(), enemy_pos.y(),
                _game_settings._bullet_speed,
                _rm->get_texture("enemy_bullet"));

            auto transform_comp = bullet->get_component<
                ecs::components::TransformComponent>();
            transform_comp->set_velocity(
                enemy_trans_comp->direction() *
                (_game_settings._bullet_speed));
            // There is no angle because texture has round symmetry
        }
    }
}

} // namespace yaschperitsy::game

// Other functions
namespace yaschperitsy::game
{

void Game::destroy_objects()
{
    for (auto& e : _manager.get_entities())
    {
        if (e->type() == ecs::EntityType::player)
        {
            continue;
        }
        auto sprite_component =
            e->get_component<ecs::components::SpriteComponent>();
        auto pos = sprite_component->texture_rect();
        auto x = pos.x;
        auto y = pos.y;

        // Relating to rad of enemies generation
        if (x < -1000 || x > 2300 || y < -1000 || y > 1900)
        {
            e->destroy();
        }
    }
    bullet_hit();
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

bool intersect(const ecs::EntitySPtr& ent1, const ecs::EntitySPtr& ent2)
{
    const auto rect1 =
        ent1->get_component<ecs::components::SpriteComponent>()
            ->texture_rect();
    const auto rect2 =
        ent2->get_component<ecs::components::SpriteComponent>()
            ->texture_rect();
    return intersect(rect1, rect2);
}

} // namespace

void Game::bullet_hit()
{
    const auto enemies_bullets =
        _manager.get_entities(ecs::EntityType::ebullet);

    // enemies strike
    for (const auto& ebullet : enemies_bullets)
    {
        if (intersect(_player, ebullet))
        {
            // reset_state();
        }
    }

    // enemies bite
    const auto enemies = _manager.get_entities(ecs::EntityType::enemy);

    for (const auto& enemy : enemies)
    {
        if (intersect(_player, enemy))
        {
            // reset_state();
        }
    }

    const auto player_bullets =
        _manager.get_entities(ecs::EntityType::pbullet);

    for (const auto& pbullet : player_bullets)
    {
        for (const auto& enemy : enemies)
        {
            if (intersect(pbullet, enemy))
            {
                enemy->destroy();
                _stat->_score++;
            }
        }
    }
}

void Game::reset_state()
{
    for (auto& e : _manager.get_entities())
    {
        if (e->type() == ecs::EntityType::player)
        {
            e->get_component<ecs::components::TransformComponent>()
                ->set_position(640, 360);
        }
        else
        {
            e->destroy();
        }
    }

    _stat->_max_score = std::max(_stat->_max_score, _stat->_score);
    _stat->_score = 0;
    _stat->_enemies_num = _stat->_enemies_total_num;
}

} // namespace yaschperitsy::game
