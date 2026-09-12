#include "movable_object.h"

namespace game::entity
{

movable_object::movable_object(point position, uint8_t speed) : object(position), speed(speed)
{
}

void movable_object::move(direction dir)
{
    switch (dir)
    {
    case direction::up:
        position.second -= get_speed();
        break;
    case direction::down:
        position.second += get_speed();
        break;
    case direction::left:
        position.first -= get_speed();
        break;
    case direction::right:
        position.first += get_speed();
        break;
    }
}

uint8_t movable_object::get_speed() const
{
    return speed;
}

} // namespace game::entity
