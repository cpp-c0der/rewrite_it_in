#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <stdint.h>

namespace game::geometry
{

struct point
{
    uint8_t x;
    uint8_t y;
};

struct rectangle
{
    point left_up;
    point right_down;
};

} // namespace game::geometry

#endif
