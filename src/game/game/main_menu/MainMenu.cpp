#include "MainMenu.hpp"

namespace yaschperitsy::game::ui::main_menu
{

void MainMenuLayer::render(SDL_Renderer* ren)
{
    new_game_button.render(ren);
    settings_button.render(ren);
    exit_button.render(ren);
}

void MainMenuLayer::on_event(const yaschperitsy::core::events::EventSPtr& event)
{
    new_game_button.on_event(event);
    settings_button.on_event(event);
    exit_button.on_event(event);
}

}; // namespace yaschperitsy::game::ui::main_menu
