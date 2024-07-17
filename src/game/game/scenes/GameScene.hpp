#pragma once

#include <utility>

#include "GameSettings.hpp"
#include "YaschperitsyController.hpp"
#include "core/scene/LayerStack.hpp"
#include "core/scene/Scene.hpp"
#include "ecs/Manager.hpp"

namespace yaschperitsy::game::scenes
{

using EventCallbackFn =
    std::function<void(const yaschperitsy::core::events::EventSPtr&)>;

class GameScene : public core::scenes::Scene
{
    public:
        GameScene(std::string name)
            : GameScene(std::move(name), core::LayerStack{}) {};

        GameScene(std::string name, const EventCallbackFn& callback)
            : GameScene(std::move(name), core::LayerStack{})
        {
            _callback = callback;
        }

        GameScene(const core::LayerStack& layers)
            : GameScene("Simple Scene", layers) {};

        GameScene(std::string name, const core::LayerStack& layers);

        virtual void update() override;

        virtual void
        render(const core::renderer::SDLRendererUPtr& renderer) override
        {
            Scene::render(renderer);
            _manager.render(renderer);
        };

    private:
        void player_update();
        void player_fire();
        void bullet_hit();
        void destroy_objects();
        void reset_state();

        GameInfo _game_info{};

        EventCallbackFn _callback;

        ecs::Manager _manager{};
        YaschperitsyController::YaschperitsyController yash_ctrl{_manager,
                                                                 _game_info};

        // virtual ~GameScene() override {};
        // virtual void push_layer(const LayerSPtr& layer);
        // virtual void pop_layer(const LayerSPtr& layer);
        // virtual void on_event(const core::events::EventSPtr& e) override {}
};

}; // namespace yaschperitsy::game::scenes
