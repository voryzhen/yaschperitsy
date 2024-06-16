#pragma once

#include <ecs/icomponent.h>
#include <memory>
#include <utility/vector2D.h>

namespace yaschperitsy::ecs::components
{

class TransformComponent : public IComponent
{
    public:
        TransformComponent(int x, int y) : _position(x, y) {}

        TransformComponent(int x, int y, int speed)
            : TransformComponent(x, y)
        {
            _speed = speed;
        }

        TransformComponent(int x, int y, int speed, float angle)
            : TransformComponent(x, y, speed)
        {
            _angle = angle;
        }

        float angle() const { return _angle; }

        Vector2D<float> direction() const { return _direction; }

        Vector2D<float> position() const { return _position; }

        Vector2D<float> velocity() const { return _velocity; }

        void set_angle(float angle) { _angle = angle; }

        void set_direction(Vector2D<float> direction)
        {
            _direction = direction;
        }

        void set_position(int x, int y)
        {
            _position = {static_cast<float>(x), static_cast<float>(y)};
        }

        void set_velocity(const Vector2D<float>& vel)
        {
            _velocity = vel;
        }

        void set_x_velocity(int x_vel)
        {
            _velocity = {static_cast<float>(x_vel), _velocity.y()};
        }

        void set_y_velocity(int y_vel)
        {
            _velocity = {_velocity.x(), static_cast<float>(y_vel)};
        }

        void update(const SDL_Event& /*e*/) override
        {
            _position += (_velocity * _speed);
        }

        void render(const app::SDL_RendererUPtr& renderer) override {}

        void init() override {}

    private:
        int _speed{3};
        float _angle{.0};

        Vector2D<float> _position;
        Vector2D<float> _velocity;
        Vector2D<float> _direction;
};

using TransformComponentSPtr = std::shared_ptr<TransformComponent>;

}; // namespace yaschperitsy::ecs::components
