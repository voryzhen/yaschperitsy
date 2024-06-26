#include <app/Window.h>

#include "Logger.h"
#include "SDL_events.h"
#include "SDL_video.h"
#include "app/events/AppEvent.h"
#include "app/events/Event.h"
#include "app/events/KeyEvent.h"
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <memory>
#include <string_view>

namespace
{
constexpr int _sdl_img_flags{IMG_INIT_PNG | IMG_INIT_JPG};
constexpr int _sdl_flags{SDL_INIT_VIDEO};
constexpr std::string_view _sdl_hint_flags{
    SDL_HINT_RENDER_SCALE_QUALITY};

constexpr int _renderer_flags{SDL_RENDERER_ACCELERATED};
constexpr int _window_flags{SDL_WINDOW_RESIZABLE};
} // namespace

namespace yaschperitsy::app
{

Window::Window()
{
    WindowProps win_props = {720, 1280, "Ящперицы"};

    if (init_sdl())
    {
        if (create_window(win_props))
        {
            logging::Logger::get_logger()->info(
                "SDL initialized successfully.");
        }
    }
}

bool Window::init_sdl()
{
    if (SDL_Init(_sdl_flags) < 0)
    {
        logging::Logger::get_logger()->error(
            "Couldn't initialize SDL. Error: {0}", SDL_GetError());
        return false;
    }

    if (IMG_Init(_sdl_img_flags) < 0)
    {
        logging::Logger::get_logger()->error(
            "Couldn't initialize SDL Image. Error: {0}",
            SDL_GetError());
        return false;
    }

    SDL_SetHint(_sdl_hint_flags.data(), "linear");

    if (TTF_Init() < 0)
    {
        logging::Logger::get_logger()->error(
            "Couldn't initialize SDL_ttf. Error: {0}", TTF_GetError());
        return false;
    }

    return true;
}

bool Window::create_window(const WindowProps& win_props)
{
    _data._height = win_props._height;
    _data._width = win_props._width;

    _window.reset(SDL_CreateWindow(
        win_props._title.data(), SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, _data._width, _data._height,
        _window_flags));

    if (_window == nullptr)
    {
        logging::Logger::get_logger()->error(
            "Couldn't open window. Error: {0}", SDL_GetError());
        return false;
    }

    _renderer.reset(
        SDL_CreateRenderer(_window.get(), -1, _renderer_flags));

    if (_renderer == nullptr)
    {
        logging::Logger::get_logger()->error(
            "Couldn't create renderer. Error: {0}", SDL_GetError());
        return false;
    }

    SDL_SetRenderDrawColor(_renderer.get(), 255, 255, 255, 255);

    return true;
}

void Window::update()
{
    SDL_PollEvent(&e);

    switch (e.type)
    {
    case SDL_WINDOWEVENT:
        if (e.window.event == SDL_WINDOWEVENT_RESIZED ||
            e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
        {
            process_window_resize_event();
        }
        else if (e.window.event == SDL_WINDOWEVENT_CLOSE)
        {
            process_window_close_event();
        }
        break;
    case SDL_KEYUP:
        process_keyboard_released_event();
        break;
    case SDL_KEYDOWN:
        process_keyboard_pressed_event();
        break;
    default:
        break;
    }
}

void Window::process_window_resize_event()
{
    _data._width = e.window.data1;
    _data._height = e.window.data2;
    SDL_RenderPresent(_renderer.get());

    _data._event_callback(std::make_shared<events::WindowResizeEvent>(
        _data._width, _data._height));
}

void Window::process_window_close_event()
{
    _data._event_callback(std::make_shared<events::WindowCloseEvent>());
}

void Window::process_keyboard_released_event()
{
    _data._event_callback(std::make_shared<events::KeyReleasedEvent>(
        e.key.keysym.scancode));
}

void Window::process_keyboard_pressed_event()
{
    _data._event_callback(std::make_shared<events::KeyPressedEvent>(
        e.key.keysym.scancode, e.key.repeat));
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
