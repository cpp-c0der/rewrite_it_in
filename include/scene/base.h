#ifndef BASE_SCENE_H
#define BASE_SCENE_H

#include "core/mode.h"

#include <stdint.h>

namespace game::scene
{

class base
{
public:
    base(const game::core::mode scene);
    game::core::mode get_scene() const;

    static inline constexpr uint8_t char_width = 5;
    static inline constexpr uint8_t char_height = 8;

protected:
    static inline constexpr uint8_t text_size = 1;

    game::core::mode current_scene;
};

} // namespace game::scene

#endif
