#pragma once

#include "SDL_events.h"
#include "game/Game.h"
#include "ui/BaseScreen.h"
#include <core/ResourceManager.h>

namespace yaschperitsy::ui
{

class GameScreen : public BaseScreen
{
    public:
        GameScreen(const resource::ResourceManagerUPtr& rm,
                   int* current_screen)
            : BaseScreen(rm, current_screen)
        {
            _game = std::make_unique<game::Game>(rm);
        }

        void handle_events(const SDL_Event& event) override
        {
            _game->handle_events(event);
        }

        int update() override
        {
            _game->reset_state();
            return _game->update();
        }

        void render(const core::SDL_RendererUPtr& _renderer) override
        {
            _game->render(_renderer);
        }

    private:
        std::unique_ptr<game::Game> _game;
};

using GameScreenUPtr = std::unique_ptr<GameScreen>;

}; // namespace yaschperitsy::ui
