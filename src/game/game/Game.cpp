#include "Game.hpp"

#include <core/Logger.hpp>

Game::Game()
{
    yaschperitsy::core::logging::Logger::get_logger()->info("Game");
}

Game::~Game()
{
    yaschperitsy::core::logging::Logger::get_logger()->info("~Game");
}
