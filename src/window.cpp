#include <window.h>

#include "SDL.h"
#include "SDL_render.h"
#include <SDL_image.h>
#include <SDL_ttf.h>

namespace
{
constexpr int SCREEN_WIDTH{1280};
constexpr int SCREEN_HEIGHT{720};
constexpr std::string_view title = "Ящперицы";
constexpr int _renderer_flags{SDL_RENDERER_ACCELERATED};
constexpr int _window_flags{0};
} // namespace

Window::Window()
{
    if (init_sdl())
    {
        initialized = true;
    }
}

bool Window::init_sdl()
{
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
        SCREEN_WIDTH, SCREEN_HEIGHT, _window_flags));
    // NOLINTEND(hicpp-signed-bitwise)

    if (_window == nullptr)
    {
        printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH,
               SCREEN_HEIGHT, SDL_GetError());
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    _renderer.reset(
        SDL_CreateRenderer(_window.get(), -1, _renderer_flags),
        [](SDL_Renderer* ren) { SDL_DestroyRenderer(ren); });

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

Window::~Window() { cleanup(); }

void Window::cleanup()
{
    // Clean up
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}
