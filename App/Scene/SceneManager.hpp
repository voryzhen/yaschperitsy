#pragma once

#include "Scene.hpp"
#include <memory>
#include <string_view>
#include <unordered_map>

class SceneManager
{
    public:
        void add_scene(const std::string_view& name, const ScenePtr& scene);
        ScenePtr get_scene(const std::string_view& name);

    private:
        std::unordered_map<std::string_view, ScenePtr> _scenes;
};
using SceneManagerPtr = std::shared_ptr<SceneManager>;
