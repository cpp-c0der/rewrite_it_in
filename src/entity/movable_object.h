#ifndef MOVABLE_OBJECT_H
#define MOVABLE_OBJECT_H

#include "object.h"

#include <stdint.h>

namespace game::entity
{

enum class direction : uint8_t
{
    up,
    down,
    left,
    right
};

class movable_object : public object
{
public:
    movable_object(point position, uint8_t speed);

    void move(direction dir);
    uint8_t get_speed() const;

protected:
    uint8_t speed;
};

} // namespace game::entity

#endif
