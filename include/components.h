#pragma once

#include "SDL_rect.h"
#include "SDL_render.h"
#include "ecs.h"
#include <cstdlib>

class PositionComponent : public Component
{
    public:
        PositionComponent(int x, int y) : _x(x), _y(y) {}

        int x() const { return _x; }

        int y() const { return _y; }

        void set_pos(int x, int y)
        {
            _x = x;
            _y = y;
        }

        void update() override { _x++; }

    private:
        int _x{0};
        int _y{0};
};

class SpriteComponent : public Component
{
    public:
        SpriteComponent() = default;

        SpriteComponent(SDL_Texture* texture) : _texture(texture) {}

        void init() override
        {
            _position = owner->get_component<PositionComponent>();

            _src_rect.x = _src_rect.y = 0;
            _src_rect.h = _src_rect.w = 32;

            _dest_rect.h = _dest_rect.w = 64;
        }

        void update() override
        {
            _dest_rect.x = _position->x();
            _dest_rect.y = _position->y();
        }

        void render(SDL_Renderer* renderer) override
        {
            SDL_RenderCopy(renderer, _texture, &_src_rect, &_dest_rect);
        }

    private:
        PositionComponent* _position{nullptr};
        SDL_Texture* _texture{nullptr};
        SDL_Rect _src_rect{0, 0, 0, 0};
        SDL_Rect _dest_rect{0, 0, 0, 0};
};
