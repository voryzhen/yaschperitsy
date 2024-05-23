#pragma once

#include <array>
#include <memory>
#include <string_view>
#include <vector>

#include "background.h"
#include "ecs/components.h"
#include "ecs/ecs.h"
#include "keyboard_controller.h"
#include "resource_manager.h"
#include "topbar.h"
#include <SDL.h>

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

        // int _field_width{0};
        // int _field_height{0};

        // int enemy_spawn_timer{0};

        // size_t _score{0};
        // size_t _max_score{0};
};
