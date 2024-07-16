#pragma once

#include <utility>

#include "GameSettings.hpp"
#include "YaschperitsyController.hpp"
#include "core/scene/LayerStack.hpp"
#include "core/scene/Scene.hpp"
#include "ecs/Manager.hpp"

namespace yaschperitsy::game::scenes
{

class GameScene : public core::scenes::Scene
{
    public:
        GameScene(std::string name) : GameScene(std::move(name), {}) {};

        GameScene(const core::LayerStack& layers)
            : GameScene(std::move("Simple Scene"), layers) {};

        GameScene(std::string name, const core::LayerStack& layers)
            : Scene(std::move(name), layers)
        {
            init_entites();
        };

        virtual void update() override;

        virtual void
        render(const core::renderer::SDLRendererUPtr& renderer) override
        {
            Scene::render(renderer);
            _manager.render(renderer);
        };

    private:
        void init_entites();

        void update_yaschperitsy();
        void destroy_objects();

        GameSettings _game_settings;
        ecs::Manager _manager{};
        YaschperitsyController::YaschperitsyController yash_ctrl{
            _manager, _game_settings};

        // virtual ~GameScene() override {};
        // virtual void push_layer(const LayerSPtr& layer);
        // virtual void pop_layer(const LayerSPtr& layer);
        // virtual void on_event(const core::events::EventSPtr& e) override {}
};

}; // namespace yaschperitsy::game::scenes
