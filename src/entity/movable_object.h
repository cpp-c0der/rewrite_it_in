#ifndef MOVABLE_OBJECT_H
#define MOVABLE_OBJECT_H

#include "object.h"

#include "geometry.h"

#include <stdint.h>

namespace game::entity
{

enum class direction : uint8_t
{
    right,
    left,
    up,
    down
};

class movable_object : public object
{
public:
    movable_object(game::geometry::point position, size hitbox, uint8_t speed);

    void move(const geometry::rectangle border, const object& obj);
    uint8_t get_speed() const;
    void set_speed(uint8_t speed);
    direction get_direction() const;
    void set_direction(direction dir);

protected:
    void move(const geometry::rectangle border, const object& obj, const uint8_t current_speed);

protected:
    uint8_t speed;
    direction current_direction = direction::right;
};

} // namespace game::entity

#endif
