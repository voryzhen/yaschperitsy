#pragma once

#include "Events/Event.hpp"
#include "Renderer.hpp"
#include "ResourceManager/ResourceManager.hpp"
#include <functional>

using EventCallbackFn = std::function<void(const EventSPtr&)>;

class GraphicEngine
{
    public:
        static GraphicEngine& get();

        ErrorCode initialize() const;
        ErrorCode finalize() const;

        void set_event_callback(const EventCallbackFn& ec);

        const Renderer& renderer() const;
        const ResourceManager& resource_manager() const;

        int events() const;
        int update() const;
        int render() const;

    private:
        GraphicEngine();
        const Renderer& _ren;
        const ResourceManager& _rm;
        EventCallbackFn _event_callback;
};
