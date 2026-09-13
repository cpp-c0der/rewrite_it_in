#ifndef MENU_H
#define MENU_H

#include "core/mode.h"
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
    static inline constexpr char scores[] = "leaderbord";

    game::core::mode current_highlight = core::mode::level;
};

} // namespace game::scene

#endif
