#include "object.h"

namespace game::entity
{

object::object(const game::geometry::point position, const size hitbox) : position(position), hitbox(hitbox)
{
}

game::geometry::point object::get_position() const
{
    return position;
}

void object::set_position(const game::geometry::point position)
{
    this->position = position;
}

object::size object::get_hitbox() const
{
    return hitbox;
}

bool object::is_intersect(const object& obj) const
{
    if (obj.is_hide() || &obj == this)
        return false;

    if (position.x + hitbox.first <= obj.position.x)
        return false;
    if (obj.position.x + obj.hitbox.first <= position.x)
        return false;
    if (position.y + hitbox.second <= obj.position.y)
        return false;
    if (obj.position.y + obj.hitbox.second <= position.y)
        return false;

    return true;
}

void object::hide()
{
    is_visible = false;
}

void object::show()
{
    is_visible = true;
}

bool object::is_hide() const
{
    return !is_visible;
}

} // namespace game::entity
