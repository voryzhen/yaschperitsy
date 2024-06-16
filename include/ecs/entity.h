#pragma once

#include <memory>
#include <string_view>
#include <vector>

#include "ecs/icomponent.h"
#include <window.h>

#include "SDL_events.h"

namespace yaschperitsy::ecs2
{

class Entity
{
    public:
        Entity(const std::string_view name) : _name(name) {}

        void update(const SDL_Event& event)
        {
            for (auto& c : _components)
            {
                c->update(event);
            }
        }

        void render(const app::SDL_RendererUPtr& renderer)
        {
            for (auto& c : _components)
            {
                c->render(renderer);
            }
        }

        bool is_active() const { return _active; }

        std::string_view name() const { return _name; }

        void destroy() { _active = false; }

        template <typename T> bool has_component() const
        {
            return _component_bitset[get_component_type_ID<T>()];
        }

        template <typename T> std::shared_ptr<T> get_component() const
        {
            auto icomponent =
                _component_array[get_component_type_ID<T>()];

            return std::static_pointer_cast<T>(icomponent);
        }

        template <typename T, typename... TArgs>
        std::shared_ptr<T> add_component(TArgs&&... args)
        {
            std::shared_ptr<T> component(
                new T(std::forward<TArgs>(args)...));

            _components.emplace_back(component);
            _component_array[get_component_type_ID<T>()] = component;
            _component_bitset[get_component_type_ID<T>()] = true;

            component->owner = this;
            component->init();

            return component;
        }

    private:
        bool _active = true;
        std::string_view _name;

        SComponentVector _components;

        SComponentArray _component_array;
        ComponentBitset _component_bitset;
};

using EntitySPtr = std::shared_ptr<Entity>;
using SEntityVector = std::vector<EntitySPtr>;

}; // namespace yaschperitsy::ecs2
