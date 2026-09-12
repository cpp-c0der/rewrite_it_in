#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "entity/accelerable_object.h"
#include "scene/base.h"

#include <stdint.h>

namespace game::scene
{

class gameplay : public scene::base
{
public:
    gameplay();
    void draw();
    void reset();

private:
    void draw_sprites() const;
    void draw_status() const;
    void process_key_press();
    void process_project();
    void process_adrenaline();
    void process_enemy();

private:
    static inline constexpr auto border_width = uint8_t(2);
    static inline constexpr auto hero_default_speed = uint8_t(1);
    static inline constexpr auto enemy_default_speed = uint8_t(1);
    static inline constexpr auto hero_frame_interval = uint8_t(4);
    static inline constexpr auto enemy_frame_interval = uint8_t(16);
    static inline constexpr auto scores_for_project = uint8_t(10);
    static inline constexpr auto adrenaline_propability = uint8_t(1);

    entity::accelerable_object hero;
    entity::movable_object enemy;
    entity::object project;
    entity::object adrenaline;

    uint32_t hero_score = 0;
};

} // namespace game::scene

#endif
