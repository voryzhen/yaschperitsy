#pragma once

#include "core/renderer/Renderer.hpp"
#include "core/scene/Scene.hpp"
#include <core/Window.hpp>
#include <core/events/AppEvent.hpp>
#include <core/scene/LayerStack.hpp>

namespace yaschperitsy::core
{

class App
{
    public:
        App();

        virtual ~App() = default;

        void run_app();

        void push_layer(const LayerSPtr& layer) { _scene->push_layer(layer); }

        void pop_layer(const LayerSPtr& layer) { _scene->pop_layer(layer); }

        void set_scene(const renderer::SceneSPtr& scene)
        {
            _scene.reset(scene.get());
        }

    private:
        void on_event(const events::EventSPtr& event);
        bool on_window_close(const events::WindowCloseEventSPtr& event);

        bool _running = true;
        WindowUPtr _window;
        renderer::RendererUPtr _renderer;
        renderer::SceneSPtr _scene{nullptr};
};

}; // namespace yaschperitsy::core
