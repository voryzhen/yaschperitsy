#include "SDL_events.h"
#include <ui/screen_manager.h>

void ScreenManager::update(const SDL_Event& event)
{
    switch (_current_screen)
    {
    case SCREENS::start:
        _start_screen->update(event);
        break;
    case SCREENS::settings:
        _settings_screent->update(event);
        break;
    default:
        break;
    }
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