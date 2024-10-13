#pragma once

#include "App/Scene/Scene.hpp"
#include "Controllers/YaschperitsyController.hpp"
#include "GraphicEngine/GraphicEngine.hpp"
#include "GraphicEngine/ResourceManager/ResourceManager.hpp"
#include "Scenes/GameScene/Controllers/PlayerController.hpp"
#include "Scenes/GameScene/Controllers/UIController.hpp"
#include "Scenes/GameScene/GameSettings.hpp"

class GameScene : public Scene
{
    public:
        GameScene(const ResourceManager& rm, EventCallbackFn callback,
                  int win_width, int win_height);

        void on_event(const EventSPtr& event) override;
        void events() override;
        void update() override;
        void render(const Renderer& ren) override;

    private:
        void player_update();
        void destroy_objects();
        void bullet_hit();
        void reset_state();
        bool outfield(const Vector2D<float>& position);

        const ResourceManager& rm_;

        ControllerArray controllers_;

        int win_width_ { 0 };
        int win_height_ { 0 };

        GameInfo game_info_ {};

        EventCallbackFn callback_;
};
