#pragma once

#include "Component.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Entity.hpp"
#include "GraphicEngine/Input/Input.hpp"
#include "Logger/Logger.hpp"

class KeyboardController : public Component
{
    public:
        KeyboardController() {}

        void events() override {}

        void update() override
        {

            int x_dir = is_left() ? -1 : (is_right() ? 1 : 0);
            int y_dir = is_up() ? -1 : (is_down() ? 1 : 0);

            // check_borders
            auto pos = transf_comp_->position();
            auto vel = transf_comp_->velocity();

            auto next_x = pos.x + x_dir * vel;
            auto next_y = pos.y + y_dir * vel;

            if (next_x < 0 || next_x > (1280. - 80.))
            {
                x_dir = 0;
            }

            if (next_y < 0 || next_y > (720. - 80.))
            {
                y_dir = 0;
            }

            transf_comp_->set_direction({ .x = static_cast<float>(x_dir),
                                          .y = static_cast<float>(y_dir) });
        }

        void render(const Renderer& ren) override {}

        void on_event() override {}

        void init() override
        {
            transf_comp_ = owner_.lock()->get_component<TransformComponent>();
            if (!transf_comp_)
            {
                Logger().error("Wrong components init. Transform should be "
                               "init before KeyboardController");
            }
        }

    private:
        static bool is_left()
        {
            return Input::is_key_pressed(KEYS::A) ||
                   Input::is_key_pressed(KEYS::Left);
        }

        static bool is_right()
        {
            return Input::is_key_pressed(KEYS::D) ||
                   Input::is_key_pressed(KEYS::Right);
        }

        static bool is_down()
        {
            return Input::is_key_pressed(KEYS::S) ||
                   Input::is_key_pressed(KEYS::Down);
        }

        static bool is_up()
        {
            return Input::is_key_pressed(KEYS::W) ||
                   Input::is_key_pressed(KEYS::Up);
        }

        TransformComponentPtr transf_comp_;
};
using KeyboardControllerPtr = std::shared_ptr<KeyboardController>;
