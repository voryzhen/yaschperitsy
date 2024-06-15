#pragma once

#include "ecs/components.h"
#include <memory>
#include <vector>

namespace yaschperitsy::app
{

class Entity
{
    public:
        Entity() = default;

        Entity(const std::string_view& name) : _name(name) {}

        void update(const SDL_Event& event)
        {
            for (auto& c : _components)
            {
                c->update(event);
            }
        }

        void render(const SDL_RendererUPtr& renderer)
        {
            for (auto& c : _components)
            {
                c->render(renderer);
            }
        }

        bool is_active() const { return _active; }

        void destroy() { _active = false; }

        template <typename T> bool has_component() const
        {
            return _component_bitset[get_component_type_id<T>];
        }

        template <typename T, typename... TArgs>
        T& add_component(TArgs&&... args)
        {
            T* c(new T(std::forward<TArgs>(args)...));
            c->owner = this;
            std::unique_ptr<Component> u_ptr{c};
            _components.emplace_back(std::move(u_ptr));

            _component_array[get_component_type_id<T>()] = c;
            _component_bitset[get_component_type_id<T>()] = true;

            c->init();
            return *c;
        }

        template <typename T> T* get_component() const
        {
            auto ptr = _component_array[get_component_type_id<T>()];
            return static_cast<T*>(ptr);
        }

        std::string_view _name;

    private:
        bool _active{true};
        std::vector<std::unique_ptr<Component>> _components;

        ComponentArray _component_array{};
        ComponentBitSet _component_bitset;
};

}; // namespace yaschperitsy::app
