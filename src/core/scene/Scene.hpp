#pragma once

#include <memory>
#include <string>
#include <utility>

#include "core/events/Event.hpp"
#include "core/scene/Layer.hpp"
#include "core/scene/LayerStack.hpp"

namespace yaschperitsy::core::renderer
{

class Scene
{
    public:
        Scene() = default;

        Scene(std::string name) : _name(std::move(name)) {}

        Scene(const LayerStack& layers) : _layers(layers) {};

        Scene(std::string name, const LayerStack& layers)
            : _name(std::move(name)), _layers(layers)
        {
        }

        virtual ~Scene() = default;

        virtual void render(SDL_Renderer* render);

        virtual void push_layer(const LayerSPtr& layer);

        virtual void pop_layer(const LayerSPtr& layer);

        virtual void update();
        virtual void on_event(const events::EventSPtr& e);

        virtual inline std::string name() const { return _name; }

    private:
        std::string _name = "Simple Scene";
        LayerStack _layers;
};

using SceneSPtr = std::shared_ptr<Scene>;
using SceneUPtr = std::unique_ptr<Scene>;

}; // namespace yaschperitsy::core::renderer
