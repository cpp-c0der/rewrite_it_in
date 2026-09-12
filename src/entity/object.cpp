#include "object.h"

namespace game::entity
{

object::object(const point position) : position(position)
{
}

object::point object::get_position() const
{
    return position;
}

} // namespace game::entity
