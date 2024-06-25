#include <app/Window.h>

#include "Log.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string_view>

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
        logging::Logger::get_logger()->info(
            "SDL initialized successfully.");
    }
}

bool Window::init_sdl()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        logging::Logger::get_logger()->error(
            "Couldn't initialize SDL. Error: {0}", SDL_GetError());
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) < 0)
    {
        logging::Logger::get_logger()->error(
            "Couldn't initialize SDL Image. Error: {0}",
            SDL_GetError());
        return false;
    }

    _window.reset(SDL_CreateWindow(
        title.data(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, _window_flags));

    if (_window == nullptr)
    {
        logging::Logger::get_logger()->error(
            "Couldn't open window. Error: {0}", SDL_GetError());
        return false;
    }

    SDL_GetWindowSize(_window.get(), &_width, &_height);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    _renderer.reset(
        SDL_CreateRenderer(_window.get(), -1, _renderer_flags));

    if (_renderer == nullptr)
    {
        logging::Logger::get_logger()->error(
            "Couldn't create renderer. Error: {0}", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(_renderer.get(), 255, 255, 255, 255);

    if (TTF_Init() == -1)
    {
        logging::Logger::get_logger()->error(
            "Couldn't initialize SDL_ttf. Error: {0}", TTF_GetError());
        return false;
    }

    return true;
}

Window::~Window()
{
    logging::Logger::get_logger()->info("Cleaning up.");

    _renderer.reset(nullptr);
    _window.reset(nullptr);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

}; // namespace yaschperitsy::app
