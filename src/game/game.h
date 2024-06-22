#pragma once

#include "Background.h"
#include "GameParameters.h"
#include "Topbar.h"
#include "app/ResourceManager.h"
#include "ecs/Entity.h"
#include "ecs/Manager.h"

#include "SDL_events.h"
#include <SDL.h>

namespace yaschperitsy::game
{

class Game
{
    public:
        Game(const resource::ResourceManagerUPtr& rm);

        Game(const Game&) = delete;
        Game(const Game&&) = delete;
        Game& operator=(const Game&) = delete;
        Game& operator=(const Game&&) = delete;

        ~Game() {}

        // Main logic
        void handle_events(const SDL_Event& event);
        void update();
        void render(const SDL_RendererUPtr& renderer);

    private:
        // Enemies logic
        void update_enemies();
        void spawn_enemies();
        void fire_enemies();
        void update_enemies_direction();

        // Player logic
        void update_player();

        // Bullet logic
        void destroy_objects();
        void bullet_hit();

        void reset_state();

        unsigned char _fps = 60;
        bool _quit{false};

        GameSettings _game_settings;
        GameField _game_field;
        int enemy_spawn_timer{0};

        SDL_Event _event{};
        ecs::Manager _manager{};

        const resource::ResourceManagerUPtr& _rm;

        ecs::EntitySPtr _player;
        std::unique_ptr<Background> _background;
        std::unique_ptr<Topbar> _topbar;

        GameStatisticUPtr _stat{new GameStatistic()};
};

} // namespace yaschperitsy::game
