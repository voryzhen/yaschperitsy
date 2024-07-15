#pragma once

#include "core/scene/Scene.hpp"
#include <core/App.hpp>
#include <cstddef>

namespace yaschperitsy::game
{

class Game : public yaschperitsy::core::App
{
    public:
        Game();
        ~Game();

    private:
        yaschperitsy::core::renderer::SceneSPtr _main_menu_scene{nullptr};
        yaschperitsy::core::renderer::SceneSPtr _settings_menu_scene{nullptr};
};

}; // namespace yaschperitsy::game
