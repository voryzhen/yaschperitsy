#include "App/App.hpp"
#include "App/Scene/SceneManager.hpp"
#include "Events/Event.hpp"
#include "Scenes/GameScene/GameSettings.hpp"

class Game : public App
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
