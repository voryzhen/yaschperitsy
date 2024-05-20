#include "SDL_render.h"
#include "entity.h"
#include <game.h>

#include <random>

#include <SDL_image.h>
#include <string>

namespace
{

std::random_device rd;
std::mt19937 mt(rd());

int get_random_int(int max)
{
    std::uniform_real_distribution<double> dist(0, max);
    return (int)dist(mt);
}

bool collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2,
               int h2)
{
    return (std::max(x1, x2) < std::min(x1 + w1, x2 + w2)) &&
           (std::max(y1, y2) < std::min(y1 + h1, y2 + h2));
}

bool collision(const Entity* e1, const Entity* e2)
{
    return collision(e1->_x, e1->_y, e1->_w, e1->_h, e2->_x, e2->_y,
                     e2->_w, e2->_h);
}

}; // namespace

void Game::prepare_scene()
{
    SDL_SetRenderDrawColor(_renderer, 96, 128, 255, 255);
    SDL_RenderClear(_renderer);
}

void Game::present_scene() { SDL_RenderPresent(_renderer); }

void Game::draw_texture(SDL_Texture* texture, int x, int y)
{
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

    SDL_RenderCopy(_renderer, texture, NULL, &dest);
}

void Game::handle_input() { _quit = _controller->handle_input(); }

int Game::run_game()
{

    while (!_quit)
    {
        std::uint32_t time = SDL_GetTicks();

        prepare_scene();
        handle_input();
        logic();
        draw();
        present_scene();

        SDL_Delay(count_wait_60fps(time));
    }

    return 0;
}

std::uint32_t Game::count_wait_60fps(const std::uint32_t& last)
{
    std::uint32_t delta = SDL_GetTicks() - last;

    //  16 is 1000 ms / 60 fps
    std::uint32_t wait = 16 - delta;

    wait = wait < 1 ? 1 : wait;
    wait = wait > 16 ? 16 : wait;

    return wait;
}

void Game::logic()
{
    player_logic();
    bullets_logic();
    enemy_logic();
    bullet_hit_enemy();
    bullet_hit_player();
}

void Game::enemy_logic()
{
    spawn_enemies();

    if (_enemies.empty())
    {
        return;
    }

    for (auto& e : _enemies)
    {
        e._x += e._dx;
        e._y += e._dy;
    }

    const auto enemy_deleter = [](const Enemy& e)
    { return e._x < -e._w; };

    const auto remained_enemies =
        std::remove_if(_enemies.begin(), _enemies.end(), enemy_deleter);

    if (remained_enemies - _enemies.begin() < _enemies.size())
    {
        _enemies.erase(remained_enemies);
    }

    enemy_fire();
}

void Game::enemy_fire()
{
    for (auto& e : _enemies)
    {
        if (e._reload > 0)
        {
            e._reload--;
        }
        else
        {
            _enemy_bullets.emplace_back(
                e._x, e._y, -BULLET_SPEED, 0,
                _rm.get_texture("enemy_bullet"));

            e._reload = e._default_reload;
        }
    }
}

void Game::spawn_enemies()
{
    if (--enemy_spawn_timer <= 0)
    {
        _enemies.emplace_back(_field_width, 0, -4, 0,
                              _rm.get_texture("enemy"));
        auto& last_enemy = _enemies[_enemies.size() - 1];
        last_enemy._y = get_random_int(_field_height - last_enemy._h);

        // frame rate is 60 and every 3 second
        enemy_spawn_timer = 1 * 60;
    }
}

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
    _enemy_bullets.erase(_enemy_bullets.begin(), _enemy_bullets.end());
    _max_score = std::max(_max_score, _score);
    _score = 0;
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
    _player->_dx = _player->_dy = 0;

    if (_player->_reload > 0)
    {
        _player->_reload--;
    }

    if ((_keyboard[SDL_SCANCODE_UP] == 1) ||
        (_keyboard[SDL_SCANCODE_W] == 1))
    {
        _player->_dy = -PLAYER_SPEED;
    }

    if ((_keyboard[SDL_SCANCODE_DOWN] == 1) ||
        (_keyboard[SDL_SCANCODE_S] == 1))
    {
        _player->_dy = PLAYER_SPEED;
    }

    if ((_keyboard[SDL_SCANCODE_LEFT] == 1) ||
        (_keyboard[SDL_SCANCODE_A] == 1))
    {
        _player->_dx = -PLAYER_SPEED;
    }

    if ((_keyboard[SDL_SCANCODE_RIGHT] == 1) ||
        (_keyboard[SDL_SCANCODE_D] == 1))
    {
        _player->_dx = PLAYER_SPEED;
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
        _player->_y + _player->_dy > _field_height - _player->_h)
    {
        _player->_dy = 0;
    }

    _player->_x += _player->_dx;
    _player->_y += _player->_dy;
}

void Game::fire_bullet()
{
    _bullets.emplace_back(_player->_x, _player->_y, BULLET_SPEED, 0,
                          _rm.get_texture("bullet"));

    _player->_reload = _player->_default_reload;
}

void Game::bullets_logic()
{
    if (!_bullets.empty())
    {
        for (auto& b : _bullets)
        {
            b._x += b._dx;
            b._y += b._dy;
        }

        const auto bullet_deleter = [this](const Entity& el)
        { return el._x > _field_width; };

        const auto remained_bullets = std::remove_if(
            _bullets.begin(), _bullets.end(), bullet_deleter);

        if (remained_bullets - _bullets.begin() < _bullets.size())
        {
            _bullets.erase(remained_bullets);
        }
    }

    if (!_enemy_bullets.empty())
    {
        for (auto& b : _enemy_bullets)
        {
            b._x += b._dx;
            b._y += b._dy;
        }

        const auto bullet_deleter = [this](const Entity& el)
        { return el._x > _field_width; };

        const auto remained_bullets =
            std::remove_if(_enemy_bullets.begin(), _enemy_bullets.end(),
                           bullet_deleter);

        if (remained_bullets - _enemy_bullets.begin() <
            _enemy_bullets.size())
        {
            _enemy_bullets.erase(remained_bullets);
        }
    }
}

void Game::draw()
{
    draw_player();
    draw_bullets();
    draw_enemies();
    draw_info();
}

void Game::draw_player()
{
    draw_texture(_player->_texture, _player->_x, _player->_y);
}

void Game::draw_bullets()
{
    for (const auto& b : _bullets)
    {
        draw_texture(b._texture, b._x, b._y);
    }
    for (const auto& b : _enemy_bullets)
    {
        draw_texture(b._texture, b._x, b._y);
    }
}

void Game::draw_enemies()
{
    for (const auto& e : _enemies)
    {
        draw_texture(e._texture, e._x, e._y);
    }
}

void Game::draw_info()
{
    render_text("Total Score: " + std::to_string(_score), 5, 5);
    render_text("Max Score: " + std::to_string(_max_score), 300, 5);
}

void Game::render_text(const std::string& text, int x, int y)
{
    SDL_Surface* text_surface =
        TTF_RenderText_Solid(_rm.get_font(), text.c_str(), _text_color);

    SDL_Texture* text_texture{nullptr};

    int w = 0;
    int h = 0;

    if (text_surface == nullptr)
    {
        printf("Unable to render text surface! SDL_ttf Error: %s\n",
               TTF_GetError());
    }
    else
    {
        // Create texture from surface pixels
        text_texture =
            SDL_CreateTextureFromSurface(_renderer, text_surface);
        if (text_texture == nullptr)
        {
            printf("Unable to create texture from rendered text! SDL "
                   "Error: %s\n",
                   SDL_GetError());
        }
        else
        {
            // Get image dimensions
            w = text_surface->w;
            h = text_surface->h;
        }

        // Get rid of old surface
        SDL_FreeSurface(text_surface);
    }

    draw_texture(text_texture, x, y);
}
