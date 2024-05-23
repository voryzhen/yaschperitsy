#pragma once

#include "SDL_events.h"
#include "SDL_keycode.h"
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

        void set_position(int x, int y)
        {
            _position = {static_cast<float>(x), static_cast<float>(y)};
        }

        void set_velocity(const Vector2D& vel) { _velocity = vel; }

        void set_x_velocity(float x_vel)
        {
            _velocity = {x_vel, _velocity.y()};
        }

        void set_y_velocity(float y_vel)
        {
            _velocity = {_velocity.x(), y_vel};
        }

        void update(const SDL_Event& /*e*/) override
        {
            _position += (_velocity * _speed);
        }

    private:
        Vector2D _position;
        Vector2D _velocity;
        int _speed{3};
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

        void update(const SDL_Event& /*e*/) override
        {
            _dest_rect.x = static_cast<int>(_position->position().x());
            _dest_rect.y = static_cast<int>(_position->position().y());
        }

        void render(SDL_Renderer* renderer) override
        {
            SDL_RenderCopy(renderer, _texture._texture, &_src_rect,
                           &_dest_rect);
        }

        SDL_Rect get_texture_rect()
        {
            Vector2D pos = {};
            if (_position != nullptr)
            {
                pos = _position->position();
            }
            return {static_cast<int>(pos.x()),
                    static_cast<int>(pos.y()), _texture._w,
                    _texture._h};
        }

    private:
        TransformComponent* _position{nullptr};
        Texture _texture{nullptr};
        SDL_Rect _src_rect{0, 0, 0, 0};
        SDL_Rect _dest_rect{0, 0, 0, 0};
};

class KeyboardController : public Component
{
    public:
        void init() override
        {
            _transformComponent =
                owner->get_component<TransformComponent>();
        }

        void update(const SDL_Event& e) override
        {
            if (e.type == SDL_KEYDOWN)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_UP:
                case SDLK_w:
                    _transformComponent->set_y_velocity(-1.f);
                    break;

                case SDLK_LEFT:
                case SDLK_a:
                    _transformComponent->set_x_velocity(-1.f);
                    break;

                case SDLK_DOWN:
                case SDLK_s:
                    _transformComponent->set_y_velocity(1.f);
                    break;

                case SDLK_RIGHT:
                case SDLK_d:
                    _transformComponent->set_x_velocity(1.f);
                    break;
                default:
                    break;
                }
            }
            if (e.type == SDL_KEYUP)
            {
                switch (e.key.keysym.sym)
                {
                case SDLK_UP:
                case SDLK_w:
                    _transformComponent->set_y_velocity(.0f);
                    break;

                case SDLK_LEFT:
                case SDLK_a:
                    _transformComponent->set_x_velocity(.0f);
                    break;

                case SDLK_DOWN:
                case SDLK_s:
                    _transformComponent->set_y_velocity(.0f);
                    break;

                case SDLK_RIGHT:
                case SDLK_d:
                    _transformComponent->set_x_velocity(.0f);
                    break;
                default:
                    break;
                }
            }
        }

    private:
        TransformComponent* _transformComponent{nullptr};
};
