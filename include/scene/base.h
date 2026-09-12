#ifndef BASE_SCENE_H
#define BASE_SCENE_H

#include <stdint.h>

namespace game::scene
{

class base
{
public:
    static inline constexpr uint8_t char_width = 5;
    static inline constexpr uint8_t char_height = 8;

protected:
    static inline constexpr uint8_t text_size = 1;
};

} // namespace game::scene

#endif
