#include "movable_object.h"

namespace game::entity
{

movable_object::movable_object(game::geometry::point position, size hitbox, uint8_t speed) : object(position, hitbox), speed(speed)
{
}

void movable_object::move(const geometry::rectangle border)
{
    move(border, get_speed());
}

uint8_t movable_object::get_speed() const
{
    return speed;
}

direction movable_object::get_direction() const
{
    return current_direction;
}

void movable_object::set_direction(direction dir)
{
    current_direction = dir;
}

void movable_object::move(const geometry::rectangle border, const uint8_t current_speed)
{
    switch (current_direction)
    {
    case direction::up:
        if (position.y > current_speed)
            position.y -= current_speed;
        else
            position.y = border.left_up.y;
        break;
    case direction::down:
        if (position.y + hitbox.second + current_speed <= border.right_down.y)
            position.y += current_speed;
        else
            position.y = border.right_down.y - hitbox.second;
        break;
    case direction::left:
        if (position.x > current_speed)
            position.x -= current_speed;
        else
            position.x = border.left_up.x;
        break;
    case direction::right:
        if (position.x + hitbox.first + current_speed <= border.right_down.x)
            position.x += current_speed;
        else
            position.x = border.right_down.x - hitbox.first;
        break;
    }
}

} // namespace game::entity
