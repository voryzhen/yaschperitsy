#pragma once

#include <array>
#include <bitset>
#include <memory>
#include <vector>

#include <app/Window.h>

#include "SDL_events.h"

namespace yaschperitsy::ecs
{

class Entity;

using ComponentTypeID = std::uint64_t;

inline ComponentTypeID get_component_type_ID()
{
    static ComponentTypeID type_ID = 0;
    return type_ID++;
}

template <typename T>
inline ComponentTypeID get_component_type_ID() noexcept
{
    static ComponentTypeID typeID = get_component_type_ID();
    return typeID;
}

constexpr std::uint64_t max_components = 32;

class IComponent
{
    public:
        Entity* owner{nullptr};
        virtual void init() = 0;
        virtual void update(const SDL_Event& e) = 0;
        virtual void render(const app::SDL_RendererUPtr& renderer) = 0;
        virtual ~IComponent() {};
};

using IComponentUPtr = std::unique_ptr<IComponent>;
using IComponentSPtr = std::shared_ptr<IComponent>;

using ComponentBitset = std::bitset<max_components>;
using SComponentArray = std::array<IComponentSPtr, max_components>;
using SComponentVector = std::vector<IComponentSPtr>;

}; // namespace yaschperitsy::ecs
