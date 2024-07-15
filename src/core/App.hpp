#pragma once

#include "core/renderer/Renderer.hpp"
#include "core/scene/Scene.hpp"
#include <core/Window.hpp>
#include <core/events/AppEvent.hpp>
#include <core/scene/LayerStack.hpp>
#include <string_view>
#include <type_traits>

namespace yaschperitsy::core
{

class App
{
    public:
        App();

        virtual ~App() { renderer::Renderer::clear(); };

        void run_app();

        void set_scene(const renderer::SceneSPtr& scene) { _scene = scene; }

        std::string scene() const { return _scene->name(); };

        virtual void shutdown() { _running = false; }

        virtual void update() {}

    private:
        void on_event(const events::EventSPtr& event);
        bool on_window_close(const events::WindowCloseEventSPtr& event);

        bool _running = true;
        WindowUPtr _window;
        renderer::SceneSPtr _scene{nullptr};
};

}; // namespace yaschperitsy::core
