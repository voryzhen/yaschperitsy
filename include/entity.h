#pragma once

#include <SDL.h>

static constexpr int PLAYER_SPEED{4};
static constexpr int BULLET_SPEED{16};
static constexpr int PLAYER_BULLET{0};
static constexpr int ENEMY_BULLET{1};

class Entity
{
    public:
        Entity(SDL_Texture* texture) : _texture(texture)
        {
            SDL_QueryTexture(_texture, NULL, NULL, &_w, &_h);
        }

        Entity(int x, int y, int dx, int dy, SDL_Texture* texture)
            : _x(x), _y(y), _dx(dx), _dy(dy), _texture(texture)
        {
            SDL_QueryTexture(_texture, NULL, NULL, &_w, &_h);
        }

        virtual ~Entity() = default;

        int _x{100};
        int _y{100};

        int _dx{0};
        int _dy{0};

        int _h{0};
        int _w{0};

        SDL_Texture* _texture{nullptr};
};

class Player : public Entity
{
    public:
        Player(SDL_Texture* texture) : Entity(texture) {}

        Player(int x, int y, int dx, int dy, SDL_Texture* texture)
            : Entity(x, y, dx, dy, texture)
        {
        }

        void reset_player()
        {
            _x = 100;
            _y = 100;
        }

        int _default_reload{8};
        int _reload{_default_reload};
        int _health{1};
};

class Enemy : public Entity
{
    public:
        Enemy(SDL_Texture* texture) : Entity(texture) {}

        Enemy(int x, int y, int dx, int dy, SDL_Texture* texture)
            : Entity(x, y, dx, dy, texture)
        {
        }

        int _default_reload{80};
        int _reload{_default_reload};
        int _health{1};
};

class Bullet : public Entity
{
    public:
        Bullet(SDL_Texture* texture) : Entity(texture) {}

        Bullet(int x, int y, int dx, int dy, SDL_Texture* texture)
            : Entity(x, y, dx, dy, texture)
        {
        }
};
