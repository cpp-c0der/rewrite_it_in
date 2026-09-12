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
    static inline constexpr auto default_speed = uint8_t(1);
    static inline constexpr auto frame_interval = uint8_t(4);
    static inline constexpr auto scores_for_project = uint8_t(10);
    static inline constexpr auto adrenaline_propability = uint8_t(100);

    entity::accelerable_object hero;
    entity::object project;
    entity::object adrenaline;

    uint64_t hero_scores = 0;
};

} // namespace game::scene

#endif
