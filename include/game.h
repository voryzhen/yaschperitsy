#pragma once

#include <cstdint>
#include <memory>

#include "background.h"
#include "ecs/ecs.h"
#include "game_parameters.h"
#include "resource_manager.h"
#include "topbar.h"
#include <SDL.h>

using SDL_RendererPtr =
    std::unique_ptr<SDL_Renderer, decltype(&SDL_DestroyRenderer)>;

class Game
{
    public:
        Game(int field_width, int field_height,
             const SDL_RendererPtr& renderer);

        Game(const Game&) = delete;
        Game(const Game&&) = delete;
        Game& operator=(const Game&) = delete;
        Game& operator=(const Game&&) = delete;

        int run_game();

        ~Game() {}

    private:
        // Main logic
        void handle_events();
        void update();
        void render();

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
        unsigned char _frame_delay = 1000 / _fps;
        bool _quit{false};

        GameSettings _game_settings;
        GameField _game_field;
        int enemy_spawn_timer{0};

        SDL_Event _event{};
        Manager _manager{};

        const SDL_RendererPtr& _renderer;
        ResourceManager _rm;

        Entity& _player;
        std::unique_ptr<Background> _background;
        std::unique_ptr<Topbar> _topbar;

        std::unique_ptr<GameStatistic> _stat{new GameStatistic()};
};
