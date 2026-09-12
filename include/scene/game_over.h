#ifndef GAME_OVER_SCENE_H
#define GAME_OVER_SCENE_H

#include "scene/base.h"

#include <stdint.h>

namespace game::scene
{

class game_over final : public scene::base
{
public:
    game_over(const uint32_t score);
    void draw();
    void reset();

private:
    void process_key_press();

private:
    static inline char text[] = "Game Over";
    static inline char score_text[] = "Scores: ";

    const uint32_t score;
};

} // namespace game::scene

#endif
