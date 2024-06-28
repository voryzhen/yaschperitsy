#pragma once

#include <ecs/IComponent.h>
#include <utility/Vector2D.h>

namespace yaschperitsy::ecs::components
{

class TransformComponent : public IComponent
{
    public:
        TransformComponent(float x, float y) : _position(x, y) {}

        TransformComponent(float x, float y, int speed)
            : TransformComponent(x, y)
        {
            _speed = speed;
        }

        TransformComponent(float x, float y, int speed, float angle)
            : TransformComponent(x, y, speed)
        {
            _angle = angle;
        }

        int speed() const { return _speed; }

        void set_speed(int speed) { _speed = speed; }

        float angle() const { return _angle; }

        void set_angle(float angle) { _angle = angle; }

        Vector2D<float> direction() const { return _direction; }

        void set_direction(Vector2D<float> direction)
        {
            _direction = direction;
        }

        Vector2D<float> position() const { return _position; }

        void set_position(float x, float y) { _position = {x, y}; }

        Vector2D<float> velocity() const { return _velocity; }

        void set_velocity(const Vector2D<float>& vel)
        {
            _velocity = vel;
        }

        void set_x_velocity(float x_vel) { _velocity.set_x(x_vel); }

        void set_y_velocity(float y_vel) { _velocity.set_y(y_vel); }

        void update(const SDL_Event& /*e*/) override
        {
            _position += (_velocity * _speed);
        }

        void render(const core::SDL_RendererUPtr& renderer) override {}

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
