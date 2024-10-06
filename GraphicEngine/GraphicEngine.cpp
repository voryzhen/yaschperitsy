#include "GraphicEngine.hpp"
#include "GraphicEngine/GraphicSystem.hpp"
#include <SDL_events.h>

#include "Events/AppEvent.hpp"
#include "Events/KeyEvent.hpp"
#include "Events/MouseEvent.hpp"
#include "Logger/Logger.hpp"
#include "Types.hpp"

GraphicEngine& GraphicEngine::get()
{
    static GraphicEngine singleton;
    return singleton;
}

ErrorCode GraphicEngine::initialize() const
{
    if (GraphicSystem::initialize() != ErrorCode::NoError)
    {
        Logger().error("GraphicSystem initialization error");
        return ErrorCode::GraphicEngineInitError;
    }
    if (_ren.initialize() != ErrorCode::NoError)
    {
        Logger().error("Renderer initialization error");
        return ErrorCode::GraphicEngineInitError;
    }
    return ErrorCode::NoError;
}

ErrorCode GraphicEngine::finalize() const
{
    if (_ren.finalize() != ErrorCode::NoError)
    {
        Logger().error("Renderer finalization error");
        return ErrorCode::GraphicEngineFinalizeError;
    }
    if (GraphicSystem::finalize() != ErrorCode::NoError)
    {
        Logger().error("GraphicSystem finalization error");
        return ErrorCode::GraphicEngineFinalizeError;
    }
    return ErrorCode::NoError;
}

const Renderer& GraphicEngine::renderer() const { return _ren; }

const ResourceManager& GraphicEngine::resource_manager() const { return _rm; }

void GraphicEngine::set_event_callback(const EventCallbackFn& ec)
{
    _event_callback = ec;
}

int GraphicEngine::events() const
{

    SDL_Event e;
    SDL_PollEvent(&e);

    switch (e.type)
    {
        // Window event
        case SDL_WINDOWEVENT:
            if (e.window.event == SDL_WINDOWEVENT_RESIZED ||
                e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
            {
                auto _width = e.window.data1;
                auto _height = e.window.data2;
                // SDL_RenderPresent(_renderer.get());

                _event_callback(
                    std::make_shared<WindowResizeEvent>(_width, _height));
            }
            else if (e.window.event == SDL_WINDOWEVENT_CLOSE)
            {
                _event_callback(std::make_shared<WindowCloseEvent>());
            }
            break;
        // Keyboard event
        case SDL_KEYDOWN:
            _event_callback(std::make_shared<KeyPressedEvent>(
                e.key.keysym.scancode, e.key.keysym.sym, e.key.repeat));
            break;
        case SDL_KEYUP:
            _event_callback(std::make_shared<KeyReleasedEvent>(
                e.key.keysym.scancode, e.key.keysym.sym));
            break;
        // Mouse event
        case SDL_MOUSEMOTION:
            _event_callback(
                std::make_shared<MouseMovedEvent>(e.motion.x, e.motion.y));
            break;
        case SDL_MOUSEBUTTONDOWN:
            _event_callback(std::make_shared<MouseButtonPressedEvent>(
                e.button.button, e.button.x, e.button.y));
            break;
        case SDL_MOUSEBUTTONUP:
            _event_callback(std::make_shared<MouseButtonReleasedEvent>(
                e.button.button, e.button.x, e.button.y));
            break;
        case SDL_MOUSEWHEEL:
            _event_callback(
                std::make_shared<MouseScrolledEvent>(e.wheel.x, e.wheel.y));
            break;
        default:
            break;
    }

    return 0;
}

int GraphicEngine::update() const { return 0; }

int GraphicEngine::render() const { return 0; }

GraphicEngine::GraphicEngine()
    : _ren(Renderer::get()), _rm(ResourceManager::get())
{
}