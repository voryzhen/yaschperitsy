#pragma once

#include "SDL_render.h"
#include <algorithm>
#include <array>
#include <bitset>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID get_component_type_id()
{
    static ComponentID lastID = 0;
    return lastID++;
}

template <typename T>
inline ComponentID get_component_type_id() noexcept
{
    static ComponentID typeID = get_component_type_id();
    return typeID;
}

constexpr std::size_t max_components = 32;

using ComponentBitSet = std::bitset<max_components>;
using ComponentArray = std::array<Component*, max_components>;

class Component
{
    public:
        Component() = default;
        Component(const Component&) = default;
        Component& operator=(const Component&) = default;

        Component(Component&&) = default;
        Component& operator=(Component&&) = default;

        Entity* owner{nullptr};

        virtual void init() {}

        virtual void update() {}

        virtual void render(SDL_Renderer* renderer) {}

        virtual ~Component() {}
};

class Entity
{
    public:
        void update()
        {
            for (auto& c : _components)
            {
                c->update();
            }
        }

        void render(SDL_Renderer* renderer)
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

    private:
        bool _active{true};
        std::vector<std::unique_ptr<Component>> _components;

        ComponentArray _component_array{};
        ComponentBitSet _component_bitset;
};

class Manager
{
    public:
        void update()
        {
            for (auto& e : _entities)
            {
                e->update();
            }
        }

        void render(SDL_Renderer* renderer)
        {
            for (auto& e : _entities)
            {
                e->render(renderer);
            }
        }

        void refresh()
        {
            _entities.erase(std::remove_if(_entities.begin(),
                                           _entities.end(),
                                           [](const auto& e)
                                           { return !e->is_active(); }),
                            _entities.end());
        }

        Entity& add_entity()
        {
            auto e = new Entity();
            std::unique_ptr<Entity> u_e(e);
            _entities.emplace_back(std::move(u_e));
            return *e;
        }

    private:
        std::vector<std::unique_ptr<Entity>> _entities;
};
