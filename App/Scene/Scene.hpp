#pragma once

#include "ECS/Manager.hpp"
#include "IOSystem/Renderer.hpp"
#include <memory>

class Scene
{
    public:
        Scene() : man_(std::make_shared<Manager>()) {}
        virtual ~Scene() = default;

        virtual void on_event(const EventSPtr& event);
        virtual void events();
        virtual void update();
        virtual void render(const Renderer& ren);

        ManagerPtr man_;
};
using ScenePtr = std::shared_ptr<Scene>;
