#include "accelerable_object.h"

namespace game::entity
{

void accelerable_object::move(const game::geometry::rectangle border, const object& obj)
{
    movable_object::move(border, obj, get_speed());
    process_energy();
}

void accelerable_object::move(const game::geometry::rectangle border, const object& obj, const object& obj2)
{
    movable_object::move(border, obj, obj2, get_speed());
    process_energy();
}

uint8_t accelerable_object::get_speed() const
{
    return acceleration_enabled ? speed * acceleration : speed;
}

uint8_t accelerable_object::get_energy() const
{
    return energy;
}

void accelerable_object::add_energy(uint8_t value)
{
    energy += value;

    if (energy > energy_limit)
        energy = energy_limit;
}

void accelerable_object::switch_acceleration()
{
    acceleration_enabled = !acceleration_enabled;
}

void accelerable_object::enable_acceleration()
{
    acceleration_enabled = true;
}

void accelerable_object::disable_acceleration()
{
    acceleration_enabled = false;
}

void accelerable_object::process_energy()
{
    if (acceleration_enabled && energy)
        energy -= 1;

    if (!energy)
        disable_acceleration();
}

} // namespace game::entity
