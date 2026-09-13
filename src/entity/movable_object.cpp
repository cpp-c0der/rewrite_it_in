#include "movable_object.h"

namespace game::entity
{

movable_object::movable_object(game::geometry::point position, size hitbox, uint8_t speed) : object(position, hitbox), speed(speed)
{
}

void movable_object::move(const geometry::rectangle border, const object& obj, const object& obj2)
{
    move(border, obj, obj2, get_speed());
}

void movable_object::move(const geometry::rectangle border, const object& obj)
{
    move(border, obj, get_speed());
}

uint8_t movable_object::get_speed() const
{
    return speed;
}

void movable_object::set_speed(uint8_t speed)
{
    this->speed = speed;
}

direction movable_object::get_direction() const
{
    return current_direction;
}

void movable_object::set_direction(direction dir)
{
    current_direction = dir;
}

void movable_object::move(const geometry::rectangle border, const object& obj, const object& obj2, const uint8_t current_speed)
{
    process_border(border, current_speed);
    process_overlap(obj);
    process_overlap(obj2);
}

void movable_object::move(const geometry::rectangle border, const object& obj, const uint8_t current_speed)
{
    process_border(border, current_speed);
    process_overlap(obj);
}

void movable_object::process_border(const geometry::rectangle border, const uint8_t current_speed)
{
    switch (current_direction)
    {
    case direction::up:
        if (position.y > current_speed + border.left_up.y)
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
        if (position.x > current_speed + border.left_up.x)
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

void movable_object::process_overlap(const object& obj)
{
    if (is_intersect(obj))
    {
        const auto overlap_left = position.x + hitbox.first - obj.get_position().x;
        const auto overlap_right = obj.get_position().x + obj.get_hitbox().first - position.x;
        const auto overlap_top = position.y + hitbox.second - obj.get_position().y;
        const auto overlap_bottom = obj.get_position().y + obj.get_hitbox().second - position.y;

        const auto min_x = overlap_left > overlap_right ? overlap_right : overlap_left;
        const auto min_y = overlap_bottom > overlap_top ? overlap_top : overlap_bottom;

        if (min_x < min_y)
        {
            if (overlap_right < overlap_left)
                position.x += overlap_right;
            else
                position.x -= overlap_left;
        }
        else
        {
            if (overlap_bottom < overlap_top)
                position.y += overlap_bottom;
            else
                position.y -= overlap_top;
        }
    }
}

} // namespace game::entity
