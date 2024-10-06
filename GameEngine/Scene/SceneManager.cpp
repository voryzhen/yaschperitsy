#include "SceneManager.hpp"

#include "Logger/Logger.hpp"

void SceneManager::add_scene(const std::string_view& name,
                             const ScenePtr& scene)
{
    _scenes.insert({ name, scene });
}

ScenePtr SceneManager::get_scene(const std::string_view& name)
{
    auto scene = _scenes.find(name);
    if (scene == _scenes.end())
    {
        Logger().error("Scene {} not found in Scene Manager", name);
        return nullptr;
    }
    return scene->second;
}
