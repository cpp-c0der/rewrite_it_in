#include "scene/base.h"

namespace game::scene
{

base::base(const game::core::mode scene) : current_scene(scene)
{
}

game::core::mode base::get_scene() const
{
    return current_scene;
}

} // namespace game::scene
