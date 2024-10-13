#pragma once

#include "settingsYaml.hpp"

struct GameStatistic
{
    public:
        unsigned int _score { 0 };
        unsigned int _max_score { 0 };
        unsigned int _yaschperitsy_num { 0 };
        unsigned int _yaschperitsy_total_num { 0 };
        unsigned int _curr_hp { 0 };
};

struct GameSettings
{
        // Game settings TODO: add yml reader to load params
        unsigned int bullet_speed_ { 0 };
        unsigned int player_speed_ { 0 };
        unsigned int yaschperitsy_speed_ { 0 };
        unsigned int yaschperitsy_spawn_freq_ { 0 };
};

struct GameInfo
{
        GameSettings settings_;
        GameStatistic statistics_;
};
