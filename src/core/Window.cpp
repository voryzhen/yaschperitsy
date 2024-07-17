#include <core/Window.hpp>

#include <core/Logger.hpp>

#include <core/events/AppEvent.hpp>
#include <core/events/KeyEvent.hpp>
#include <core/events/MouseEvent.hpp>

#include <SDL_image.h>
#include <SDL_ttf.h>

namespace yaschperitsy::core
{

namespace
{
constexpr int _sdl_img_flags{IMG_INIT_PNG | IMG_INIT_JPG};
constexpr int _sdl_flags{SDL_INIT_VIDEO};
constexpr std::string_view _sdl_hint_flags{SDL_HINT_RENDER_SCALE_QUALITY};

constexpr int _window_flags{SDL_WINDOW_RESIZABLE};
} // namespace

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
            "Couldn't initialize SDL Image. Error: {0}", SDL_GetError());
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

    // NOLINTBEGIN
    _window.reset(SDL_CreateWindow(
        win_props._title.data(), SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, _data._width, _data._height, _window_flags));
    // NOLINTEND

    if (_window == nullptr)
    {
        logging::Logger::get_logger()->error("Couldn't open window. Error: {0}",
                                             SDL_GetError());
        return false;
    }

    return true;
}

void Window::update()
{
    SDL_PollEvent(&e);

    switch (e.type)
    {
    // Window event
    case SDL_WINDOWEVENT:
        if (e.window.event == SDL_WINDOWEVENT_RESIZED ||
            e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
        {
            _data._width = e.window.data1;
            _data._height = e.window.data2;
            // SDL_RenderPresent(_renderer.get());

            _data._event_callback(std::make_shared<events::WindowResizeEvent>(
                _data._width, _data._height));
        }
        else if (e.window.event == SDL_WINDOWEVENT_CLOSE)
        {
            _data._event_callback(std::make_shared<events::WindowCloseEvent>());
        }
        break;
    // Keyboard event
    case SDL_KEYDOWN:
        _data._event_callback(std::make_shared<events::KeyPressedEvent>(
            e.key.keysym.scancode, e.key.keysym.sym, e.key.repeat));
        break;
    case SDL_KEYUP:
        _data._event_callback(std::make_shared<events::KeyReleasedEvent>(
            e.key.keysym.scancode, e.key.keysym.sym));
        break;
    // Mouse event
    case SDL_MOUSEMOTION:
        _data._event_callback(
            std::make_shared<events::MouseMovedEvent>(e.motion.x, e.motion.y));
        break;
    case SDL_MOUSEBUTTONDOWN:
        _data._event_callback(std::make_shared<events::MouseButtonPressedEvent>(
            e.button.button, e.button.x, e.button.y));
        break;
    case SDL_MOUSEBUTTONUP:
        _data._event_callback(
            std::make_shared<events::MouseButtonReleasedEvent>(
                e.button.button, e.button.x, e.button.y));
        break;
    case SDL_MOUSEWHEEL:
        _data._event_callback(
            std::make_shared<events::MouseScrolledEvent>(e.wheel.x, e.wheel.y));
        break;
    default:
        break;
    }
}

Window::~Window()
{
    logging::Logger::get_logger()->info("Cleaning up.");

    _window.reset(nullptr);

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}

}; // namespace yaschperitsy::core
