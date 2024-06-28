#pragma once

#include "Background.h"
#include "GameParameters.h"
#include "Topbar.h"
#include "core/ResourceManager.h"
#include "core/ecs/Entity.h"
#include "core/ecs/Manager.h"

#include "SDL_events.h"
#include "game/entities/Organism.h"
#include <SDL.h>
#include <memory>

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
        int update();
        void render(const SDL_RendererUPtr& renderer);

        void reset_state();

    private:
        // Yaschperitsy logic
        void update_yaschperitsy();
        void spawn_yaschperitsy();
        void fire_yaschperitsy();
        void update_yaschperitsy_direction();

        // Player logic
        void update_player();

        // Bullet logic
        void destroy_objects();
        void bullet_hit();

        unsigned char _fps = 60;
        bool _quit{false};
        bool _end{false};

        GameSettings _game_settings;
        GameField _game_field;
        int yaschperitsy_spawn_timer{0};

        SDL_Event _event{};
        ecs::Manager _manager{};

        const resource::ResourceManagerUPtr& _rm;

        std::shared_ptr<Organism> _player;
        std::unique_ptr<Background> _background;
        std::unique_ptr<Topbar> _topbar;

        GameStatisticUPtr _stat{new GameStatistic()};
};

} // namespace yaschperitsy::game
