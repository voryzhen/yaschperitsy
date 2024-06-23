#include "GameEndScreen.h"

namespace yaschperitsy::ui
{

int* GameEndScreen::_current_screen = nullptr;

void on_click_gameend_screen_reset()
{
    *GameEndScreen::_current_screen = 3;
}

} // namespace yaschperitsy::ui
