#pragma once

#include "ECS/Components/SpriteComponent.hpp"
#include "ECS/Components/TransformComponent.hpp"
#include "ECS/Entity.hpp"
#include "Events/MouseEvent.hpp"
#include "Yaschperitsy/Events/UIEvent.hpp"
#include <array>
#include <utility>
#include <vector>

using EventCallbackFn = std::function<void(const EventSPtr&)>;

class UIButton : public Entity
{
    public:
        static EntityPtr create(UIEventCode button_id, int width, int height,
                                const std::array<RenderData, 3>& render_data,
                                const EventCallbackFn& callback)
        {
            int x_pos = (width - render_data.at(0).w) / 2;
            int y_pos = height;
            EntityPtr label = std::make_shared<UIButton>(
                button_id,
                RenderData { .x = x_pos,
                             .y = y_pos,
                             .w = render_data.at(0).w,
                             .h = render_data.at(0).h,
                             .id = render_data.at(0).id,
                             .angle = render_data.at(0).angle },
                std::vector<int> { render_data.at(0).id, render_data.at(1).id,
                                   render_data.at(2).id },
                callback);

            label->add_component<TransformComponent>(x_pos, y_pos);
            label->add_component<SpriteComponent>(render_data[0]);
            return label;
        }

        void on_event(const EventSPtr& event) override
        {
            EventDispatcher dispatcher(event);
            dispatcher.dispatch<MouseMovedEvent>(
                [this](const MouseMovedEventSPtr& event)
                { return on_mouse_move_event(event); });
            dispatcher.dispatch<MouseButtonPressedEvent>(
                [this](const MouseButtonPressedEventSPtr& event)
                { return on_mouse_pressed_event(event); });
            dispatcher.dispatch<MouseButtonReleasedEvent>(
                [this](const MouseButtonReleasedEventSPtr& event)
                { return on_mouse_released_event(event); });
        };

        void update() override
        {
            int curr_id { 0 };
            if (is_clicked_ && is_hover_)
            {
                curr_id = ids_[2];
            }
            else if (is_hover_)
            {
                curr_id = ids_[1];
            }
            else
            {
                curr_id = ids_[0];
            }
            render_data_.id = curr_id;

            if (auto comp = get_component<SpriteComponent>(); comp)
            {
                comp->set_render_data(render_data_);
            }
        }

        bool on_mouse_move_event(const MouseMovedEventSPtr& event)
        {
            is_hover_ = is_hover(event->x(), event->y());
            if (!is_hover_)
            {
                is_clicked_ = false;
            }
            return true;
        }

        bool on_mouse_pressed_event(const MouseButtonPressedEventSPtr& event)
        {
            is_clicked_ = is_hover(event->x(), event->y());
            if (is_clicked_)
            {
                callback_(std::make_shared<UIEvent>(button_id_));
            }
            return true;
        }

        bool
        on_mouse_released_event(const MouseButtonReleasedEventSPtr& /*event*/)
        {
            is_clicked_ = false;
            return true;
        }

        UIButton(UIEventCode button_id, const RenderData& render_data,
                 const std::vector<int>& ids, EventCallbackFn callback)
            : Entity(get_entity_typeID<UIButton>()), button_id_(button_id),
              render_data_(render_data), ids_(ids), callback_(callback) {};

    private:
        bool is_hover(int x_pos, int y_pos) const
        {
            int dx_pos = x_pos - render_data_.x;
            int dy_pos = y_pos - render_data_.y;

            if (dx_pos < 0 || dx_pos > render_data_.w)
            {
                return false;
            }
            if (dy_pos < 0 || dy_pos > render_data_.h)
            {
                return false;
            }
            return true;
        }

        bool is_hover_ { false };
        bool is_clicked_ { false };

        UIEventCode button_id_ { UIEventCode::Exit };
        RenderData render_data_;
        std::vector<int> ids_;

        EventCallbackFn callback_;
};
