#pragma once

#include "ECS/TypesID.hpp"
#include "GraphicEngine/Renderer.hpp"

#include <memory>
#include <unordered_map>

class Entity;

class Component;
using ComponentPtr = std::shared_ptr<Component>;
using ComponentStore = std::unordered_map<ComponentTypeID, ComponentPtr>;

class Component
{
    public:
        Component() = default;
        virtual ~Component() = default;

        virtual void events() = 0;
        virtual void update() = 0;
        virtual void render(const Renderer& ren) = 0;

        virtual void on_event() = 0;

        virtual void init() = 0;

        std::weak_ptr<Entity> owner_;
};
