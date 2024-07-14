#pragma once

#include "core/events/Event.hpp"
#include "core/scene/Layer.hpp"
#include "core/scene/LayerStack.hpp"
#include <algorithm>
#include <memory>

namespace yaschperitsy::core::renderer
{

class Scene
{
    public:
        Scene() = default;
        Scene(const LayerStack& layers) : _layers(layers) {};

        void render(SDL_Renderer* render)
        {
            std::for_each(_layers.cbegin(), _layers.cend(),
                          [render](const LayerSPtr& l) { l->render(render); });
        }

        void push_layer(const LayerSPtr& layer) { _layers.push_layer(layer); }

        void pop_layer(const LayerSPtr& layer) { _layers.pop_layer(layer); }

        void update()
        {
            for (auto& l : _layers)
            {
                l->update();
            }
        }

        void on_event(const events::EventSPtr& e)
        {
            for (auto& l : _layers)
            {
                l->on_event(e);
            }
        }

    private:
        LayerStack _layers;
};

using SceneSPtr = std::unique_ptr<Scene>;

} // namespace yaschperitsy::core::renderer
