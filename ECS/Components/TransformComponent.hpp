#pragma once

#include "Component.hpp"
#include "Utility/Vector.hpp"
#include <limits>

class TransformComponent : public Component
{
    public:
        TransformComponent() {}
        TransformComponent(float x, float y)
            : position_(Vector2D<float> { .x = x, .y = y })
        {
        }

        explicit TransformComponent(const Vector2D<float>& position)
            : position_(position)
        {
        }

        TransformComponent(const Vector2D<float>& position, float velocity)
            : position_(position), velocity_(velocity)
        {
        }

        void events() override {}

        void update() override
        {
            position_.x += direction_.x * velocity_;
            position_.y += direction_.y * velocity_;
        }

        void render(const Renderer& ren) override {}

        void on_event() override {}

        void init() override {}

        Vector2D<float> position() const { return position_; }

        void set_position(const Vector2D<float>& position)
        {
            position_ = position;
        }

        Vector2D<float> direction() const { return direction_; };

        void set_direction(const Vector2D<float>& direction)
        {
            direction_ = direction;
        };

        Vector2D<float> view_direction() const { return view_direction_; };

        void set_view_direction(const Vector2D<float>& view_direction)
        {
            view_direction_ = view_direction;
        };

        float velocity() const { return velocity_; }

        void set_velocity(float velocity) { velocity_ = velocity; }

    private:
        Vector2D<float> position_ { .x = std::numeric_limits<float>::max(),
                                    .y = std::numeric_limits<float>::max() };
        Vector2D<float> direction_ {};
        Vector2D<float> view_direction_ {};
        float velocity_ { 3.0f };
};
using TransformComponentPtr = std::shared_ptr<TransformComponent>;
