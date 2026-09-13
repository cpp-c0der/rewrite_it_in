#ifndef CONTROLS_SCENE_H
#define CONTROLS_SCENE_H

#include "scene/base.h"

namespace game::scene
{

class controls final : public scene::base
{
public:
    void draw();

private:
    static inline constexpr char movement_control[] = "movement - arrow";
    static inline constexpr char acceleration_control[] = "acceleration - A";
    static inline constexpr char menu_control[] = "menu - B";

    void process_key_press();
};

} // namespace game::scene

#endif
