#pragma once

#include "SDL_events.h"
#include "SDL_render.h"
#include "window.h"
#include <array>
#include <bitset>

namespace yaschperitsy::ecs
{

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

class Entity;

// using SDL_RendererSPtr =
// std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;

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

        virtual void update(const SDL_Event& event) {}

        virtual void render(const app::SDL_RendererUPtr& renderer) {}

        virtual ~Component() {}
};

using ComponentBitSet = std::bitset<max_components>;
using ComponentArray = std::array<Component*, max_components>;

}; // namespace yaschperitsy::ecs
