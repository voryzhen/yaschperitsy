#pragma once

#include <memory>

#include "core/events/Event.hpp"
#include "core/scene/Layer.hpp"
#include "core/scene/LayerStack.hpp"

namespace yaschperitsy::core::renderer
{

class Scene
{
    public:
        Scene() = default;
        Scene(const LayerStack& layers) : _layers(layers) {};

        void render(SDL_Renderer* render);

        void push_layer(const LayerSPtr& layer);

        void pop_layer(const LayerSPtr& layer);

        void update();
        void on_event(const events::EventSPtr& e);

    private:
        LayerStack _layers;
};

using SceneSPtr = std::shared_ptr<Scene>;
using SceneUPtr = std::unique_ptr<Scene>;

}; // namespace yaschperitsy::core::renderer
