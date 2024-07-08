#include "SettingsScreen.h"

namespace yaschperitsy::ui
{

int* SettingsScreen::_current_screen = nullptr;

void on_click_settings_screen_settings()
{
    *SettingsScreen::_current_screen = 0;
}

}; // namespace yaschperitsy::ui
