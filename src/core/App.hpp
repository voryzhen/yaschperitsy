#pragma once

#include "core/renderer/Renderer.hpp"
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

        void push_layer(const LayerSPtr& layer)
        {
            _layer_stack.push_layer(layer);
        }

        void pop_layer(const LayerSPtr& layer)
        {
            _layer_stack.pop_layer(layer);
        }

    private:
        void on_event(const events::EventSPtr& event);
        bool on_window_close(const events::WindowCloseEventSPtr& event);

        bool _running = true;
        WindowUPtr _window;
        renderer::RendererUPtr _renderer;
        LayerStack _layer_stack;
};

}; // namespace yaschperitsy::core
