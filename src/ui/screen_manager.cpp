#include "SDL_events.h"
#include <ui/screen_manager.h>

int ScreenManager::update()
{
    switch (_current_screen)
    {
    case SCREENS::start:
        _start_screen->update();
        break;
    case SCREENS::settings:
        _settings_screent->update();
        break;
    case SCREENS::play:
        _play_screen->update();
        break;
    case SCREENS::exit:
        return -1;
        break;
    default:
        break;
    }
    return 0;
}

void ScreenManager::render(const SDL_RendererUPtr& renderer)
{
    switch (_current_screen)
    {
    case SCREENS::start:
        _start_screen->render(renderer);
        break;
    case SCREENS::settings:
        _settings_screent->render(renderer);
        break;
    case SCREENS::play:
        _play_screen->render(renderer);
        break;
    default:
        break;
    }
}

void ScreenManager::handle_events(const SDL_Event& event)
{
    switch (_current_screen)
    {
    case SCREENS::start:
        _start_screen->handle_events(event);
        break;
    case SCREENS::settings:
        _settings_screent->handle_events(event);
        break;
    case SCREENS::play:
        _play_screen->handle_events(event);
        break;
    default:
        break;
    }
}