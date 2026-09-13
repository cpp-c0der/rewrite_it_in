#ifndef SCENE_H
#define SCENE_H

#include <stdint.h>

namespace game::core
{

enum class mode : uint8_t
{
    menu,
    game,
    scores,
    level,
    controls,
    end
};

} // namespace game::core

#endif
