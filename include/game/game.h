#pragma once

#include <cstdint>
#include <memory>

#include "SDL_events.h"
#include "background.h"
#include "ecs/ecs.h"
#include "game_parameters.h"
#include "resource_manager.h"
#include "topbar.h"
#include <SDL.h>

namespace yaschperitsy::app
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
        void game_update_enemies();
        void spawn_enemies();
        void fire_enemies();

        // Player logic
        void game_update_player();

        void destroy_objects();

        void bullet_hit();

        void reset_state();

        void compose_player();

        unsigned char _fps = 60;
        bool _quit{false};

        GameSettings _game_settings;
        GameField _game_field;
        int enemy_spawn_timer{0};

        SDL_Event _event{};
        Manager _manager{};

        const resource::ResourceManagerUPtr& _rm;

        Entity& _player;
        std::unique_ptr<Background> _background;
        std::unique_ptr<Topbar> _topbar;

        std::unique_ptr<GameStatistic> _stat{new GameStatistic()};
};

} // namespace yaschperitsy::app
