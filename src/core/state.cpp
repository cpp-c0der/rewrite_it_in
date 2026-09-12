#include "core/state.h"

namespace game::core
{

scene::menu& state::get_menu()
{
    return menu;
}

scene::gameplay& state::get_gameplay()
{
    return gameplay;
}

scene::level& state::get_level()
{
    return level;
}

scene::game_over& state::get_game_over()
{
    return game_over;
}

mode state::get_current_scene() const
{
    return current_scene;
}

mode state::get_previous_scene() const
{
    return previous_scene;
}

void state::set_current_scene(mode current_scene)
{
    this->previous_scene = this->current_scene;
    this->current_scene = current_scene;
}

void state::set_last_score(const uint32_t score)
{
    this->last_score = score;
}

uint32_t state::get_last_score() const
{
    return last_score;
}

void state::set_next_level(const uint32_t level_number)
{
    this->last_level = level_number;
}

uint32_t state::get_next_level() const
{
    return last_level;
}

state& get_state()
{
    static state s;

    return s;
}

} // namespace game::core
