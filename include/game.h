#pragma once

#include <array>
#include <memory>
#include <string_view>
#include <vector>

#include "background.h"
#include "components.h"
#include "ecs.h"
#include "keyboard_controller.h"
#include "resource_manager.h"
#include "topbar.h"
#include <SDL.h>

class Game
{
    public:
        Game(int field_width, int field_height, SDL_Renderer* renderer)
            : _renderer(renderer), _rm(_renderer),
              _player(_manager.add_entity()),
              _background(std::make_unique<Background>(
                  _rm.get_texture("background"),
                  _rm.get_texture("explosion"), field_width,
                  field_height)),
              _controller(
                  std::make_unique<KeyboardController>(&_keyboard)),
              _topbar(std::make_unique<Topbar>(_rm.get_font())),
              _field_width(field_width), _field_height(field_height)
        {
            _player.add_component<PositionComponent>(100, 100);
            _player.add_component<SpriteComponent>(
                _rm.get_texture("player"));
        }

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

        bool is_running() const { return !_quit; }

        unsigned char _fps = 60;
        unsigned char _frame_delay = 1000 / 60;

        SDL_Event event{};

        void update_enemies();
        void update_bullets();

        Manager _manager;
        Entity& _player;

        // ------------

        // Handle input
        void handle_input();

        void logic();
        void player_logic();
        void bullets_logic();
        void enemy_logic();

        void draw();
        void draw_player();
        void draw_bullets();
        void draw_enemies();

        void fire_bullet();
        void spawn_enemies();

        void bullet_hit_enemy();
        void bullet_hit_player();
        void enemy_fire();

        void draw_info();

        void reset_state();

        void render_text(const std::string& text);

        bool _quit{false};

        SDL_Renderer* _renderer{nullptr};

        ResourceManager _rm;

        // std::unique_ptr<Player> _player;
        // std::vector<Entity> _bullets;
        // std::vector<Enemy> _enemies;
        // std::vector<Entity> _enemy_bullets;
        std::unique_ptr<Background> _background;

        std::array<int, MAX_KEYBOARD_KEYS> _keyboard{};
        std::unique_ptr<KeyboardController> _controller;
        std::unique_ptr<Topbar> _topbar;

        int _field_width{0};
        int _field_height{0};

        int enemy_spawn_timer{0};

        size_t _score{0};
        size_t _max_score{0};
};
