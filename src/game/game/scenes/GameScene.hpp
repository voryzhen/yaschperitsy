#pragma once

#include <utility>

#include "core/resource_manager/ResourceManager.hpp"
#include "core/scene/LayerStack.hpp"
#include "core/scene/Scene.hpp"
#include "ecs/Manager.hpp"
#include "game/game/Assets.hpp"

namespace yaschperitsy::game::scenes
{

struct GameSettings
{
    public:
        GameSettings() = default;

        GameSettings(uint8_t bullet_speed, uint8_t player_speed,
                     uint8_t yaschperitsy_speed)
            : _bullet_speed(bullet_speed), _player_speed(player_speed),
              _yaschperitsy_speed(yaschperitsy_speed)
        {
        }

        // Game settings TODO: add yml reader to load params
        uint8_t _bullet_speed{5};
        uint8_t _player_speed{5};
        uint8_t _yaschperitsy_speed{3};
        uint8_t _yaschperitsy_spawn_freq{1};
};

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

        virtual void update() override
        {
            Scene::update();
            _manager.refresh();
            _manager.update({});
        }

        virtual void
        render(const core::renderer::SDLRendererUPtr& renderer) override
        {
            Scene::render(renderer);
            _manager.render(renderer);
        };

    private:
        void init_entites();

        GameSettings _game_settings;
        ecs::Manager _manager{};

        // virtual ~GameScene() override {};
        // virtual void push_layer(const LayerSPtr& layer);
        // virtual void pop_layer(const LayerSPtr& layer);
        // virtual void render(SDL_Renderer* render) override {};
        // virtual void on_event(const core::events::EventSPtr& e) override {}
};

}; // namespace yaschperitsy::game::scenes
