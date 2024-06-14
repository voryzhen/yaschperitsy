#include "SDL_events.h"
#include <ui/screen_manager.h>

int ScreenManager::update(const SDL_Event& event)
{
    switch (_current_screen)
    {
    case SCREENS::start:
        _start_screen->update(event);
        break;
    case SCREENS::settings:
        _settings_screent->update(event);
        break;
    case SCREENS::exit:
        return -1;
        break;
    default:
        break;
    }
    return 0;
}

void ScreenManager::render()
{
    switch (_current_screen)
    {
    case SCREENS::start:
        _start_screen->render();
        break;
    case SCREENS::settings:
        _settings_screent->render();
        break;
    default:
        break;
    }
}