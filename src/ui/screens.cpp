#include "ui/Screens.h"

namespace yaschperitsy::ui
{

int* StartScreen::_current_screen = nullptr;
int* SettingsScreen::_current_screen = nullptr;

void on_click_start_screen_new_game()
{
    *StartScreen::_current_screen = 3;
}

void on_click_start_screen_settings()
{
    *StartScreen::_current_screen = 1;
}

void on_click_start_screen_exit() { *StartScreen::_current_screen = 2; }

void on_click_settings_screen_settings()
{
    *SettingsScreen::_current_screen = 0;
}

}; // namespace yaschperitsy::ui
