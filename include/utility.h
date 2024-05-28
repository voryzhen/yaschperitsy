#pragma once

#include <random>

int get_random_int(int max);
bool collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2,
               int h2);
// bool collision(const Entity* e1, const Entity* e2);