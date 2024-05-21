#include <app.h>

#include <SDL_image.h>
#include <SDL_ttf.h>

std::unique_ptr<SDL_Window, void (*)(SDL_Window*)> App::_window =
    std::unique_ptr<SDL_Window, void (*)(SDL_Window*)>(
        nullptr, SDL_DestroyWindow);
std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)> App::_renderer =
    std::unique_ptr<SDL_Renderer, void (*)(SDL_Renderer*)>(
        nullptr, SDL_DestroyRenderer);

bool App::init_sdl()
{
    int rendererFlags = 0;
    int windowFlags = 0;

    rendererFlags = SDL_RENDERER_ACCELERATED;

    windowFlags = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0)
    {
        printf("Couldn't initialize SDL Image: %s\n", SDL_GetError());
        return false;
    }

    // NOLINTBEGIN(hicpp-signed-bitwise)
    _window.reset(SDL_CreateWindow(
        title.data(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, windowFlags));
    // NOLINTEND(hicpp-signed-bitwise)

    if (_window == nullptr)
    {
        printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH,
               SCREEN_HEIGHT, SDL_GetError());
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    _renderer.reset(
        SDL_CreateRenderer(_window.get(), -1, rendererFlags));

    if (_renderer == nullptr)
    {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(_renderer.get(), 255, 255, 255, 255);

    // Initialize SDL_ttf
    if (TTF_Init() == -1)
    {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n",
               TTF_GetError());
        return false;
    }

    return true;
}

void App::cleanup()
{
    // Clean up
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
