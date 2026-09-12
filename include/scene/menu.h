#ifndef MENU_H
#define MENU_H

#include "scene/base.h"

namespace game::scene
{

class menu final : public scene::base
{
public:
    menu();
    void draw();
    void reset();

private:
    void process_key_press();

private:
    static inline constexpr char start[] = "start";
    static inline constexpr char scores[] = "scores";

    game::core::mode current_highlight = core::mode::game;
};

} // namespace game::scene

#endif
