#pragma once

#include <utility>

#include "core/scene/LayerStack.hpp"
#include "core/scene/Scene.hpp"

namespace yaschperitsy::game::scenes
{

class GameScene : public core::renderer::Scene
{
    public:
        GameScene(const core::LayerStack& layers) : Scene(layers) {};
        GameScene(std::string name, const core::LayerStack& layers)
            : Scene(std::move(name), layers) {};

        // virtual ~GameScene() override {};
        // virtual void push_layer(const LayerSPtr& layer);
        // virtual void pop_layer(const LayerSPtr& layer);
        // virtual void render(SDL_Renderer* render) override {};
        // virtual void update() override {}
        // virtual void on_event(const core::events::EventSPtr& e) override {}
};

}; // namespace yaschperitsy::game::scenes
