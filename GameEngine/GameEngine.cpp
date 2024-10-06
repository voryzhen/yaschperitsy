#include "GameEngine.hpp"
#include <memory>

GameEngine::GameEngine() : ge_(GraphicEngine::get())
{
    ge_.initialize();
    ge_.set_event_callback([this](const EventSPtr& event) { on_event(event); });
}

GameEngine::~GameEngine() { ge_.finalize(); }

int GameEngine::run()
{
    while (is_run_)
    {
        timer_.tick();

        events();
        update();
        render();

        keep_fps(timer_.delta());
    }
    return 0;
}

int GameEngine::events()
{
    ge_.events();
    scene_->events();
    return 0;
}

int GameEngine::update()
{
    ge_.update();
    scene_->update();
    return 0;
}

int GameEngine::render()
{
    const auto& ren = ge_.renderer();
    ren.clear();
    scene_->render(ren);
    ren.present();
    return 0;
}

void GameEngine::keep_fps(uint32_t delta)
{
    constexpr double fps = 60.0;
    constexpr double frame_time = 1000000.0 / fps; // microsec
    // uint32_t real_fps = 1000000.0 / delta;
    delta = frame_time - delta;
    if (delta > .0)
    {
        timer_.sleep(delta);
    }
}

void GameEngine::on_event(const EventSPtr& event)
{
    EventDispatcher dispatcher(event);

    dispatcher.dispatch<WindowCloseEvent>(
        [this](const WindowCloseEventSPtr& event)
        { return on_window_close(event); });

    if (!event->is_handled())
    {
        scene_->on_event(event);
    }
}

bool GameEngine::on_window_close(const WindowCloseEventSPtr& /*event*/)
{
    is_run_ = false;
    return true;
}

void GameEngine::set_scene(const ScenePtr& scene) { scene_ = scene; }
