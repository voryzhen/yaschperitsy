#pragma once

#include "core/Layer.h"
#include "core/LayerStack.h"
#include <core/Logger.h> // TODO: remove ?
#include <core/ResourceManager.h>
#include <core/Window.h>
#include <core/events/AppEvent.h>
#include <core/events/Event.h>
#include <ui/ScreenManager.h>

#include <SDL_events.h>

namespace yaschperitsy::core
{

using ResourceMap =
    std::unordered_map<std::string_view, std::string_view>;

class App
{
    public:
        // New api
        App();
        virtual ~App();
        void new_run_app();
        bool load_assets(const resource::ResourceMap&);
        bool load_fonts(const resource::ResourceMap&);

        // Old api
        App(bool old);
        void on_event(const events::EventSPtr& event);

        void push_layer(const LayerSPtr& layer)
        {
            _layer_stack.push_layer(layer);
        }

        void pop_layer(const LayerSPtr& layer)
        {
            _layer_stack.pop_layer(layer);
        }

        const SDL_RendererUPtr& renderer() const
        {
            return _window->renderer();
        }

    private:
        void run_app();

        void handle_events();
        void update();
        void render();

        bool on_window_close(const events::WindowCloseEventSPtr& event);

        SDL_Event _event{};
        bool _running = true;

        WindowUPtr _window;
        resource::ResourceManagerUPtr _resource_manager;
        ui::ScreenManagerUPtr _screen_manager;

        LayerStack _layer_stack;
};

} // namespace yaschperitsy::core
