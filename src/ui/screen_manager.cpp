#include "SDL_events.h"
#include <ui/screen_manager.h>

void ScreenManager::update(const SDL_Event& event)
{
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        _current_screen = SCREENS::settings;
    }
    if (event.type == SDL_MOUSEBUTTONUP)
    {
        _current_screen = SCREENS::start;
    }

    switch (_current_screen)
    {
    case SCREENS::start:
        _start_screen->update();
        break;
    case SCREENS::settings:
        _settings_screent->update();
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