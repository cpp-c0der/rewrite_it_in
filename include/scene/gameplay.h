#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "entity/accelerable_object.h"

#include <stdint.h>

namespace game::scene
{

class gameplay
{
public:
    gameplay();
    void draw();

private:
    void process_key_press();

private:
    static inline constexpr auto border_width = uint8_t(2);
    static inline constexpr auto default_speed = uint8_t(4);

    entity::accelerable_object hero;
};

} // namespace game::scene

#endif
