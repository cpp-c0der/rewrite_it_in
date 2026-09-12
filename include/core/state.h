#ifndef STATE_H
#define STATE_H

#include "scene/gameplay.h"
#include "scene/menu.h"

namespace game::core
{

class state
{
public:
    scene::menu& get_menu();
    scene::gameplay& get_gameplay();
    mode get_current_scene() const;
    void set_current_scene(mode current_scene);

private:
    scene::menu menu;
    scene::gameplay gameplay;
    mode current_scene = mode::menu;
};

state& get_state();

} // namespace game::core

#endif
