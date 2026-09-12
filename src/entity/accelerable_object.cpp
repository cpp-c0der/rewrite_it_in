#include "accelerable_object.h"

namespace game::entity
{

void accelerable_object::move(const game::geometry::rectangle border)
{
    movable_object::move(border, get_speed());

    if (acceleration_enabled && energy)
        energy -= 1;

    if (!energy)
        disable_acceleration();
}

uint8_t accelerable_object::get_speed() const
{
    return acceleration_enabled ? speed * acceleration : speed;
}

uint8_t accelerable_object::get_energy() const
{
    return energy;
}

void accelerable_object::increase_energy(uint8_t value)
{
    energy += value;
}

void accelerable_object::enable_acceleration()
{
    acceleration_enabled = true;
}

void accelerable_object::disable_acceleration()
{
    acceleration_enabled = false;
}

} // namespace game::entity
