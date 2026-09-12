#ifndef STATE_H
#define STATE_H

#include "core/mode.h"
#include "scene/game_over.h"
#include "scene/gameplay.h"
#include "scene/level.h"
#include "scene/menu.h"

namespace game::core
{

class state
{
public:
    scene::menu& get_menu();
    scene::gameplay& get_gameplay();
    scene::level& get_level();
    scene::game_over& get_game_over();

    mode get_current_scene() const;
    mode get_previous_scene() const;
    void set_current_scene(mode current_scene);

    void set_last_score(const uint32_t score);
    uint32_t get_last_score() const;

    void set_next_level(const uint32_t level_number);
    uint32_t get_next_level() const;

private:
    scene::menu menu;
    scene::gameplay gameplay;
    scene::game_over game_over;
    scene::level level;

    mode current_scene = mode::menu;
    mode previous_scene = mode::menu;

    uint32_t last_score;
    uint32_t last_level;
};

state& get_state();

} // namespace game::core

#endif
