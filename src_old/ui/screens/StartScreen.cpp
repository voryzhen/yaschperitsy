#include "StartScreen.h"

namespace yaschperitsy::ui
{

int* StartScreen::_current_screen = nullptr;

void on_click_start_screen_new_game()
{
    *StartScreen::_current_screen = 3;
}

void on_click_start_screen_settings()
{
    *StartScreen::_current_screen = 1;
}

void on_click_start_screen_exit() { *StartScreen::_current_screen = 2; }

}; // namespace yaschperitsy::ui
