#pragma once

#include "SDL_scancode.h"
#include "core/Logger.hpp"
#include "core/input/Input.hpp"
#include "core/scene/Scene.hpp"
#include "game/game/events/UIEvent.hpp"
#include <core/App.hpp>
#include <cstddef>

namespace yaschperitsy::game
{

class Game : public yaschperitsy::core::App
{
    public:
        Game();
        ~Game();

        void
        on_button_event(const yaschperitsy::core::events::EventSPtr& event);

        bool on_button_click(const events::UIEventSPtr& event);

        void shutdown() override
        {
            core::logging::Logger::get_logger()->info("Game shutdown");
            App::shutdown();
        };

        void update() override
        {
            if (core::input::Input::is_key_pressed(SDL_SCANCODE_ESCAPE))
            {
                if (scene() == "game")
                {
                    set_scene(_pause_menu_scene);
                }
            }
        }

    private:
        inline void create_scenes()
        {
            create_game_scene();
            create_settings_scene();
            create_main_menu_scene();
            create_pause_menu_scene();
        }

        void create_game_scene();
        void create_settings_scene();
        void create_main_menu_scene();
        void create_pause_menu_scene();

        yaschperitsy::core::scenes::SceneSPtr _main_menu_scene{nullptr};
        yaschperitsy::core::scenes::SceneSPtr _pause_menu_scene{nullptr};
        yaschperitsy::core::scenes::SceneSPtr _settings_menu_scene{nullptr};
        yaschperitsy::core::scenes::SceneSPtr _game_scene{nullptr};
};

}; // namespace yaschperitsy::game
