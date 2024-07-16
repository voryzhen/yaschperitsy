#include "Scene.hpp"

#include <algorithm>

namespace yaschperitsy::core::scenes
{

void Scene::push_layer(const LayerSPtr& layer) { _layers.push_layer(layer); }

void Scene::pop_layer(const LayerSPtr& layer) { _layers.pop_layer(layer); }

void Scene::render(SDL_Renderer* render)
{
    if (_layers.size() != 0u)
    {
        std::for_each(_layers.cbegin(), _layers.cend(),
                      [render](const LayerSPtr& l) { l->render(render); });
    }
}

void Scene::update()
{
    if (_layers.size() != 0u)
    {
        std::for_each(_layers.cbegin(), _layers.cend(),
                      [](const LayerSPtr& l) { l->update(); });
    }
}

void Scene::on_event(const events::EventSPtr& e)
{
    if (_layers.size() != 0u)
    {
        std::for_each(_layers.cbegin(), _layers.cend(),
                      [e](const LayerSPtr& l) { l->on_event(e); });
    }
}

}; // namespace yaschperitsy::core::scenes
