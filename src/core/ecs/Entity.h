#pragma once

#include <algorithm>
#include <memory>
#include <string_view>

#include "core/ecs/IComponent.h"
#include <core/Window.h>

#include "SDL_events.h"

namespace yaschperitsy::ecs
{

enum class EntityType
{
    player = 0,
    yaschperitsa,
    ammunition
};

class Entity : public std::enable_shared_from_this<Entity>
{
    public:
        Entity(EntityType type) : _entity_type(type) {}

        void update(const SDL_Event& event)
        {
            std::for_each(_components.begin(), _components.end(),
                          [&](auto& c) { c->update(event); });
        }

        void render(const core::SDL_RendererUPtr& renderer)
        {
            std::for_each(_components.begin(), _components.end(),
                          [&](auto& c) { c->render(renderer); });
        }

        bool is_active() const { return _active; }

        EntityType type() const { return _entity_type; }

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

            component->owner = this->weak_from_this();
            component->init();

            return component;
        }

    private:
        bool _active = true;
        EntityType _entity_type{EntityType::yaschperitsa};

        SComponentVector _components;

        SComponentArray _component_array;
        ComponentBitset _component_bitset;
};

using EntitySPtr = std::shared_ptr<Entity>;
using SEntityVector = std::vector<EntitySPtr>;

}; // namespace yaschperitsy::ecs
