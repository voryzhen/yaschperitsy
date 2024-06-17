#include <app/window.h>

#include <iostream>
#include <string_view>

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

namespace yaschperitsy::app
{

Window::Window()
{
    if (init_sdl())
    {
        _initialized = true;
    }
}

bool Window::init_sdl()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Couldn't initialize SDL: " << SDL_GetError()
                  << std::endl;
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0)
    {
        std::cout << "Couldn't initialize SDL Image: " << SDL_GetError()
                  << std::endl;
        return false;
    }

    _window.reset(SDL_CreateWindow(
        title.data(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, _window_flags));

    if (_window == nullptr)
    {
        std::cout << "Failed to open " << SCREEN_WIDTH << " x "
                  << SCREEN_HEIGHT << " window: " << SDL_GetError()
                  << std::endl;
        return false;
    }

    SDL_GetWindowSize(_window.get(), &_width, &_height);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    _renderer.reset(
        SDL_CreateRenderer(_window.get(), -1, _renderer_flags));

    if (_renderer == nullptr)
    {
        std::cout << "Failed to create renderer: " << SDL_GetError()
                  << std::endl;
        return false;
    }

    SDL_SetRenderDrawColor(_renderer.get(), 255, 255, 255, 255);

    if (TTF_Init() == -1)
    {
        std::cout << "SDL_ttf could not initialize! SDL_ttf Error: "
                  << TTF_GetError() << std::endl;
        return false;
    }

    return true;
}

Window::~Window()
{
    // Clean up
    _renderer.reset(nullptr);
    _window.reset(nullptr);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

}; // namespace yaschperitsy::app
