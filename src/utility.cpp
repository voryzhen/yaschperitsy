#include "utility.h"

std::random_device rd;
std::mt19937 mt(rd());

int get_random_int(int max)
{
    std::uniform_real_distribution<double> dist(0, max);
    return (int)dist(mt);
}

bool collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2,
               int h2)
{
    return (std::max(x1, x2) < std::min(x1 + w1, x2 + w2)) &&
           (std::max(y1, y2) < std::min(y1 + h1, y2 + h2));
}

// bool collision(const Entity* e1, const Entity* e2)
// {
//     return collision(e1->_x, e1->_y, e1->_w, e1->_h, e2->_x, e2->_y,
//                      e2->_w, e2->_h);
// }
