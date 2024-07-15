#include "SettingsMenu.hpp"

namespace yaschperitsy::game::ui::main_menu
{

void SettingsMenuLayer::render(SDL_Renderer* ren) { _back_button.render(ren); }

void SettingsMenuLayer::on_event(
    const yaschperitsy::core::events::EventSPtr& event)
{
    _back_button.on_event(event);
}

}; // namespace yaschperitsy::game::ui::main_menu
