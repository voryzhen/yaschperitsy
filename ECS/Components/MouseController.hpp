#pragma once

#include "Component.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Entity.hpp"
#include "IOSystem/Input/Input.hpp"
#include "Logger/Logger.hpp"

#include <numbers>

constexpr float rad2grad = 180.0f / std::numbers::pi_v<float>;

class MouseController : public Component
{
    public:
        MouseController() {}

        void events() override {}

        void update() override
        {
            auto mouse_pos = Input::mouse_position();
            auto entity_pos = transf_comp_->position();
            auto vec = mouse_pos - entity_pos;
            vec.normalize();
            transf_comp_->set_view_direction(vec);
        }

        void render(const Renderer& ren) override {}

        void on_event() override {}

        void init() override
        {
            transf_comp_ = owner_.lock()->get_component<TransformComponent>();
            if (!transf_comp_)
            {
                Logger().error("Wrong components init. Transform should be "
                               "init before Mouse");
            }
        }

    private:
        TransformComponentPtr transf_comp_;
};
using MouseControllerPtr = std::shared_ptr<MouseController>;

// ========
