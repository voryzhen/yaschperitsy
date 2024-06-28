#include "core/Logger.h"
#include "new_game/App.h"

int main(int /* argc */, char* /* args */[])
{
    yaschperitsy::core::logging::Logger::init();

    yaschperitsy::game::NewGame game;
    game.new_run_app();
    return 0;
}
