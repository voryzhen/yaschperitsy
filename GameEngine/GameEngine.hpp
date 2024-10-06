#include "Events/AppEvent.hpp"
#include "GraphicEngine/GraphicEngine.hpp"

#include "GraphicEngine/ResourceManager/ResourceManager.hpp"
#include "GraphicEngine/Types.hpp"
#include "Scene/Scene.hpp"
#include "Timer/Timer.hpp"
#include <string_view>
#include <utility>

class GameEngine
{
    public:
        GameEngine();
        virtual ~GameEngine();
        int run();

        void set_scene(const ScenePtr& scene);

        const ResourceManager& get_rm() { return ge_.resource_manager(); }

        void shutdown() { is_run_ = false; }

        std::pair<int, int> get_window_size() const
        {
            return ge_.renderer().get_window_size();
        }

    private:
        int events();
        int update();
        int render();
        void keep_fps(uint32_t delta);
        void on_event(const EventSPtr& event);
        bool on_window_close(const WindowCloseEventSPtr& /*event*/);

        Timer timer_;
        bool is_run_ { true };

        GraphicEngine& ge_;
        ScenePtr scene_;
};
