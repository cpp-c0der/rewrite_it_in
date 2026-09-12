#ifndef LEVEL_SCENE_H
#define LEVEL_SCENE_H

#include "scene/base.h"

namespace game::scene
{

class level final : public game::scene::base
{
public:
    level(const uint32_t level_number);
    void draw();

private:
    void process_key_press();

private:
    static inline constexpr char text[] = "Level: ";

    uint32_t level_number;
};

} // namespace game::scene

#endif
