#pragma once

#include <array>
#include <memory>
#include <string_view>
#include <vector>

#include "background.h"
#include "ecs/components.h"
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

class Game
{
    public:
        Game(int field_width, int field_height, SDL_Renderer* renderer);
        Game(const Game&) = delete;
        Game(const Game&&) = delete;
        Game& operator=(const Game&) = delete;
        Game& operator=(const Game&&) = delete;

        int run_game();

        ~Game() {}

    private:
        void handle_events();
        void update();
        void render();

        void game_update_enemies();
        void spawn_enemies();

        unsigned char _fps = 60;
        unsigned char _frame_delay = 1000 / _fps;
        bool _quit{false};
        SDL_Event _event{};
        Manager _manager{};

        SDL_Renderer* _renderer{nullptr};
        ResourceManager _rm;

        Entity& _player;
        std::unique_ptr<Background> _background;
        std::unique_ptr<Topbar> _topbar;

        GameField _field;

        int enemy_spawn_timer{0};
        int enemy_spawn_freq{1};

        // size_t _score{0};
        // size_t _max_score{0};
};
