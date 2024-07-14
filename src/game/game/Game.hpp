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
        yaschperitsy::core::renderer::SceneSPtr _scene{nullptr};
};

}; // namespace yaschperitsy::game
