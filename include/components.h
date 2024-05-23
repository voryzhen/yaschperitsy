#pragma once

#include "SDL_rect.h"
#include "SDL_render.h"
#include "ecs.h"
#include "resource_manager.h"
#include "vector2D.h"
#include <cstdlib>

class TransformComponent : public Component
{
    public:
        TransformComponent(int x, int y)
            : _position({static_cast<float>(x), static_cast<float>(y)})
        {
        }

        Vector2D position() const { return _position; }

        void set_pos(int x, int y)
        {
            _position = {static_cast<float>(x), static_cast<float>(y)};
        }

        void update() override { _position += {1.0f, .0f}; }

    private:
        Vector2D _position;
};

class SpriteComponent : public Component
{
    public:
        SpriteComponent() = default;

        SpriteComponent(Texture texture) : _texture(texture) {}

        void init() override
        {
            _position = owner->get_component<TransformComponent>();

            _src_rect.x = _src_rect.y = 0;

            _src_rect.h = _texture._h;
            _src_rect.w = _texture._w;

            _dest_rect.h = _texture._h;
            _dest_rect.w = _texture._w;
        }

        void update() override
        {
            _dest_rect.x = static_cast<int>(_position->position().x());
            _dest_rect.y = static_cast<int>(_position->position().y());
        }

        void render(SDL_Renderer* renderer) override
        {
            SDL_RenderCopy(renderer, _texture._texture, &_src_rect,
                           &_dest_rect);
        }

    private:
        TransformComponent* _position{nullptr};
        Texture _texture{nullptr};
        SDL_Rect _src_rect{0, 0, 0, 0};
        SDL_Rect _dest_rect{0, 0, 0, 0};
};
