#include "core/Logger.h"
#include "game/Game.h"

int main(int /* argc */, char* /* args */[])
{
    yaschperitsy::core::logging::Logger::init();

    yaschperitsy::game::Game game;
    game.new_run_app();
    return 0;
}
