#pragma once

#include <array>
#include <memory>
#include <string_view>
#include <vector>

#include "controller.h"
#include "resource_manager.h"
#include <entity.h>

#include <SDL.h>

class Game
{
    public:
        Game(int field_width, int field_height, SDL_Renderer* renderer)
            : _renderer(renderer), _rm(_renderer),
              _player(
                  std::make_unique<Player>(_rm.get_texture("player"))),
              _controller(std::make_unique<Controller>(&_keyboard)),
              _field_width(field_width), _field_height(field_height)
        {
        }

        Game(const Game&) = delete;
        Game(const Game&&) = delete;
        Game& operator=(const Game&) = delete;
        Game& operator=(const Game&&) = delete;

        int run_game();

        ~Game() {}

    private:
        // Handle input
        void handle_input();

        // Hndle scene
        void prepare_scene();
        void present_scene();

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

        void draw_texture(SDL_Texture* texture, int x, int y);

        void render_text(const std::string& text, int x, int y);

        static std::uint32_t
        count_wait_60fps(const std::uint32_t& last);

        bool _quit{false};

        SDL_Renderer* _renderer{nullptr};

        ResourceManager _rm;

        std::unique_ptr<Player> _player;
        std::vector<Entity> _bullets;
        std::vector<Enemy> _enemies;
        std::vector<Entity> _enemy_bullets;

        std::array<int, MAX_KEYBOARD_KEYS> _keyboard{};
        std::unique_ptr<Controller> _controller;

        int _field_width{0};
        int _field_height{0};

        int enemy_spawn_timer{0};
        SDL_Color _text_color{0, 200, 200};

        size_t _score{0};
        size_t _max_score{0};
};
