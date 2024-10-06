#pragma once

#include <cstdint>

struct GameStatistic
{
    public:
        std::uint8_t _score { 0 };
        std::uint8_t _max_score { 0 };
        std::uint8_t _yaschperitsy_num { 10 };
        std::uint8_t _yaschperitsy_total_num { 10 };
        std::uint8_t _curr_hp { 100 };
};

struct GameSettings
{
    public:
        GameSettings() = default;

        GameSettings(uint8_t bullet_speed, uint8_t player_speed,
                     uint8_t yaschperitsy_speed)
            : _bullet_speed(bullet_speed), _player_speed(player_speed),
              _yaschperitsy_speed(yaschperitsy_speed)
        {
        }

        // Game settings TODO: add yml reader to load params
        uint8_t _bullet_speed { 25 };
        uint8_t _player_speed { 5 };
        uint8_t _yaschperitsy_speed { 3 };
        uint8_t _yaschperitsy_spawn_freq { 1 };
};

struct GameInfo
{
        GameSettings settings;
        GameStatistic statistics {};
};
