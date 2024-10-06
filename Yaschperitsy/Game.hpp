#include "Events/Event.hpp"
#include "GameEngine/GameEngine.hpp"
#include "GameEngine/Scene/SceneManager.hpp"

class Game : public GameEngine
{
    public:
        Game();

        void init_game_scene();
        void init_main_menu_scene();
        void init_game_end_scene();

    private:
        void on_event(const EventSPtr& event);

        SceneManagerPtr scene_man_;
};
