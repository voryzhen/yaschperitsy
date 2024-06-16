#pragma once

#include <ecs2/icomponent.h>
#include <memory>
#include <utility/vector2D.h>

namespace yaschperitsy::ecs2::components
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

        Vector2D<int> direction() const { return _direction; }

        Vector2D<int> position() const { return _position; }

        Vector2D<int> velocity() const { return _velocity; }

        void set_angle(float angle) { _angle = angle; }

        void set_direction(Vector2D<int> direction)
        {
            _direction = direction;
        }

        void set_position(int x, int y) { _position = {x, y}; }

        void set_velocity(const Vector2D<int>& vel) { _velocity = vel; }

        void set_x_velocity(int x_vel)
        {
            _velocity = {x_vel, _velocity.y()};
        }

        void set_y_velocity(int y_vel)
        {
            _velocity = {_velocity.x(), y_vel};
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

        Vector2D<int> _position;
        Vector2D<int> _velocity;
        Vector2D<int> _direction;
};

using TransformComponentSPtr = std::shared_ptr<TransformComponent>;

}; // namespace yaschperitsy::ecs2::components
