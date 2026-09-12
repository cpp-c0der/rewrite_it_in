#ifndef ACCELERABLE_OBJECT_H
#define ACCELERABLE_OBJECT_H

#include "movable_object.h"

namespace game::entity
{

class accelerable_object : movable_object
{
public:
    using movable_object::movable_object;

    void move(direction dir);
    uint8_t get_speed() const;
    uint8_t get_energy() const;
    void increase_energy(uint8_t value);
    void enable_acceleration();
    void disable_acceleration();

private:
    static inline constexpr auto acceleration = uint8_t(2);

    uint8_t energy = 0;
    bool acceleration_enabled = false;
};

} // namespace game::entity

#endif
