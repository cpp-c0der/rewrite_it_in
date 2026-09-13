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

private:
    void reset();
    void to_next_level();
    void draw_sprites() const;
    void draw_status() const;
    void process_key_press();
    void process_project();
    void process_adrenaline();
    void process_enemy();
    void reset_objects();

private:
    static inline constexpr auto border_width = uint8_t(2);
    static inline constexpr auto hero_default_speed = uint8_t(1);
    static inline constexpr auto enemy_default_speed = uint8_t(1);
    static inline constexpr auto hero_frame_interval = uint8_t(4);
    static inline constexpr auto enemy_frame_interval = uint8_t(16);
    static inline constexpr auto scores_for_project = uint8_t(10);
    static inline constexpr auto adrenaline_propability = uint8_t(1);
    static inline constexpr auto project_limit_factor = 2;
    static inline constexpr auto project_limit_base = 10;
    static inline constexpr auto time_limit_factor = 20;
    static inline constexpr auto time_limit_base = 60;

    uint32_t hero_score = 0;
    uint32_t level_number = 0;

    uint32_t project_limit = project_limit_base;
    uint32_t project_remaining = project_limit;

    uint32_t time_limit = time_limit_base;
    uint32_t time_remaining = time_limit;

    uint8_t frame_count = 0;

    entity::accelerable_object hero;
    entity::movable_object enemy;
    entity::movable_object enemy2;
    entity::object project;
    entity::object adrenaline;
};

} // namespace game::scene

#endif
