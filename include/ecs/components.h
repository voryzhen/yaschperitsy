#pragma once

#include "SDL_events.h"
#include "SDL_keycode.h"
#include "SDL_mouse.h"
#include "SDL_rect.h"
#include "SDL_render.h"
#include "SDL_timer.h"
#include "ecs/component.h"
#include "ecs/entity.h"
#include "resource_manager.h"
#include "utility/vector2D.h"
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <numbers>
#include <utility>

namespace yaschperitsy::ecs
{

class TransformComponent : public Component
{
    public:
        TransformComponent(int x, int y)
            : _position({static_cast<float>(x), static_cast<float>(y)})
        {
        }

        TransformComponent(int x, int y, float angle)
            : TransformComponent(x, y)

        {
            _angle = angle;
        }

        TransformComponent(int x, int y, int speed, float angle)
            : TransformComponent(x, y, angle)

        {
            _speed = speed;
        }

        Vector2D<float> position() const { return _position; }

        Vector2D<float> velocity() const { return _velocity; }

        void set_position(int x, int y)
        {
            _position = {static_cast<float>(x), static_cast<float>(y)};
        }

        void set_velocity(const Vector2D<float>& vel)
        {
            _velocity = vel;
        }

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

        float angle() const { return _angle; }

        void set_angle(float angle) { _angle = angle; }

        Vector2D<float> direction() { return _direction; }

        void set_direction(Vector2D<float> direction)
        {
            _direction = direction;
        }

    private:
        Vector2D<float> _position;
        Vector2D<float> _velocity;
        int _speed{3};
        float _angle{.0};
        Vector2D<float> _direction;
};

class SpriteComponent : public Component
{
    public:
        SpriteComponent() = default;

        SpriteComponent(resource::TextureSPtr texture)
            : _texture(std::move(texture))
        {
        }

        SpriteComponent(resource::TextureSPtr texture, int frames,
                        int speed)
            : _texture(std::move(texture)), _animated(true),
              _frames(frames), _speed(speed)
        {
        }

        void init() override
        {
            _position = owner->get_component<TransformComponent>();

            _src_rect.x = _src_rect.y = 0;

            _src_rect.h = _texture->_h;
            _src_rect.w = _texture->_w;

            _dest_rect.h = _texture->_h;
            _dest_rect.w = _texture->_w;
        }

        void update(const SDL_Event& /*e*/) override
        {
            if (_animated)
            {
                // TODO:
                // Here I should update _dest_rect as soon as I have
                // multiple sprite in one source
                // But I just will flip
                // Frames must be equals 2
                _flip = static_cast<bool>((SDL_GetTicks() / _speed) %
                                          _frames);
            }
            _dest_rect.x = static_cast<int>(_position->position().x());
            _dest_rect.y = static_cast<int>(_position->position().y());
        }

        void render(const app::SDL_RendererUPtr& renderer) override
        {
            SDL_RenderCopyEx(renderer.get(), _texture->_texture,
                             &_src_rect, &_dest_rect,
                             _position->angle(), nullptr,
                             _flip ? SDL_FLIP_NONE : SDL_FLIP_VERTICAL);
        }

        SDL_Rect get_texture_rect()
        {
            Vector2D<float> pos = {};
            if (_position != nullptr)
            {
                pos = _position->position();
            }
            return {static_cast<int>(pos.x()),
                    static_cast<int>(pos.y()), _texture->_w,
                    _texture->_h};
        }

    private:
        TransformComponent* _position{nullptr};
        resource::TextureSPtr _texture;
        SDL_Rect _src_rect{0, 0, 0, 0};
        SDL_Rect _dest_rect{0, 0, 0, 0};

        bool _animated = false;
        bool _flip = true;
        int _frames = 2;
        int _speed = 100;
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
            // TODO: refactor, very - very
            {
                auto pos = _transformComponent->position();
                auto vel = _transformComponent->velocity();

                if (pos.x() + 3 * vel.x() < 0 ||
                    pos.x() + 3 * vel.x() > 1230)
                {
                    _transformComponent->set_x_velocity(.0f);
                }

                if (pos.y() + 3 * vel.y() < 0 ||
                    pos.y() + 3 * vel.y() > 670)
                {
                    _transformComponent->set_y_velocity(.0f);
                }
            }
        }

    private:
        TransformComponent* _transformComponent{nullptr};
};

class MouseController : public Component
{
    public:
        void init() override
        {
            _transformComponent =
                owner->get_component<TransformComponent>();
        }

        void update(const SDL_Event& /*e*/) override
        {
            int x = 0;
            int y = 0;
            SDL_GetMouseState(&x, &y);
            _mouse_pos = {static_cast<float>(x), static_cast<float>(y)};

            // update angle
            auto pos = _transformComponent->position();

            float dy = static_cast<float>(y) - pos.y();
            float dx = static_cast<float>(x) - pos.x() + 25;

            _angle = -90 + atan2(dy, dx) * (180 / std::numbers::pi);

            _transformComponent->set_angle(_angle +
                                           static_cast<float>(90.0));

            float d2 = dy * dy + dx * dx;
            float d = sqrtf(d2);

            float xx = dx / d;
            float yy = dy / d;

            _direction = Vector2D(xx, yy);
            _transformComponent->set_direction(_direction);
        }

    private:
        TransformComponent* _transformComponent{nullptr};
        Vector2D<float> _mouse_pos;
        Vector2D<float> _direction;
        float _angle = 0;
};

class FireReloadComponent : public Component
{
    public:
        FireReloadComponent() = default;
        FireReloadComponent(std::int8_t reload) : _reload(reload) {};

        void update(const SDL_Event& /*e*/) override
        {
            if (_curr_load > 0)
            {
                _curr_load--;
            }
        }

        bool is_reloaded() const { return _curr_load == 0; }

        void shot() { _curr_load = _reload; }

    private:
        std::int8_t _reload{8};
        std::int8_t _curr_load{8};
};

}; // namespace yaschperitsy::ecs
