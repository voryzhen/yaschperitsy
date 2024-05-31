#pragma once

#include <memory>

#include "background.h"
#include "ecs/ecs.h"
#include "resource_manager.h"
#include "topbar.h"
#include <SDL.h>

struct GameField
{
    public:
        GameField() = default;

        GameField(int ww, int hh) : h(hh), w(ww) {}

        int h{0};
        int w{0};
};

using renderer_type =
    std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)>;

class Game
{
    public:
        Game(int field_width, int field_height,
             const renderer_type& renderer);

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

        unsigned char _fps = 60;
        unsigned char _frame_delay = 1000 / _fps;
        bool _quit{false};
        SDL_Event _event{};
        Manager _manager{};

        const renderer_type& _renderer;
        ResourceManager _rm;

        Entity& _player;
        std::unique_ptr<Background> _background;
        std::unique_ptr<Topbar> _topbar;

        GameField _field;

        int enemy_spawn_timer{0};
        int enemy_spawn_freq{1};

        GameStatistic _stat;
};
