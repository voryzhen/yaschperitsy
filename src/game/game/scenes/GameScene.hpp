#pragma once

#include <utility>

#include "core/scene/LayerStack.hpp"
#include "core/scene/Scene.hpp"
#include "ecs/Manager.hpp"

namespace yaschperitsy::game::scenes
{

class GameScene : public core::scenes::Scene
{
    public:
        GameScene(const core::LayerStack& layers) : Scene(layers) {};
        GameScene(std::string name, const core::LayerStack& layers)
            : Scene(std::move(name), layers) {};

        virtual void update() override
        {
            Scene::update();
            _manager.refresh();
        }

        virtual void
        render(const core::renderer::SDLRendererUPtr& renderer) override
        {
            Scene::render(renderer);
            // _manager.render(renderer);
        };

        ecs::Manager _manager;

        // virtual ~GameScene() override {};
        // virtual void push_layer(const LayerSPtr& layer);
        // virtual void pop_layer(const LayerSPtr& layer);
        // virtual void render(SDL_Renderer* render) override {};
        // virtual void on_event(const core::events::EventSPtr& e) override {}
};

}; // namespace yaschperitsy::game::scenes
