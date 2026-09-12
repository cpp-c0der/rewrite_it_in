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

mode state::get_current_scene() const
{
    return current_scene;
}

void state::set_current_scene(mode current_scene)
{
    this->current_scene = current_scene;
}

state& get_state()
{
    static state s;

    return s;
}

} // namespace game::core
