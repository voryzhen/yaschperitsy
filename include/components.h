#pragma once

#include "SDL_rect.h"
#include "SDL_render.h"
#include "ecs.h"
#include "resource_manager.h"
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

        SpriteComponent(Texture texture) : _texture(texture) {}

        void init() override
        {
            _position = owner->get_component<PositionComponent>();

            _src_rect.x = _src_rect.y = 0;

            _src_rect.h = _texture._h;
            _src_rect.w = _texture._w;

            _dest_rect.h = _texture._h;
            _dest_rect.w = _texture._w;
        }

        void update() override
        {
            _dest_rect.x = _position->x();
            _dest_rect.y = _position->y();
        }

        void render(SDL_Renderer* renderer) override
        {
            SDL_RenderCopy(renderer, _texture._texture, &_src_rect,
                           &_dest_rect);
        }

    private:
        PositionComponent* _position{nullptr};
        Texture _texture{nullptr};
        SDL_Rect _src_rect{0, 0, 0, 0};
        SDL_Rect _dest_rect{0, 0, 0, 0};
};
